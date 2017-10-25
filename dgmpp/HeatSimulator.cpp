#include "HeatSimulator.h"
#include "Ship.h"
#include "Module.h"
#include "Attribute.h"
#include <math.h>
#include <algorithm>

using namespace dgmpp;

class StateCompareFunction : public std::binary_function<std::shared_ptr<const HeatSimulator::State> const&, std::shared_ptr<const HeatSimulator::State> const&, bool>
{
public:
	bool operator() (std::shared_ptr<const HeatSimulator::State> const& a, std::shared_ptr<const HeatSimulator::State> const& b)
	{
		return a->tNow > b->tNow;
	}
};

HeatSimulator::HeatSimulator(std::shared_ptr<Ship> const& ship) : ship_(ship)
{
}

HeatSimulator::~HeatSimulator(void)
{
	states_.clear();
}

void HeatSimulator::reset()
{
	isCalculated_ = false;
}


void HeatSimulator::simulate()
{
	if (!isCalculated_)
	{
		std::shared_ptr<Ship> ship = ship_.lock();
		if (!ship)
			return;
		
		for (auto slot: {Module::Slot::hi, Module::Slot::mode, Module::Slot::low}) {
			simulate(ship->getModules(slot, true));
		}
		
		isCalculated_ = true;
	}
}

void HeatSimulator::simulate(const ModulesList& modules)
{
	if (modules.size() == 0)
		return;
	
	states_.clear();

	std::shared_ptr<Ship> ship = ship_.lock();
	if (!ship)
		return;
	std::shared_ptr<Module> module = modules.front();
	Module::Slot slot = module->getSlot();
	Float heatCapacity = 0;
	Float heatGenerationMultiplier = ship->getAttribute(AttributeID::heatGenerationMultiplier)->getValue();
	Float heatAttenuation = 0;
	Float heatGeneration = 0;
	Float heatAbsorbtionRateModifier = 0;
	int numberOfSlots = ship->getNumberOfSlots(slot);
	int numberOfOnlineModules = 0;
	
	if (slot == Module::Slot::hi)
	{
		heatCapacity = ship->getAttribute(AttributeID::heatCapacityHi)->getValue() / 100.0;
		heatAttenuation = ship->getAttribute(AttributeID::heatAttenuationHi)->getValue();
	}
	else if (slot == Module::Slot::med)
	{
		heatCapacity = ship->getAttribute(AttributeID::heatCapacityMed)->getValue() / 100.0;
		heatAttenuation = ship->getAttribute(AttributeID::heatAttenuationMed)->getValue();
	}
	else if (slot == Module::Slot::low)
	{
		heatCapacity = ship->getAttribute(AttributeID::heatCapacityLow)->getValue() / 100.0;
		heatAttenuation = ship->getAttribute(AttributeID::heatAttenuationLow)->getValue();
	}
	
	int n = (int) modules.size();
	std::vector<Float> modulesHP(n);

	for (int i = 0; i < n; i++)
	{
		std::shared_ptr<Module> module = modules[i];
		if (module->isDummy())
			continue;
		
		modulesHP[i] = module->getAttribute(AttributeID::hp)->getValue();
		Module::State state = module->getState();
		if (state >= Module::State::online)
			numberOfOnlineModules++;
		if (state == Module::State::overloaded)
		{
			heatAbsorbtionRateModifier += module->getAttribute(AttributeID::heatAbsorbtionRateModifier)->getValue();
			int clipSize = module->getShots();

			std::shared_ptr<State> state = std::make_shared<State>();
			state->tNow = 0;
			state->duration = static_cast<int>(module->getCycleTime() * 1000.0);
			state->clipSize = clipSize;
			state->shot = 0;
			state->reloadTime = static_cast<int>(module->getReloadTime());
			state->moduleIndex = i;
			state->heatDamage = module->getAttribute(AttributeID::heatDamage)->getValue();
			states_.push_back(state);
			std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
		}
	}
	heatGeneration = heatAbsorbtionRateModifier * heatGenerationMultiplier;
	
	if (states_.size() > 0)
	{
		int tNow = 0;
		std::shared_ptr<State> state;

		while (1)
		{
			state = states_.front();
			std::pop_heap(states_.begin(), states_.end(), StateCompareFunction());
			states_.pop_back();

			tNow = state->tNow;
			
			Float h = heat(static_cast<Float>(tNow), heatCapacity, heatGeneration);
			int numberOfDeadModules = 0;
			for (int i = 0; i < n; i++)
			{
				if (modulesHP[i] > 0)
				{
					int range = abs(i - state->moduleIndex);
					modulesHP[i] -= damageProbability(h, range, numberOfOnlineModules, numberOfSlots, heatAttenuation) * state->heatDamage;
					if (modulesHP[i] <= 0.0)
					{
						modules[i]->setLifeTime(tNow / 1000.0);
						numberOfDeadModules++;
					}
				}
				else
					numberOfDeadModules++;
			}
			
			if (numberOfDeadModules == n)
				break;
			
			tNow += state->duration;
			state->shot++;
			
			if (state->clipSize) {
				if (state->shot % state->clipSize == 0) {
					state->shot = 0;
					tNow += state->reloadTime;
				}
			}
			state->tNow = tNow;
			states_.push_back(state);
			std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
		}
	}
}

Float HeatSimulator::heat(Float t, Float heatCapacity, Float heatGeneration)
{
	return heatCapacity - exp(-t * heatGeneration);
}

Float HeatSimulator::damageProbability(Float h, int range, int numberOfOnlineModules, int numberOfSlots, Float heatAttenuation)
{
	return (float) numberOfOnlineModules / (float) numberOfSlots * h * pow(heatAttenuation, range);
}
