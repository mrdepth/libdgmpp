#include "EffectArmorRepairInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectArmorRepairInterpreter::EffectArmorRepairInterpreter(std::shared_ptr<Engine> const& engine, bool isProjected, bool isAssistance, bool isOffensive) : engine_(engine), isProjected_(isProjected), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectArmorRepairInterpreter::~EffectArmorRepairInterpreter(void)
{
}

bool EffectArmorRepairInterpreter::addEffect(const Environment& environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";

	Environment::const_iterator Target = environment.find(key);
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(ARMOR_DAMAGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_SUB_RATE,
																		Self->second->getAttribute(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		std::dynamic_pointer_cast<Character>(Char->second));
		Target->second->addItemModifier(modifier);
	}
	return 1;
}

bool EffectArmorRepairInterpreter::removeEffect(const Environment& environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";

	Environment::const_iterator Target = environment.find(key);
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(ARMOR_DAMAGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_SUB_RATE,
																		Self->second->getAttribute(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		std::dynamic_pointer_cast<Character>(Char->second));
		Target->second->removeItemModifier(modifier);
	}
	return 1;
}
