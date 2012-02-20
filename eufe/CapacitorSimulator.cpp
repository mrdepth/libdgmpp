#include "CapacitorSimulator.h"
#include <boost/math/common_factor.hpp>
#include <math.h>
#include <functional>
#include <algorithm>
#include "Ship.h"
#include "Module.h"
#include "Drone.h"
#include "Attribute.h"

using namespace eufe;

static const float CAPACITOR_PEAK_RECHARGE = sqrt(0.25);

class StateCompareFunction : public std::binary_function<const CapacitorSimulator::State*, const CapacitorSimulator::State*, bool>
{
public:
	bool operator() (const CapacitorSimulator::State* a, const CapacitorSimulator::State* b)
	{
		return a->tNow > b->tNow;
	}
};

CapacitorSimulator::CapacitorSimulator(Ship* ship, bool reload, int maxTime) : ship_(ship), reload_(reload), maxTime_(maxTime), isCalculated_(false), capacitorCapacity_(0), capacitorRecharge_(0), iterations_(0)
{
}

CapacitorSimulator::~CapacitorSimulator(void)
{
	StatesVector::iterator i, end = states_.end();
	for (i = states_.begin(); i != end; i++)
		delete *i;
	states_.clear();
}

void CapacitorSimulator::reset()
{
	isCalculated_ = false;
}

void CapacitorSimulator::setReload(bool reload)
{
	reload_ = reload;
	reset();
}

void CapacitorSimulator::setMaxTime(int maxTime)
{
	maxTime_ = maxTime;
	reset();
}

bool CapacitorSimulator::getReload()
{
	return reload_;
}

int CapacitorSimulator::getMaxTime()
{
	return maxTime_;
}

int CapacitorSimulator::getIterations()
{
	if (!isCalculated_)
		run();
	return iterations_;
}

bool CapacitorSimulator::isCapStable()
{
	if (!isCalculated_)
		run();
	return capStableLow_ + capStableHigh_ > 0;
}

float CapacitorSimulator::getCapLastsTime()
{
	if (!isCalculated_)
		run();
	
	if (isCapStable())
		return std::numeric_limits<float>::infinity();
	else
	{
		return static_cast<float>(time_ / 1000.0);
	}
}

float CapacitorSimulator::getCapStableLevel()
{
	if (!isCalculated_)
		run();

	if (isCapStable())
	{
		float capState = (capStableLow_ + capStableHigh_) / (2 * capacitorCapacity_);
		return std::min(capState, float(1.0));
	}
	else
		return 0;
}

float CapacitorSimulator::getCapUsed()
{
	if (!isCalculated_)
		run();
	return capUsed_;
}

float CapacitorSimulator::getCapRecharge()
{
	if (!isCalculated_)
		run();
	return capRecharge_;
}


