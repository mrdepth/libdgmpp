#pragma once
#include "types.h"
#include "Modifier.h"

namespace dgmpp {
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
		virtual Item* structure() {
			return nullptr;
		}
		Item* operator[](Modifier::Domain domain) {
			switch(domain) {
				case Modifier::Domain::self:
					return self();
				case Modifier::Domain::ship:
					return ship();
				case Modifier::Domain::character:
					return character();
				case Modifier::Domain::other:
					return other();
				case Modifier::Domain::target:
					return target();
				case Modifier::Domain::gang:
					return gang();
				case Modifier::Domain::area:
					return area();
				case Modifier::Domain::structure:
					return structure();
			}
			return nullptr;
		}
	};
}
