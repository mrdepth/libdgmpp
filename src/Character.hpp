//
//  Character.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Skill.hpp"
#include "Structure.hpp"
#include "Ship.hpp"
#include "Implant.hpp"
#include "Booster.hpp"

namespace dgmpp {
	class Character: public Type {
	public:
		static std::unique_ptr<Character> Create() { return std::unique_ptr<Character>(new Character); }
		static std::unique_ptr<Character> Create (const Character& other) { return std::unique_ptr<Character>(new Character(other)); }
		
		const std::string& name() const noexcept { return name_(); }
		template<typename T>
		void name (T&& name) noexcept { name_(std::forward<T>(name)); }

		
		Ship* ship() const { return ship_(); }
		Ship* ship (std::unique_ptr<Ship>&& ship) { return ship_(std::move(ship)); }
		Ship* ship (TypeID typeID) { return ship(Ship::Create(typeID)); }
		Structure* structure() const { return structure_(); }
		Structure* structure (std::unique_ptr<Structure>&& structure) { return structure_(std::move(structure)); }
		Structure* structure (TypeID typeID) { return structure(Structure::Create(typeID)); }

		void setSkillLevels (int level) { setSkillLevels_(level); }
		
		Implant* add(std::unique_ptr<Implant>&& implant, bool replace = false) { return add_(std::move(implant), replace); }
		Booster* add(std::unique_ptr<Booster>&& booster, bool replace = false) { return add_(std::move(booster), replace); }
		Implant* addImplant(TypeID typeID, bool replace = false) { return add(Implant::Create(typeID), replace); }
		Booster* addBooster(TypeID typeID, bool replace = false) { return add(Booster::Create(typeID), replace); }
		void remove(Implant* implant) { remove_(implant); }
		void remove(Booster* booster) { remove_(booster); }
		
		std::vector<Skill*> skills() const { return skills_(); }
		std::vector<Implant*> implants() const { return implants_(); }
		std::vector<Booster*> boosters() const { return boosters_(); }
		
		Implant* implant (Implant::Slot slot) const noexcept { return implant_(slot); }
		Booster* booster (Booster::Slot slot) const noexcept { return booster_(slot); }
		
		Meter droneControlDistance() { return droneControlDistance_(); }


	protected:
		virtual void setEnabled_ (bool enabled) override;
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
		virtual void reset_() override;
	private:
		
		struct SlotCompare {
			template <typename A, typename B, typename = decltype(std::declval<A>()->slot()), typename = decltype(std::declval<B>()->slot())>
			bool operator() (const A& a, const B& b) const noexcept {
				return a->slot() < b->slot();
			}
			
			template <typename T, typename K, typename = std::enable_if_t<std::is_same_v<K, decltype(std::declval<T>()->slot())>>>
			bool operator() (const T& a, K b) const noexcept {
				return a->slot() < b;
			}
			
			template <typename T, typename K, typename = std::enable_if_t<std::is_same_v<K, decltype(std::declval<T>()->slot())>>>
			bool operator() (K a, const T& b) const noexcept {
				return a < b->slot();
			}
			
			typedef void is_transparent;
		};
		
		friend class Gang;
		friend class Ship;
		std::unique_ptr<Ship> shipValue_;
		std::map<TypeID, std::unique_ptr<Skill>> skillsMap_;
		
		std::set<std::unique_ptr<Implant>, SlotCompare> implantsSet_;
		std::set<std::unique_ptr<Booster>, SlotCompare> boostersSet_;
		std::string nameValue_;
		
		Character();
		Character (const Character& other);
		

		bool factorReload_() const noexcept;

		
		const std::string& name_() const noexcept { return nameValue_; }
		template<typename T>
		void name_ (T&& name) noexcept { nameValue_ = std::forward<T>(name); }
		
		
		Ship* ship_() const { return shipValue_.get(); }
		Ship* ship_ (std::unique_ptr<Ship>&& ship);
		Structure* structure_() const { return dynamic_cast<Structure*>(shipValue_.get()); }
		Structure* structure_ (std::unique_ptr<Structure>&& structure);

		void setSkillLevels_ (int level);
		
		Implant* add_(std::unique_ptr<Implant>&& implant, bool replace = false);
		Booster* add_(std::unique_ptr<Booster>&& booster, bool replace = false);
		void remove_(Implant* implant);
		void remove_(Booster* booster);
		
		std::vector<Skill*> skills_() const;
		std::vector<Implant*> implants_() const;
		std::vector<Booster*> boosters_() const;
		
		Implant* implant_ (Implant::Slot slot) const noexcept;
		Booster* booster_ (Booster::Slot slot) const noexcept;
		
		Meter droneControlDistance_();
	};
	

}
