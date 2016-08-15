#include "CapacitorSimulator.h"
#include <math.h>
#include <functional>
#include <algorithm>
#include "Ship.h"
#include "Module.h"
#include "Drone.h"
#include "Attribute.h"

using namespace dgmpp;

static const float CAPACITOR_PEAK_RECHARGE = sqrtf(0.25);

class StateCompareFunction : public std::binary_function<std::shared_ptr<const CapacitorSimulator::State> const&, std::shared_ptr<const CapacitorSimulator::State> const&, bool>
{
public:
	bool operator() (std::shared_ptr<const CapacitorSimulator::State> const& a, std::shared_ptr<const CapacitorSimulator::State> const& b)
	{
		return a->tNow > b->tNow;
	}
};

CapacitorSimulator::CapacitorSimulator(std::shared_ptr<Ship> const& ship, bool reload, int maxTime) : ship_(ship), reload_(reload), maxTime_(maxTime), isCalculated_(false), capacitorCapacity_(0), capacitorRecharge_(0), iterations_(0)
{
}

CapacitorSimulator::~CapacitorSimulator(void)
{
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
		states_.clear();
	}
	
	std::shared_ptr<Ship> ship = ship_.lock();
	if (!ship)
		return;
	
	capacitorCapacity_ = ship->getAttribute(CAPACITOR_CAPACITY_ATTRIBUTE_ID)->getValue();
	capacitorRecharge_ = ship->getAttribute(RECHARGE_RATE_ATTRIBUTE_ID)->getValue();
	capUsed_ = 0;
	bool isDisallowedAssistance = ship->isDisallowedAssistance();
	bool isDisallowedOffensiveModifiers = ship->isDisallowedOffensiveModifiers();
	
	capRecharge_ = 10.0f / (capacitorRecharge_ / 1000.0f) * CAPACITOR_PEAK_RECHARGE * (1 - CAPACITOR_PEAK_RECHARGE) * capacitorCapacity_;
	
	std::list<std::shared_ptr<Module>> drains;
	std::list<std::shared_ptr<Drone>> drainDrones;
	for (const auto& i: ship->getModules())
	{
		if (i->getState() >= Module::STATE_ACTIVE)
			drains.push_back(i);
	}
	
	for (const auto& i: ship->getProjectedModules())
	{
		auto module = i.lock();
		if (module && module->getState() >= Module::STATE_ACTIVE)
			drains.push_back(module);
	}
	
	if (!isDisallowedOffensiveModifiers)
	{
		for (const auto& i: ship->getProjectedDrones())
		{
			auto drone = i.lock();
			if (drone && drone->hasEffect(ENERGY_DESTABILIZATION_NEW_EFFECT_ID))
				drainDrones.push_back(drone);
		}
	}
	
	states_.reserve(drains.size());
	std::make_heap(states_.begin(), states_.end(), StateCompareFunction());

	period_ = 1;
	
	bool disablePeriod = false;
	
	for (const auto& module: drains)
	{
		bool projected = module->getOwner() != ship;
		int duration = static_cast<int>(module->getCycleTime());
		int clipSize = module->getShots();
		float capNeed = 0;
		
		if (duration == 0)
			continue;

		if (projected)
		{
			if (module->hasEffect(ENERGY_NOSFERATU_FALLOFF))
				capNeed = static_cast<float>(module->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID)->getValue());
			else if (module->hasEffect(ENERGY_DESTABILIZATION_NEW_EFFECT_ID))
				capNeed = static_cast<float>(module->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID)->getValue());
			else if (module->hasEffect(ENERGY_TRANSFER_EFFECT_ID))
				capNeed = static_cast<float>(-module->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID)->getValue());
		}
		else
			capNeed = module->getCapUse() * module->getCycleTime() / 1000.0f;
		
		if (capNeed > 0)
		{
			if (projected && isDisallowedOffensiveModifiers)
				continue;
			capUsed_ += capNeed / (duration / 1000.0f);
		}
		else if (capNeed < 0)
		{
			if (projected && isDisallowedAssistance)
				continue;
			capRecharge_ -= capNeed / (duration / 1000.0f);
		}
		else
			continue;
		
		period_ = lcm(period_, duration);
		
		if (!reload_ && capNeed > 0)
			clipSize = 0;
		
		if (clipSize)
			disablePeriod = true;
		
		std::shared_ptr<State> state = std::make_shared<State>();
		state->tNow = 0;
		state->reactivationTime = module->hasAttribute(MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID) ? module->getAttribute(MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID)->getValue() : 0;
		state->duration = module->getRawCycleTime() + (state->reactivationTime);
		state->capNeed = capNeed;
		state->clipSize = clipSize;
		state->shot = 0;
		state->reloadTime = static_cast<int>(module->getReloadTime());
		states_.push_back(state);
		std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
	}
	
	for (const auto& drone: drainDrones)
	{
		int duration = static_cast<int>(drone->getCycleTime());
		float capNeed = capNeed = drone->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID)->getValue();
		capUsed_ += static_cast<float>(capNeed / (duration / 1000.0));
		period_ = lcm(period_, duration);
		
		std::shared_ptr<State> state = std::make_shared<State>();
		state->tNow = 0;
		state->reactivationTime = 0;
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
		float tau = capacitorRecharge_ / 5.0f;
		float capWrap = capacitorCapacity_;
		float capLowest = capacitorCapacity_;
		float capLowestPre = capacitorCapacity_;
		float cap = capacitorCapacity_;
		int tWrap = period_;
		int tNow = 0;
		int tLast = 0;
		std::shared_ptr<State> state;
		iterations_ = 0;
		
		while (1) {
			state = states_.front();
			std::pop_heap(states_.begin(), states_.end(), StateCompareFunction());
			states_.pop_back();
			
			tNow = state->tNow;
			if (tNow > maxTime_)
				break;
			
			float s((1.0f + (sqrtf(cap / capacitorCapacity_) - 1.0f) * expf((tLast - state->tNow) / tau)));
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
			
			tLast = tNow;

			if (cap < capLowest) {
				if (cap < 0.0)
					break;
				capLowest = cap;
			}
			
			tNow += state->duration;
			state->shot++;
			
			if (state->clipSize) {
				if (state->shot % state->clipSize == 0) {
					state->shot = 0;
					tNow += std::max(state->reloadTime, state->reactivationTime);
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
		
		for (const auto& i: states_)
			avgDrain += i->capNeed / i->duration;
		
		float a = - (2.0f * avgDrain * tau - capacitorCapacity_) / capacitorCapacity_;
		if (a < 0.0)
			capStableEVE_ = 0;
		else {
			float t = (1.0f + sqrtf(a));
			capStableEVE_ = 0.25f * t * t;	
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

int CapacitorSimulator::gcd(int a, int b) {
    return b?gcd(b,a%b):a;
}

int CapacitorSimulator::lcm(int a, int b) {
    return a/gcd(a,b) * b;
}
