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
		Gang(): Type(TypeID::none) { setEnabled(true); }
		Gang(const Gang& other);

		static std::unique_ptr<Gang> Create() { return std::unique_ptr<Gang>(new Gang); }
		static std::unique_ptr<Gang> Create(const Gang& other) { return std::unique_ptr<Gang>(new Gang(other)); }
		
		Character* add (std::unique_ptr<Character>&& pilot);
		Character* addPilot() { return add(Character::Create()); }
		
		void remove (Character* pilot);
		std::vector<Character*> pilots() const;
		
		virtual void setEnabled (bool enabled) override;
		
		bool factorReload()		const noexcept	{ return factorReload_; }
		void factorReload (bool factorReload) noexcept { factorReload_ = factorReload; }

		Area* area() const noexcept { return area_.get(); }
		Area* area(std::unique_ptr<Area>&& area);
		Area* area(TypeID typeID) { return area(Area::Create(typeID)); }

	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) noexcept override;
		
	private:
		friend class WarfareBuffEffect;
		std::list<std::unique_ptr<Character>> pilots_;
		bool factorReload_;
		std::unique_ptr<Area> area_;
	};
}
