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
        Character();
        Character (const Character& other);
        virtual ~Character();

		const std::string& name() const noexcept { LOCK(this); return name_(); }
		template<typename T>
		void name (T&& name) noexcept { LOCK(this); name_(std::forward<T>(name)); }

		
		std::shared_ptr<Ship> ship() const { LOCK(this); return ship_(); }
		void ship (const std::shared_ptr<Ship>& ship) { LOCK(this); return ship_(ship); }

		void setSkillLevels (int level) { LOCK(this); setSkillLevels_(level); }
		
		void add(const std::shared_ptr<Implant>& implant, bool replace = false) { LOCK(this); add_(implant, replace); }
		void add(const std::shared_ptr<Booster>& booster, bool replace = false) { LOCK(this); add_(booster, replace); }
//		Implant* addImplant(TypeID typeID, bool replace = false) { return add(Implant::Create(typeID), replace); }
//		Booster* addBooster(TypeID typeID, bool replace = false) { return add(Booster::Create(typeID), replace); }
		void remove(Implant* implant) { LOCK(this); remove_(implant); }
		void remove(Booster* booster) { LOCK(this); remove_(booster); }
		
		std::vector<std::shared_ptr<Skill>> skills() const { LOCK(this); return skills_(); }
		std::vector<std::shared_ptr<Implant>> implants() const { LOCK(this); return implants_(); }
		std::vector<std::shared_ptr<Booster>> boosters() const { LOCK(this); return boosters_(); }
		
		std::shared_ptr<Implant> implant (Implant::Slot slot) const noexcept { LOCK(this); return implant_(slot); }
		std::shared_ptr<Booster> booster (Booster::Slot slot) const noexcept { LOCK(this); return booster_(slot); }
		
		Meter droneControlDistance() { LOCK(this); return droneControlDistance_(); }


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
		std::shared_ptr<Ship> shipValue_;
		std::map<TypeID, std::shared_ptr<Skill>> skillsMap_;
		
		std::set<std::shared_ptr<Implant>, SlotCompare> implantsSet_;
		std::set<std::shared_ptr<Booster>, SlotCompare> boostersSet_;
		std::string nameValue_;
		
		bool factorReload_() const noexcept;

		
		const std::string& name_() const noexcept { return nameValue_; }
		template<typename T>
		void name_ (T&& name) noexcept { nameValue_ = std::forward<T>(name); }
		
		
		std::shared_ptr<Ship> ship_() const { return shipValue_; }
		void ship_ (const std::shared_ptr<Ship>& ship);

		void setSkillLevels_ (int level);
		
		void add_(const std::shared_ptr<Implant>& implant, bool replace = false);
		void add_(const std::shared_ptr<Booster>& booster, bool replace = false);
		void remove_(Implant* implant);
		void remove_(Booster* booster);
		
		std::vector<std::shared_ptr<Skill>> skills_() const;
		std::vector<std::shared_ptr<Implant>> implants_() const;
		std::vector<std::shared_ptr<Booster>> boosters_() const;
		
		std::shared_ptr<Implant> implant_ (Implant::Slot slot) const noexcept;
		std::shared_ptr<Booster> booster_ (Booster::Slot slot) const noexcept;
		
		Meter droneControlDistance_();
	};
	

}
