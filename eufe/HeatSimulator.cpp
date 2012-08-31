#include "HeatSimulator.h"
#include "Ship.h"
#include "Module.h"
#include "Attribute.h"
#include <math.h>

using namespace eufe;

class StateCompareFunction : public std::binary_function<const HeatSimulator::State*, const HeatSimulator::State*, bool>
{
public:
	bool operator() (const HeatSimulator::State* a, const HeatSimulator::State* b)
	{
		return a->tNow > b->tNow;
	}
};

HeatSimulator::HeatSimulator(Ship* ship) : ship_(ship)
{
}

HeatSimulator::~HeatSimulator(void)
{
	for (auto i: states_)
		delete i;
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
		hiSlot.reserve(ship_->getNumberOfSlots(Module::SLOT_HI));
		medSlot.reserve(ship_->getNumberOfSlots(Module::SLOT_HI));
		lowSlot.reserve(ship_->getNumberOfSlots(Module::SLOT_HI));
		
		for (auto i: ship_->getModules())
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
	{
		for (auto i: states_)
			delete i;
		states_.clear();
	}

	Module* module = *modules.begin();
	Module::Slot slot = module->getSlot();
	float heatCapacity = 0;
	float heatGenerationMultiplier = ship_->getAttribute(HEAT_GENERATION_MULTIPLIER_ATTRIBUTE_ID)->getValue();
	float heatAttenuation = 0;
	float heatGeneration = 0;
	float heatAbsorbtionRateModifier = 0;
	int numberOfSlots = ship_->getNumberOfSlots(slot);
	int numberOfOnlineModules = 0;
	
	if (slot == Module::SLOT_HI)
	{
		heatCapacity = ship_->getAttribute(HEAT_CAPACITY_HI_ATTRIBUTE_ID)->getValue() / 100.0;
		heatAttenuation = ship_->getAttribute(HEAT_ATTENUATION_HI_ATTRIBUTE_ID)->getValue();
	}
	else if (slot == Module::SLOT_MED)
	{
		heatCapacity = ship_->getAttribute(HEAT_CAPACITY_MED_ATTRIBUTE_ID)->getValue() / 100.0;
		heatAttenuation = ship_->getAttribute(HEAT_ATTENUATION_MED_ATTRIBUTE_ID)->getValue();
	}
	else if (slot == Module::SLOT_LOW)
	{
		heatCapacity = ship_->getAttribute(HEAT_CAPACITY_LOW_ATTRIBUTE_ID)->getValue() / 100.0;
		heatAttenuation = ship_->getAttribute(HEAT_ATTENUATION_LOW_ATTRIBUTE_ID)->getValue();
	}
	
	int n = (int) modules.size();
	std::vector<float> modulesHP(n);

	for (int i = 0; i < n; i++)
	{
		Module* module = modules[i];
		modulesHP[i] = module->getAttribute(HP_ATTRIBUTE_ID)->getValue();
		Module::State state = module->getState();
		if (state >= Module::STATE_ONLINE)
			numberOfOnlineModules++;
		if (state == Module::STATE_OVERLOADED)
		{
			heatAbsorbtionRateModifier += module->getAttribute(HEAT_ABSORBTION_RATE_MODIFIER_ATTRIBUTE_ID)->getValue();
			int clipSize = module->getShots();

			State *state = new State();
			state->tNow = 0;
			state->duration = module->getCycleTime();
			state->clipSize = clipSize;
			state->shot = 0;
			state->reloadTime = module->getReloadTime();
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
		State *state;

		while (1)
		{
			state = states_.front();
			std::pop_heap(states_.begin(), states_.end(), StateCompareFunction());
			states_.pop_back();

			tNow = state->tNow;
			
			float h = heat(tNow, heatCapacity, heatGeneration);
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

float HeatSimulator::heat(float t, float heatCapacity, float heatGeneration)
{
	return heatCapacity - exp(-t * heatGeneration);
}

float HeatSimulator::damageProbability(float h, int range, int numberOfOnlineModules, int numberOfSlots, float heatAttenuation)
{
	return (float) numberOfOnlineModules / (float) numberOfSlots * h * pow(heatAttenuation, range);
}
