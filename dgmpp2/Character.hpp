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

namespace dgmpp2 {
	class Character: public Type {
	public:
		struct SlotCompare {
			template <typename T>
			bool operator() (const T& a, const T& b) {
				return a->slot() < b->slot();
			}

			template <typename T, typename K, typename = std::enable_if_t<std::is_scalar_v<K>>>
			bool operator() (const T& a, K b) {
				return a->slot() < b;
			}

			template <typename T, typename K, typename = std::enable_if_t<std::is_scalar_v<K>>>
			bool operator() (K a, const T& b) {
				return a < b->slot();
			}

			typedef void is_transparent;
		};

		using ImplantsContainer = std::set<std::unique_ptr<Implant>, SlotCompare>;
		using BoostersContainer = std::set<std::unique_ptr<Booster>, SlotCompare>;
		
		static std::unique_ptr<Character> Create() { return std::unique_ptr<Character>(new Character); }
		Ship* setShip (std::unique_ptr<Ship> ship);
		void setSkillLevels (int level);
		
		Implant* add(std::unique_ptr<Implant> implant, bool replace = false);
		Booster* add(std::unique_ptr<Booster> booster, bool replace = false);
		void remove(Implant* implant);
		void remove(Booster* booster);
		
		const ImplantsContainer& implants() const { return implants_; }
		const BoostersContainer& boosters() const { return boosters_; }
		
		Implant* implant (Implant::Slot slot) const;
		Booster* booster (Booster::Slot slot) const;

		virtual void setEnabled (bool enabled) override;
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		virtual void reset() override;
	private:
		friend class Gang;
		std::unique_ptr<Ship> ship_;
		std::map<TypeID, std::unique_ptr<Skill>> skills_;
		
		ImplantsContainer implants_;
		BoostersContainer boosters_;
		
		Character();
	};
	

}
