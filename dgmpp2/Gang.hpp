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
		std::vector<Character*> pilots() const;
		
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		
	private:
		Gang() : Type(TypeID::none) {}
		
	};
}
