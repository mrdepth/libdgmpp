//
//  Character.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Skill.hpp"
#include "Ship.hpp"

namespace dgmpp2 {
	class Character: public Type {
	public:
		struct InvalidSkillLevel: std::runtime_error {
			InvalidSkillLevel(): std::runtime_error("Skill level should be in [0...5] range") {}
		};
		
		static std::unique_ptr<Character> Create() { return std::unique_ptr<Character>(new Character); }
		Ship* setShip (std::unique_ptr<Ship> ship);
		void setSkillLevels (int level);
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		virtual void reset() override;
	private:
		Ship* ship_ = nullptr;
		std::map<TypeID, class Skill*> skills_;
		
		Character();
	};
}
