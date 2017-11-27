//
//  Gang.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Character.hpp"

namespace dgmpp2 {
	class Character;
	
	class Gang: public Type {
	public:
		static std::unique_ptr<Gang> Create() {
			auto gang = std::unique_ptr<Gang>(new Gang);
			gang->setEnabled(true);
			return gang;
		}
		
		Character* add (std::unique_ptr<Character> pilot);
		
		void remove (Character* pilot);
		const std::list<std::unique_ptr<Character>>& pilots() const { return pilots_; }
		
		virtual void setEnabled (bool enabled) override;
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		
	private:
		friend class WarfareBuffEffect;
		Gang() : Type(TypeID::none) {}
		std::list<std::unique_ptr<Character>> pilots_;
	};
}
