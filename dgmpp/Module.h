#pragma once
#include "Item.h"
#include "HostileTarget.h"
#include "DamageVector.h"

#include "Type.hpp"

namespace dgmpp {
	
	class Module : public Item
	{
	public:

		enum class Slot
		{
			unknown = -1,
			none,
			hi,
			med,
			low,
			rig,
			subsystem,
			mode,
			service,
			starbaseStructure
		};

		enum class State
		{
			unknown = -1,
			offline,
			online,
			active,
			overloaded
		};
		
		enum class Hardpoint
		{
			none,
			launcher,
			turret
		};
		
		static std::shared_ptr<Module> dummy(std::shared_ptr<Engine> const& engine, std::shared_ptr<Item> const& owner, Module::Slot slot) {
			auto module = std::make_shared<Module>(engine, TypeID::none, owner);
			module->slot_ = slot;
			return module;
		}
		
		bool isDummy() {
			return getTypeID() == TypeID::none;
		}

		Module(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner = std::shared_ptr<Item>(nullptr));
		virtual ~Module(void);
		std::shared_ptr<Module> shared_from_this() {
			return std::static_pointer_cast<Module>(Item::shared_from_this());
		}

        typedef std::invalid_argument BadTargetException;
        typedef std::invalid_argument BadStateException;

		//virtual Attribute* getAttribute(TypeID attributeID);

		Slot getSlot();
		Hardpoint getHardpoint();
		int getSocket();
		virtual bool canHaveState(State state);
		State getState();
		State getPreferredState();
		void setState(State state);
		bool canBeOnline() {return canBeOnline_;};
		bool canBeActive() {return canBeActive_;};
		bool canBeOverloaded() {return canBeOverloaded_;};
		bool isAssistance();
		bool isOffensive();

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		virtual void reset();
		
		std::shared_ptr<Charge> setCharge(TypeID typeID);
		void clearCharge();
		std::shared_ptr<Charge> getCharge();
		const std::vector<GroupID>& getChargeGroups();
		int getChargeSize();
		bool canFit(std::shared_ptr<Charge> const& charge);
		bool requireTarget();
		void setTarget(std::shared_ptr<Ship> const& target = std::shared_ptr<Ship>(nullptr));
		void clearTarget();
		std::shared_ptr<Ship> getTarget();
		Float getReloadTime();
		
		//Calculations
		
		Float getCycleTime();
		Float getRawCycleTime();
		bool factorReload();
		void setFactorReload(bool factorReload);
		
		int getCharges();
		int getShots();
		Float getCapUse();
		Float getCpuUse();
		Float getPowerGridUse();
		Float getCalibrationUse();
		
		DamageVector getVolley();
		DamageVector getDps(const HostileTarget& target = HostileTarget::defaultTarget);
		//Float getDps(Float range, Float angularSpeed, Float targetSignature);
		Float getMaxRange();
		Float getFalloff();
		//Float getTrackingSpeed();
		Float getAccuracyScore();
		Float getSignatureResolution();
		Float getAngularVelocity(Float targetSignature, Float hitChance = 0.5);
		Float getMiningYield();
		
		Float getLifeTime();
		void setLifeTime(Float lifeTime);
		
		void setEnabled(bool enabled);
		bool isEnabled();

		virtual Item* ship();
		virtual Item* character();
		virtual Item* target();

		friend std::ostream& operator<<(std::ostream& os, Module& module);
	protected:
		State state_;
		State preferredState_;
		virtual void lazyLoad();

		friend class Ship;
		virtual void setInternalState(State state);

		
	private:
		bool canBeOnline_;
		bool canBeActive_;
		bool canBeOverloaded_;
		bool forceReload_;
		bool factorReload_;
		bool enabled_;
		Slot slot_;
		Hardpoint hardpoint_;
		std::shared_ptr<Charge> charge_;
		std::vector<GroupID> chargeGroups_;
		std::weak_ptr<Ship> target_;
		Float reloadTime_;
		int shots_;
		int socket_;
		
		DamageVector volley_;
		DamageVector dps_;
		Float maxRange_;
		Float falloff_;
		Float accuracyScore_;
		Float signatureResolution_;
		
		Float lifeTime_;
		Float miningYield_;
		
		void calculateDamageStats();
		
		friend class Ship;
	};
}

namespace dgmpp2 {
	class Charge;
	
	class Module: public Type {
	public:
		static std::unique_ptr<Module> Create (TypeID typeID) { return std::unique_ptr<Module>(new Module(typeID)); }

		enum class State {
			unknown = -1,
			offline,
			online,
			active,
			overloaded
		};

		bool isDummy() const { return metaInfo().typeID == TypeID::none; }
		bool canHaveState (State state) const;
		void state (State state);
		State state() const {return state_;};
		
		virtual void setEnabled (bool enabled) override;
		
		Charge* charge() const;
		void charge (std::unique_ptr<Charge> charge);
		
		bool canBeOnline()		const	{return flags_.canBeOnline;}
		bool canBeActive()		const;
		bool canBeOverloaded()	const	{return flags_.canBeOverloaded;}
		bool requireTarget()	const;

	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		
	private:
		State state_ = State::unknown;
		
		struct {
			bool canBeOnline : 1;
			bool canBeActive : 1;
			bool canBeOverloaded : 1;
			bool forceReload : 1;
			bool factorReload : 1;
			bool requireTarget : 1;
		} flags_;
		std::vector<GroupID> chargeGroups_;
		
		Module (TypeID typeID);
	};
}
