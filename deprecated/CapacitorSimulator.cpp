#include "CapacitorSimulator.h"
#include <cmath>
#include <functional>
#include <algorithm>
#include "Ship.h"
#include "Module.h"
#include "Drone.h"
#include "Attribute.h"

using namespace dgmpp;

static const Float CAPACITOR_PEAK_RECHARGE = std::sqrt(0.25);

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

Float CapacitorSimulator::getCapLastsTime()
{
	if (!isCalculated_)
		run();
	
	if (isCapStable())
		return std::numeric_limits<Float>::infinity();
	else
	{
		return static_cast<Float>(time_ / 1000.0);
	}
}

Float CapacitorSimulator::getCapStableLevel()
{
	if (!isCalculated_)
		run();

	if (isCapStable())
	{
		Float capState = (capStableLow_ + capStableHigh_) / (2 * capacitorCapacity_);
		return std::min(capState, Float(1.0));
	}
	else
		return 0;
}

Float CapacitorSimulator::getCapUsed()
{
	if (!isCalculated_)
		run();
	return capUsed_;
}

Float CapacitorSimulator::getCapRecharge()
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
	
	capacitorCapacity_ = ship->getAttribute(AttributeID::capacitorCapacity)->getValue();
	capacitorRecharge_ = ship->getAttribute(AttributeID::rechargeRate)->getValue();
	
	capUsed_ = 0;
	bool isDisallowedAssistance = ship->isDisallowedAssistance();
	bool isDisallowedOffensiveModifiers = ship->isDisallowedOffensiveModifiers();
	
	capRecharge_ = 10.0 / (capacitorRecharge_ / 1000.0) * CAPACITOR_PEAK_RECHARGE * (1 - CAPACITOR_PEAK_RECHARGE) * capacitorCapacity_;
	
	std::list<std::shared_ptr<Module>> drains;
	std::list<std::shared_ptr<Drone>> drainDrones;
	for (const auto& i: ship->getModules())
	{
		if (i->getState() >= Module::State::active)
			drains.push_back(i);
	}
	
	for (const auto& i: ship->getProjectedModules())
	{
		auto module = i.lock();
		if (module && module->getState() >= Module::State::active)
			drains.push_back(module);
	}
	
	if (!isDisallowedOffensiveModifiers)
	{
		for (const auto& i: ship->getProjectedDrones())
		{
			auto drone = i.lock();
			if (drone && drone->hasEffect(EffectID::entityEnergyNeutralizerFalloff))
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
		int duration = static_cast<int>(module->getCycleTime() * 1000.0);
		int clipSize = module->getShots();
		Float capNeed = 0;
		
		if (duration == 0)
			continue;

		if (projected)
		{
			
			if (module->hasEffect(EffectID::energyNosferatuFalloff))
				capNeed = static_cast<Float>(module->getAttribute(AttributeID::powerTransferAmount)->getValue());
			else if (module->hasEffect(EffectID::energyNeutralizerFalloff))
				capNeed = static_cast<Float>(module->getAttribute(AttributeID::energyNeutralizerAmount)->getValue());
			else if (module->hasEffect(EffectID::shipModuleRemoteCapacitorTransmitter))
				capNeed = static_cast<Float>(-module->getAttribute(AttributeID::powerTransferAmount)->getValue());
		}
		else
			capNeed = module->getCapUse() * module->getCycleTime();
		
		if (capNeed > 0)
		{
			if (projected && isDisallowedOffensiveModifiers)
				continue;
			capUsed_ += capNeed / (duration / 1000.0);
		}
		else if (capNeed < 0)
		{
			if (projected && isDisallowedAssistance)
				continue;
			capRecharge_ -= capNeed / (duration / 1000.0);
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
		state->reactivationTime = module->hasAttribute(AttributeID::moduleReactivationDelay) ? module->getAttribute(AttributeID::moduleReactivationDelay)->getValue() : 0;
		state->duration = module->getRawCycleTime() * 1000 + state->reactivationTime;
		state->capNeed = capNeed;
		state->clipSize = clipSize;
		state->shot = 0;
		state->reloadTime = static_cast<int>(module->getReloadTime() * 1000);
		states_.push_back(state);
		std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
	}
	
	for (const auto& drone: drainDrones)
	{
		int duration = static_cast<int>(drone->getCycleTime() * 1000);
		Float capNeed = capNeed = drone->getAttribute(AttributeID::energyNeutralizerAmount)->getValue();
		capUsed_ += static_cast<Float>(capNeed / (duration / 1000.0));
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
		Float tau = capacitorRecharge_ / 5.0;
		Float capWrap = capacitorCapacity_;
		Float capLowest = capacitorCapacity_;
		Float capLowestPre = capacitorCapacity_;
		Float cap = capacitorCapacity_;
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
			
			Float s((1.0 + (std::sqrt(cap / capacitorCapacity_) - 1.0) * std::exp((tLast - state->tNow) / tau)));
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
					//tNow += std::max(state->reloadTime, state->reactivationTime);
					tNow += 10000;
				}
			}
			state->tNow = tNow;
			states_.push_back(state);
			std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
		}
		states_.push_back(state);
		std::push_heap(states_.begin(), states_.end(), StateCompareFunction());
		
		time_ = tLast;
		
		Float avgDrain = 0;
		
		for (const auto& i: states_)
			avgDrain += i->capNeed / i->duration;
		
		Float a = - (2.0 * avgDrain * tau - capacitorCapacity_) / capacitorCapacity_;
		if (a < 0.0)
			capStableEVE_ = 0;
		else {
			Float t = (1.0 + std::sqrt(a));
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

int CapacitorSimulator::gcd(int a, int b) {
    return b?gcd(b,a%b):a;
}

int CapacitorSimulator::lcm(int a, int b) {
    return a/gcd(a,b) * b;
}
