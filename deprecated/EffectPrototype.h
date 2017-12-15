#pragma once
#include "types.h"
#include "Modifier.h"
#include <stdexcept>
#include <vector>
#include "Effect.h"

namespace dgmpp {
	class EffectPrototype {
	public:
		static std::shared_ptr<EffectPrototype> getEffectPrototype(std::shared_ptr<Engine> const& engine, EffectID effectID);

		class ModifierPrototype {
		public:
			Modifier::Domain domain;
			Modifier::Type type;
			AttributeID modifiedAttributeID;
			AttributeID modifyingAttributeID;
			Modifier::Association association;
			int32_t requiredID;
		};
		
		typedef std::list<std::shared_ptr<ModifierPrototype>> ModifierPrototypesList;
		
		const ModifierPrototypesList& getModifierPrototypes() const {
			return modifierPrototypes_;
		};

		EffectPrototype(std::shared_ptr<Engine> const& engine, EffectID effectID);
		virtual ~EffectPrototype();
		
		EffectID getEffectID() const {return effectID_;};
		Effect::Category getCategory() const {return category_;};
		const char* getEffectName() const {return effectName_.c_str();};
		bool isAssistance() const {return isAssistance_;};
		bool isOffensive() const {return isOffensive_;};
	private:

		std::weak_ptr<Engine> engine_;
		ModifierPrototypesList modifierPrototypes_;
		
		Effect::Category category_;
		EffectID effectID_;
		std::string effectName_;
		bool isAssistance_;
		bool isOffensive_;
	};
}
