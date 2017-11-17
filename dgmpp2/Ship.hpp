//
//  Ship.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Type.hpp"
#include "Module.hpp"
#include "Drone.hpp"
#include "Capacitor.hpp"

namespace dgmpp2 {
	class Module;
	
	class Ship: public Type {
	public:
//		using Position = std::vector<Module*>::const_iterator;
		using ModulesContainer = std::vector<Module*>;
		using DronesContainer = TuplesSet<TypeID, Drone::SquadronTag, Drone*>;
		
		template <typename T>
		struct CannotFit: public std::runtime_error {
			CannotFit(std::unique_ptr<T> type): type(std::move(type)), std::runtime_error("Cannot fit") {}
			std::unique_ptr<T> type;
		};
		
		static std::unique_ptr<Ship> Create (TypeID typeID) { return std::unique_ptr<Ship>(new Ship(typeID)); }
		
		Module* add (std::unique_ptr<Module> module, bool forced = false, Module::Socket socket = Module::anySocket);
		Drone* add (std::unique_ptr<Drone> drone, Drone::SquadronTag squadronTag = Drone::anySquadronTag);
		void remove (Module* module);
		void remove (Drone* drone);
		bool canFit (Module* module);
		bool canFit (Drone* drone);
		slice<ModulesContainer::const_iterator> modules (Module::Slot slot) const;
		const ModulesContainer& modules () const {return modules_;}
		const DronesContainer& drones () const {return drones_;}
		
		std::vector<CategoryID> supportedDroneCategories();
		
		size_t totalSlots (Module::Slot slot);
		size_t freeSlots (Module::Slot slot) {return totalSlots(slot) - usedSlots(slot);}
		size_t usedSlots (Module::Slot slot) {return modules(slot).size();}
		
		size_t totalHardpoints (Module::Hardpoint hardpoint);
		size_t freeHardpoints (Module::Hardpoint hardpoint);
		size_t usedHardpoints (Module::Hardpoint hardpoint);
		
		Capacitor& capacitor() { return capacitor_; }
		
		int rigSize() { return static_cast<int>((*this)[AttributeID::rigSize]->value()); }
		
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		virtual void reset() override;
		
		const std::list<Module*>& projectedModules() const { return projectedModules_; }
		const std::list<Drone*>& projectedDrones() const { return projectedDrones_; }

	private:
		friend class Character;
		friend class Capacitor;
		
		Ship (TypeID typeID): Type(typeID), capacitor_(*this) {};
		
		ModulesContainer modules_;
		DronesContainer drones_;
		
		std::list<Module*> projectedModules_;
		std::list<Drone*> projectedDrones_;
		
		Capacitor capacitor_;

	};
}
