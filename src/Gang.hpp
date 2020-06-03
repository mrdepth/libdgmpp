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
        virtual ~Gang();

//		static std::unique_ptr<Gang> Create() { return std::unique_ptr<Gang>(new Gang); }
//		static std::unique_ptr<Gang> Create(const Gang& other) { return std::unique_ptr<Gang>(new Gang(other)); }
		
		void add(const std::shared_ptr<Character>& pilot) { LOCK(this); add_(pilot); }
		
		void remove (Character* pilot) { LOCK(this); remove_(pilot); }
		const std::list<std::shared_ptr<Character>>& pilots() const { LOCK(this); return pilots_(); }
		
		bool factorReload()		const noexcept	{ LOCK(this); return factorReload_(); }
		void factorReload (bool factorReload) noexcept { LOCK(this); factorReload_(factorReload); }

		std::shared_ptr<Area> area() const noexcept { LOCK(this); return area_(); }
        
		void area(const std::shared_ptr<Area>& area) { LOCK(this); return area_(area); }
//		void area(TypeID typeID) { return area(Area::Create(typeID)); }

	protected:
		virtual void setEnabled_ (bool enabled) override;
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
		
	private:
		friend class WarfareBuffEffect;
		friend class Character;
		std::list<std::shared_ptr<Character>> pilotsList_;
		bool factorReloadValue_ = false;
		std::shared_ptr<Area> areaValue_;

		void add_ (const std::shared_ptr<Character>& pilot);
		
		void remove_ (Character* pilot);
        const std::list<std::shared_ptr<Character>>& pilots_() const { return pilotsList_; }

		bool factorReload_() const noexcept	{ return factorReloadValue_; }
		void factorReload_ (bool factorReload) noexcept;
		
		std::shared_ptr<Area> area_() const noexcept { return areaValue_; }
		void area_(const std::shared_ptr<Area>& area);

	};
}
