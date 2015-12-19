#pragma once
#include "types.h"
#include "Modifier.h"

namespace eufe {
	struct Environment {
		Environment() : character(nullptr), ship(nullptr), gang(nullptr), self(nullptr), area(nullptr), target(nullptr), other(nullptr) {};
		Item* character;
		Item* ship;
		Item* gang;
		Item* self;
		Item* area;
		Item* target;
		Item* other;
		Item* operator[](const std::string& s) const {
			if (s == "Self")
				return self;
			else if (s == "Ship")
				return ship;
			else if (s == "Char")
				return character;
			else if (s == "Other")
				return other;
			else if (s == "Target")
				return target;
			else if (s == "Area")
				return area;
			else if (s == "Gang")
				return gang;
			else {
				assert(nullptr);
				return nullptr;
			}
		}
		
		Item* operator[](Modifier::Domain domain) const {
			switch(domain) {
				case Modifier::DOMAIN_SELF:
					return self;
				case Modifier::DOMAIN_SHIP:
					return ship;
				case Modifier::DOMAIN_CHAR:
					return character;
				case Modifier::DOMAIN_OTHER:
					return other;
				case Modifier::DOMAIN_TARGET:
					return target;
				case Modifier::DOMAIN_GANG:
					return gang;
				case Modifier::DOMAIN_AREA:
					return area;
			}
			return nullptr;
		}
	};
}