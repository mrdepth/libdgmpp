#include "HeatSimulator.h"
#include "Ship.h"
#include "Module.h"
#include "Attribute.h"
#include <math.h>
#include <algorithm>

using namespace eufe;

class StateCompareFunction : public std::binary_function<std::shared_ptr<const HeatSimulator::State>, std::shared_ptr<const HeatSimulator::State>, bool>
{
public:
	bool operator() (std::shared_ptr<const HeatSimulator::State> a, std::shared_ptr<const HeatSimulator::State> b)
	{
		return a->tNow > b->tNow;
	}
};

HeatSimulator::HeatSimulator(std::shared_ptr<Ship> ship) : ship_(ship)
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
		ModulesVector hiSlot;
		ModulesVector medSlot;
		ModulesVector lowSlot;
		std::shared_ptr<Ship> ship = ship_.lock();
		if (!ship)
			return;
		hiSlot.reserve(ship->getNumberOfSlots(Module::SLOT_HI));
		medSlot.reserve(ship->getNumberOfSlots(Module::SLOT_HI));
		lowSlot.reserve(ship->getNumberOfSlots(Module::SLOT_HI));
		
		for (auto i: ship->getModules())
		{
			Module::Slot slot = i->getSlot();
			if (slot == Module::SLOT_HI)
				hiSlot.push_back(i);
			else if (slot == Module::SLOT_MED)
				medSlot.push_back(i);
			else if (slot == Module::SLOT_LOW)
				lowSlot.push_back(i);
		}
		if (hiSlot.size() > 0)
			simulate(hiSlot);
		if (medSlot.size() > 0)
			simulate(medSlot);
		if (lowSlot.size() > 0)
			simulate(lowSlot);
		isCalculated_ = true;
	}
}

void HeatSimulator::simulate(const ModulesVector& modules)
{
	states_.clear();

	std::shared_ptr<Ship> ship = ship_.lock();
	if (!ship)
		return;
	std::shared_ptr<Module> module = *modules.begin();
	Module::Slot slot = module->getSlot();
	float heatCapacity = 0;
	float heatGenerationMultiplier = ship->getAttribute(HEAT_GENERATION_MULTIPLIER_ATTRIBUTE_ID)->getValue();
	float heatAttenuation = 0;
	float heatGeneration = 0;
	float heatAbsorbtionRateModifier = 0;
	int numberOfSlots = ship->getNumberOfSlots(slot);
	int numberOfOnlineModules = 0;
	
	if (slot == Module::SLOT_HI)
	{
		heatCapacity = ship->getAttribute(HEAT_CAPACITY_HI_ATTRIBUTE_ID)->getValue() / 100.0f;
		heatAttenuation = ship->getAttribute(HEAT_ATTENUATION_HI_ATTRIBUTE_ID)->getValue();
	}
	else if (slot == Module::SLOT_MED)
	{
		heatCapacity = ship->getAttribute(HEAT_CAPACITY_MED_ATTRIBUTE_ID)->getValue() / 100.0f;
		heatAttenuation = ship->getAttribute(HEAT_ATTENUATION_MED_ATTRIBUTE_ID)->getValue();
	}
	else if (slot == Module::SLOT_LOW)
	{
		heatCapacity = ship->getAttribute(HEAT_CAPACITY_LOW_ATTRIBUTE_ID)->getValue() / 100.0f;
		heatAttenuation = ship->getAttribute(HEAT_ATTENUATION_LOW_ATTRIBUTE_ID)->getValue();
	}
	
	int n = (int) modules.size();
	std::vector<float> modulesHP(n);

	for (int i = 0; i < n; i++)
	{
		std::shared_ptr<Module> module = modules[i];
		modulesHP[i] = module->getAttribute(HP_ATTRIBUTE_ID)->getValue();
		Module::State state = module->getState();
		if (state >= Module::STATE_ONLINE)
			numberOfOnlineModules++;
		if (state == Module::STATE_OVERLOADED)
		{
			heatAbsorbtionRateModifier += module->getAttribute(HEAT_ABSORBTION_RATE_MODIFIER_ATTRIBUTE_ID)->getValue();
			int clipSize = module->getShots();

			std::shared_ptr<State> state = std::make_shared<State>();
			state->tNow = 0;
			state->duration = static_cast<int>(module->getCycleTime());
			state->clipSize = clipSize;
			state->shot = 0;
			state->reloadTime = static_cast<int>(module->getReloadTime());
			state->moduleIndex = i;
			state->heatDamage = module->getAttribute(HEAT_DAMAGE_ATTRIBUTE_ID)->getValue();
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
			
			float h = heat(static_cast<float>(tNow), heatCapacity, heatGeneration);
			int numberOfDeadModules = 0;
			for (int i = 0; i < n; i++)
			{
				if (modulesHP[i] > 0)
				{
					int range = abs(i - state->moduleIndex);
					modulesHP[i] -= damageProbability(h, range, numberOfOnlineModules, numberOfSlots, heatAttenuation) * state->heatDamage;
					if (modulesHP[i] <= 0.0)
					{
						modules[i]->setLifeTime(tNow / 1000.0f);
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

float HeatSimulator::heat(float t, float heatCapacity, float heatGeneration)
{
	return heatCapacity - exp(-t * heatGeneration);
}

float HeatSimulator::damageProbability(float h, int range, int numberOfOnlineModules, int numberOfSlots, float heatAttenuation)
{
	return (float) numberOfOnlineModules / (float) numberOfSlots * h * pow(heatAttenuation, range);
}