void CapacitorSimulator::internalReset()
{
	{
		StatesVector::iterator i, end = states_.end();
		for (i = states_.begin(); i != end; i++)
			delete *i;
		states_.clear();
	}
	
	capacitorCapacity_ = ship_->getAttribute(CAPACITOR_CAPACITY_ATTRIBUTE_ID)->getValue();
	capacitorRecharge_ = ship_->getAttribute(RECHARGE_RATE_ATTRIBUTE_ID)->getValue();
	capUsed_ = 0;
	bool isDisallowedAssistance = ship_->isDisallowedAssistance();
	bool isDisallowedOffensiveModifiers = ship_->isDisallowedOffensiveModifiers();
	
	capRecharge_ = 10.0 / (capacitorRecharge_ / 1000.0) * CAPACITOR_PEAK_RECHARGE * (1 - CAPACITOR_PEAK_RECHARGE) * capacitorCapacity_;
	
	std::list<Module*> drains;
	std::list<Drone*> drainDrones;
	{
		ModulesList::const_iterator i, end = ship_->getModules().end();
		for (i = ship_->getModules().begin(); i != end; i++)
		{
			if ((*i)->getState() >= Module::STATE_ACTIVE)
				drains.push_back((*i).get());
		}
		
		ProjectedModulesList::const_iterator j, endj = ship_->getProjectedModules().end();
		for (j = ship_->getProjectedModules().begin(); j != endj; j++)
		{
			if ((*j)->getState() >= Module::STATE_ACTIVE)
				drains.push_back((*j));
		}

		if (!isDisallowedOffensiveModifiers)
		{
			ProjectedDronesList::const_iterator k, endk = ship_->getProjectedDrones().end();
			for (k = ship_->getProjectedDrones().begin(); k != endk; k++)
			{
				if ((*k)->hasEffect(ENERGY_DESTABILIZATION_NEW_EFFECT_ID))
					drainDrones.push_back((*k));
			}
		}
	}
	
	states_.reserve(drains.size());
	std::make_heap(states_.begin(), states_.end(), StateCompareFunction());

	period_ = 1;
	
	bool disablePeriod = false;
	
	std::list<Module*>::iterator i, end = drains.end();
	for (i = drains.begin(); i != end; i++)
	{
		Module* module = *i;
		bool projected = module->getOwner() != ship_;
		int duration = static_cast<int>(module->getCycleTime());
		int clipSize = module->getShots();
		float capNeed = 0;
		
		if (projected)
		{
			if (module->hasEffect(LEECH_EFFECT_ID))
				capNeed = static_cast<float>(module->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID)->getValue());
			else if (module->hasEffect(ENERGY_DESTABILIZATION_NEW_EFFECT_ID))
				capNeed = static_cast<float>(module->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID)->getValue());
			else if (module->hasEffect(ENERGY_TRANSFER_EFFECT_ID))
				capNeed = static_cast<float>(-module->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID)->getValue());
		}
		else
			capNeed = module->getCapUse() * module->getCycleTime() / 1000.0;
		
		if (capNeed > 0)
		{
			if (projected && isDisallowedOffensiveModifiers)
				continue;
			capUsed_ += capNeed / (duration / 1000.0);
		}
		else
		{
			if (projected && isDisallowedAssistance)
				continue;
			capRecharge_ -= capNeed / (duration / 1000.0);
		}
		
		period_ = boost::math::lcm(period_, duration);
		
		if (!reload_ && capNeed > 0)
			clipSize = 0;
		
		if (clipSize)
			disablePeriod = true;
		
		State *state = new State();
		state->tNow = 0;
		state->duration = duration;
		state->capNeed = capNeed;
		state->clipSize = clipSize;
		state->shot = 0;
		state->reloadTime = module->getReloadTime();
		states_.push_back(state);
		std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
	}
	
	std::list<Drone*>::iterator j, endj = drainDrones.end();
	for (j = drainDrones.begin(); j != endj; j++)
	{
		Drone* drone = *j;
		int duration = static_cast<int>(drone->getCycleTime());
		float capNeed = capNeed = drone->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID)->getValue();
		capUsed_ += static_cast<float>(capNeed / (duration / 1000.0));
		period_ = boost::math::lcm(period_, duration);
		
		State *state = new State();
		state->tNow = 0;
		state->duration = duration;
		state->capNeed = capNeed;
		state->clipSize = 0;
		state->shot = 0;
		state->reloadTime = 0;
		states_.push_back(state);
		std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
	}
	
	if (disablePeriod)
		period_ = maxTime_;
}

void CapacitorSimulator::run()
{
	internalReset();
	
	if (states_.size() > 0)
	{
		float tau = capacitorRecharge_ / 5.0;
		float capWrap = capacitorCapacity_;
		float capLowest = capacitorCapacity_;
		float capLowestPre = capacitorCapacity_;
		float cap = capacitorCapacity_;
		int tWrap = period_;
		int tNow = 0;
		int tLast = 0;
		State *state;
		iterations_ = 0;
		
		while (1) {
			state = states_.front();
			std::pop_heap(states_.begin(), states_.end(), StateCompareFunction());
			states_.pop_back();
			
			tNow = state->tNow;
			if (tNow > maxTime_)
				break;
			
			float s((1.0 + (sqrt(cap / capacitorCapacity_) - 1.0) * exp((tLast - state->tNow) / tau)));
			cap = s * s *capacitorCapacity_;
			if (tNow != tLast) {
				if (cap < capLowestPre)
					capLowestPre = cap;
				if (tNow == tWrap) {
					if (cap >= capWrap)
						break;
					capWrap = cap;
					tWrap += period_;
				}
			}
			
			cap -= state->capNeed;
			cap = std::min(cap, capacitorCapacity_);
			
			iterations_++;
			
			if (cap < capLowest) {
				if (cap < 0.0)
					break;
				capLowest = cap;
			}
			
			tLast = tNow;
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
		states_.push_back(state);
		std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
		
		time_ = tLast;
		
		float avgDrain = 0;
		
		StatesVector::iterator i, end = states_.end();
		for (i = states_.begin(); i != end; i++)
			avgDrain += (*i)->capNeed / (*i)->duration;
		
		float a = - (2.0 * avgDrain * tau - capacitorCapacity_) / capacitorCapacity_;
		if (a < 0.0)
			capStableEVE_ = 0;
		else {
			float t = (1.0 + sqrt(a));
			capStableEVE_ = 0.25 * t * t;	
		}
		
		if (cap > 0.0) {
			capStableLow_ = capLowest;
			capStableHigh_ = capLowestPre;
		}
		else
			capStableLow_ = capStableHigh_ = 0.0;
	}
	else
	{
		time_ = 0;
		capStableEVE_ = capStableLow_ = capStableHigh_ = capacitorCapacity_;
	}
	isCalculated_ = true;
}
