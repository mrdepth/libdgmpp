#pragma once
#include "types.h"
#include "Modifier.h"

namespace eufe {
	class Environment {
	public:
		virtual Item* character() {
			return nullptr;
		}
		virtual Item* ship() {
			return nullptr;
		}
		virtual Item* gang() {
			return nullptr;
		}
		virtual Item* self() {
			return nullptr;
		}
		virtual Item* area() {
			return nullptr;
		}
		virtual Item* target() {
			return nullptr;
		}
		virtual Item* other() {
			return nullptr;
		}
		Item* operator[](Modifier::Domain domain) {
			switch(domain) {
				case Modifier::DOMAIN_SELF:
					return self();
				case Modifier::DOMAIN_SHIP:
					return ship();
				case Modifier::DOMAIN_CHAR:
					return character();
				case Modifier::DOMAIN_OTHER:
					return other();
				case Modifier::DOMAIN_TARGET:
					return target();
				case Modifier::DOMAIN_GANG:
					return gang();
				case Modifier::DOMAIN_AREA:
					return area();
			}
			return nullptr;
		}
	};
}