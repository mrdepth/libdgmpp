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
		Gang() : Type(TypeID::none) { setEnabled(true); }

		static std::unique_ptr<Gang> Create() { return std::unique_ptr<Gang>(new Gang); }
		
		Character* add (std::unique_ptr<Character>&& pilot);
		Character* addPilot() { return add(Character::Create()); }
		
		void remove (Character* pilot);
		std::vector<Character*> pilots() const;
		
		virtual void setEnabled (bool enabled) override;
		
		bool factorReload()		const noexcept	{ return factorReload_; }
		void factorReload (bool factorReload) noexcept { factorReload_ = factorReload; }

	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) noexcept override;
		
	private:
		friend class WarfareBuffEffect;
		std::list<std::unique_ptr<Character>> pilots_;
		bool factorReload_;
	};
}
