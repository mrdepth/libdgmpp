#include "EffectArmorRepairInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectArmorRepairInterpreter::EffectArmorRepairInterpreter(Engine* engine, bool isProjected, bool isAssistance, bool isOffensive) : engine_(engine), isProjected_(isProjected), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectArmorRepairInterpreter::~EffectArmorRepairInterpreter(void)
{
}

bool EffectArmorRepairInterpreter::addEffect(const Environment& environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";

	auto Target = environment.find(key);
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(ARMOR_DAMAGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_SUB_RATE,
										  Self->second->getAttribute(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->addItemModifier(modifier);
	}
	return 1;
}

bool EffectArmorRepairInterpreter::removeEffect(const Environment& environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";

	auto Target = environment.find(key);
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(ARMOR_DAMAGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_SUB_RATE,
										  Self->second->getAttribute(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->removeItemModifier(modifier);
		delete modifier;
	}
	return 1;
}

EffectInterpreter* EffectArmorRepairInterpreter::clone() const
{
	return new EffectArmorRepairInterpreter(*this);
}
