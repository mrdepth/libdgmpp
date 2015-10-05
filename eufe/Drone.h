#pragma once
#include "Item.h"

namespace eufe {
	
	class Drone : public Item
	{
	public:
		//typedef boost::error_info<struct BadDroneTargetExceptionInfoTag, Ship*> BadDroneTargetExceptionInfo;
		//struct BadDroneTargetException : virtual boost::exception {};
        
        typedef std::invalid_argument BadDroneTargetException;

		virtual Environment getEnvironment();
		
		void setTarget(std::shared_ptr<Ship> target = nullptr);
		void clearTarget();
		std::shared_ptr<Ship> getTarget();

		bool dealsDamage();
		std::shared_ptr<Charge> getCharge();
		
		void setActive(bool active);
		bool isActive();
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		virtual void reset();

		//Calculations
		
		float getCycleTime();
		
		float getVolley();
		float getDps();
		float getMaxRange();
		float getFalloff();
		float getTrackingSpeed();

	protected:
		friend class Ship;
		Drone(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Ship> owner = nullptr);
		virtual ~Drone(void);

	private:
		std::weak_ptr<Ship> target_;
		std::shared_ptr<Charge> charge_;
		
		float volley_;
		float dps_;
		float maxRange_;
		float falloff_;
		float trackingSpeed_;

		bool isActive_;
		
		void calculateDamageStats();
	};
	
}