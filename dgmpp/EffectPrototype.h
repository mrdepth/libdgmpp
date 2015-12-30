#pragma once
#include "types.h"
#include "Modifier.h"
#include <stdexcept>
#include <vector>
#include "Effect.h"

namespace dgmpp {
	class EffectPrototype {
	public:
		static std::shared_ptr<EffectPrototype> getEffectPrototype(std::shared_ptr<Engine> const& engine, TypeID effectID);

		class ModifierPrototype {
		public:
			dgmpp::Modifier::Domain domain;
			dgmpp::Modifier::Type type;
			int32_t modifiedAttributeID;
			int32_t modifyingAttributeID;
			dgmpp::Modifier::Association association;
			int32_t requiredID;
		};
		
		typedef std::list<std::shared_ptr<ModifierPrototype>> ModifierPrototypesList;
		
		const ModifierPrototypesList& getModifierPrototypes() const {
			return modifierPrototypes_;
		};

		EffectPrototype(std::shared_ptr<Engine> const& engine, TypeID effectID);
		virtual ~EffectPrototype();
		
		TypeID getEffectID() const {return effectID_;};
		Effect::Category getCategory() const {return category_;};
		const char* getEffectName() const {return effectName_.c_str();};
		bool isAssistance() const {return isAssistance_;};
		bool isOffensive() const {return isOffensive_;};
	private:

		std::weak_ptr<Engine> engine_;
		ModifierPrototypesList modifierPrototypes_;
		
		Effect::Category category_;
		TypeID effectID_;
		std::string effectName_;
		bool isAssistance_;
		bool isOffensive_;
	};
}