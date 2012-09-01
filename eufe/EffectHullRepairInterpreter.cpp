#include "EffectHullRepairInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectHullRepairInterpreter::EffectHullRepairInterpreter(Engine* engine, bool isProjected, bool isAssistance, bool isOffensive) : engine_(engine), isProjected_(isProjected), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectHullRepairInterpreter::~EffectHullRepairInterpreter(void)
{
}

bool EffectHullRepairInterpreter::addEffect(const Environment& environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";
	
	Environment::const_iterator Target = environment.find(key);
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(DAMAGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_SUB_RATE,
										  Self->second->getAttribute(STRUCTURE_DAMAGE_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->addItemModifier(modifier);
	}
	return 1;
}

bool EffectHullRepairInterpreter::removeEffect(const Environment& environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";
	
	Environment::const_iterator Target = environment.find(key);
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(DAMAGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_SUB_RATE,
										  Self->second->getAttribute(STRUCTURE_DAMAGE_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->removeItemModifier(modifier);
		delete modifier;
	}
	return 1;
}

EffectInterpreter* EffectHullRepairInterpreter::clone() const
{
	return new EffectHullRepairInterpreter(*this);
}
