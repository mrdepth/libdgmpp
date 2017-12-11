//
//  Character.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Skill.hpp"
#include "Ship.hpp"
#include "Implant.hpp"
#include "Booster.hpp"

namespace dgmpp {
	class Character: public Type {
	public:
		static std::unique_ptr<Character> Create() { return std::unique_ptr<Character>(new Character); }
		
		Ship* ship() const { return ship_.get(); }
		Ship* ship (std::unique_ptr<Ship> ship);
		Ship* ship (TypeID typeID) { return ship(Ship::Create(typeID)); }
		
		void setSkillLevels (int level);
		
		Implant* add(std::unique_ptr<Implant> implant, bool replace = false);
		Booster* add(std::unique_ptr<Booster> booster, bool replace = false);
		Implant* addImplant(TypeID typeID, bool replace = false) { return add(Implant::Create(typeID), replace); }
		Booster* addBooster(TypeID typeID, bool replace = false) { return add(Booster::Create(typeID), replace); }
		void remove(Implant* implant);
		void remove(Booster* booster);
		
		std::vector<Implant*> implants() const;
		std::vector<Booster*> boosters() const;
		
		Implant* implant (Implant::Slot slot) const noexcept;
		Booster* booster (Booster::Slot slot) const noexcept;

		virtual void setEnabled (bool enabled) override;
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) noexcept override;
		virtual void reset() override;
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
		std::unique_ptr<Ship> ship_;
		std::map<TypeID, std::unique_ptr<Skill>> skills_;
		
		std::set<std::unique_ptr<Implant>, SlotCompare> implants_;
		std::set<std::unique_ptr<Booster>, SlotCompare> boosters_;
		
		Character();
	};
	

}
