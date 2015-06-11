#pragma once
#include "Item.h"

namespace eufe {
	
	class Drone : public Item
	{
	public:
		//typedef boost::error_info<struct BadDroneTargetExceptionInfoTag, Ship*> BadDroneTargetExceptionInfo;
		//struct BadDroneTargetException : virtual boost::exception {};
        
        typedef std::invalid_argument BadDroneTargetException;

		Drone(Engine* engine, TypeID typeID, Ship* owner = NULL);
		Drone(const Drone& from);
		virtual ~Drone(void);
		
		virtual Environment getEnvironment();
		
		void setTarget(Ship* target = NULL);
		void clearTarget();
		Ship* getTarget();

		bool dealsDamage();
		Charge* getCharge();
		
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

	private:
		Ship* target_;
		Charge* charge_;
		
		float volley_;
		float dps_;
		float maxRange_;
		float falloff_;
		float trackingSpeed_;

		bool isActive_;
		
		void calculateDamageStats();
	};
	
}