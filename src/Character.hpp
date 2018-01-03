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
		
		const std::string& name() const noexcept { return name_; }
		template<typename T>
		void name (T&& name) noexcept { name_ = std::forward<T>(name); }

		
		Ship* ship() const { return ship_(); }
		Ship* ship (std::unique_ptr<Ship>&& ship) { return ship_(std::move(ship)); }
		Ship* ship (TypeID typeID) { return ship_(Ship::Create(typeID)); }
		Structure* structure() const { return structure_(); }
		Structure* structure (std::unique_ptr<Structure>&& structure) { return structure_(std::move(structure)); }
		Structure* structure (TypeID typeID) { return structure_(Structure::Create(typeID)); }

		void setSkillLevels (int level);
		
		Implant* add(std::unique_ptr<Implant>&& implant, bool replace = false);
		Booster* add(std::unique_ptr<Booster>&& booster, bool replace = false);
		Implant* addImplant(TypeID typeID, bool replace = false) { return add(Implant::Create(typeID), replace); }
		Booster* addBooster(TypeID typeID, bool replace = false) { return add(Booster::Create(typeID), replace); }
		void remove(Implant* implant);
		void remove(Booster* booster);
		
		std::vector<Skill*> skills() const;
		std::vector<Implant*> implants() const;
		std::vector<Booster*> boosters() const;
		
		Implant* implant (Implant::Slot slot) const noexcept;
		Booster* booster (Booster::Slot slot) const noexcept;
		
		Meter droneControlDistance();


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
		std::map<TypeID, std::unique_ptr<Skill>> skills_;
		
		std::set<std::unique_ptr<Implant>, SlotCompare> implants_;
		std::set<std::unique_ptr<Booster>, SlotCompare> boosters_;
		std::string name_;
		
		Character();
		Character (const Character& other);
		
		Ship* ship_() const { return shipValue_.get(); }
		Ship* ship_ (std::unique_ptr<Ship>&& ship);
		Structure* structure_() const { return dynamic_cast<Structure*>(shipValue_.get()); }
		Structure* structure_ (std::unique_ptr<Structure>&& structure);

		bool factorReload_() const noexcept;

	};
	

}
