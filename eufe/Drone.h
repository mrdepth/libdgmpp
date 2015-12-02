#pragma once
#include "Item.h"
#include "DamageVector.h"
#include "HostileTarget.h"

namespace eufe {
	
	class Drone : public Item
	{
	public:
		//typedef boost::error_info<struct BadDroneTargetExceptionInfoTag, Ship*> BadDroneTargetExceptionInfo;
		//struct BadDroneTargetException : virtual boost::exception {};
        
        typedef std::invalid_argument BadDroneTargetException;

		Drone(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Ship> owner = nullptr);
		virtual ~Drone(void);
		std::shared_ptr<Drone> shared_from_this() {
			return std::static_pointer_cast<Drone>(Item::shared_from_this());
		}
		virtual Environment getEnvironment();
		
		void setTarget(std::shared_ptr<Ship> target = nullptr);
		void clearTarget();
		std::shared_ptr<Ship> getTarget();

		bool dealsDamage();
		std::shared_ptr<Charge> getCharge();
		
		void setActive(bool active);
		bool isActive();
		bool isAssistance();
		bool isOffensive();

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		virtual void reset();

		//Calculations
		
		float getCycleTime();
		
		DamageVector getVolley();
		DamageVector getDps(const HostileTarget& target = HostileTarget::defaultTarget);
		float getMaxRange();
		float getFalloff();
		float getTrackingSpeed();

	protected:
		virtual void lazyLoad();

	private:
		std::weak_ptr<Ship> target_;
		std::shared_ptr<Charge> charge_;
		
		DamageVector volley_;
		DamageVector dps_;
		float maxRange_;
		float falloff_;
		float trackingSpeed_;

		bool isActive_;
		
		void calculateDamageStats();
	};
	
}