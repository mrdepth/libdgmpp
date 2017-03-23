#pragma once
#include "Item.h"
#include "DamageVector.h"
#include "HostileTarget.h"

namespace dgmpp {
	
	class Drone : public Item
	{
	public:
		enum FighterSquadron
		{
			FIGHTER_SQUADRON_NONE = 0,
			FIGHTER_SQUADRON_HEAVY,
			FIGHTER_SQUADRON_LIGHT,
			FIGHTER_SQUADRON_SUPPORT
		};

		
        typedef std::invalid_argument BadDroneTargetException;

		Drone(std::shared_ptr<Engine> const& engine, TypeID typeID, int squadronTag, std::shared_ptr<Ship> const& owner = std::shared_ptr<Ship>(nullptr));
		virtual ~Drone(void);
		std::shared_ptr<Drone> shared_from_this() {
			return std::static_pointer_cast<Drone>(Item::shared_from_this());
		}
		
		void setTarget(std::shared_ptr<Ship> const& target = std::shared_ptr<Ship>(nullptr));
		void clearTarget();
		std::shared_ptr<Ship> getTarget();

		virtual bool dealsDamage();
		std::shared_ptr<Charge> getCharge();
		
		void setActive(bool active);
		bool isActive();
		bool isAssistance();
		bool isOffensive();

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		virtual void reset();

		FighterSquadron getSquadron();
		int getSquadronSize();
		
		int getSquadronTag();
		void setSquadronTag(int squadronTag);

		//Calculations
		
		virtual Float getCycleTime();
		
		DamageVector getVolley();
		DamageVector getDps(const HostileTarget& target = HostileTarget::defaultTarget);
		Float getMaxRange();
		Float getFalloff();
		Float getAccuracyScore();
		Float getMiningYield();
		Float getVelocity();
		
		virtual Item* ship();
		virtual Item* character();
		virtual Item* target();

		virtual std::insert_iterator<ModifiersList> getModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);

	protected:
		DamageVector volley_;
		DamageVector dps_;
		Float maxRange_;
		Float falloff_;
		Float trackingSpeed_;
		Float miningYield_;

		virtual void lazyLoad();
		virtual void calculateDamageStats();

	private:
		std::weak_ptr<Ship> target_;
		std::shared_ptr<Charge> charge_;
		FighterSquadron squadron_;
		int squadronTag_;

		bool isActive_;
		
	};
	
}
