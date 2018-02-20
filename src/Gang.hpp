//
//  Gang.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Character.hpp"

namespace dgmpp {
	class Character;
	
	class Gang final: public Type {
	public:
		Gang(): Type(TypeID::none) { setEnabled_(true); }
		Gang(const Gang& other);

		static std::unique_ptr<Gang> Create() { return std::unique_ptr<Gang>(new Gang); }
		static std::unique_ptr<Gang> Create(const Gang& other) { return std::unique_ptr<Gang>(new Gang(other)); }
		
		Character* add (std::unique_ptr<Character>&& pilot) { LOCK(this); return add_(std::move(pilot)); }
		Character* addPilot() { return add(Character::Create()); }
		
		void remove (Character* pilot) { LOCK(this); remove_(pilot); }
		std::vector<Character*> pilots() const { LOCK(this); return pilots_(); }
		
		bool factorReload()		const noexcept	{ LOCK(this); return factorReload_(); }
		void factorReload (bool factorReload) noexcept { LOCK(this); factorReload_(factorReload); }

		Area* area() const noexcept { LOCK(this); return area_(); }
		Area* area(std::unique_ptr<Area>&& area) { LOCK(this); return area_(std::move(area)); }
		Area* area(TypeID typeID) { return area(Area::Create(typeID)); }

	protected:
		virtual void setEnabled_ (bool enabled) override;
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
		
	private:
		friend class WarfareBuffEffect;
		friend class Character;
		std::list<std::unique_ptr<Character>> pilotsList_;
		bool factorReloadValue_ = false;
		std::unique_ptr<Area> areaValue_;

		Character* add_ (std::unique_ptr<Character>&& pilot);
		
		void remove_ (Character* pilot);
		std::vector<Character*> pilots_() const;

		bool factorReload_() const noexcept	{ return factorReloadValue_; }
		void factorReload_ (bool factorReload) noexcept;// { factorReloadValue_ = factorReload; }
		
		Area* area_() const noexcept { return areaValue_.get(); }
		Area* area_(std::unique_ptr<Area>&& area);

	};
}
