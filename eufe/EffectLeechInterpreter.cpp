#include "EffectLeechInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectLeechInterpreter::EffectLeechInterpreter(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectLeechInterpreter::~EffectLeechInterpreter(void)
{
}

bool EffectLeechInterpreter::addEffect(const Environment& environment)
{
	Environment::const_iterator Target = environment.find("Target");
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(CHARGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_SUB_RATE,
										  Self->second->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->addItemModifier(modifier);
	}
	return 1;
}

bool EffectLeechInterpreter::removeEffect(const Environment& environment)
{
	Environment::const_iterator Target = environment.find("Target");
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(CHARGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_SUB_RATE,
										  Self->second->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->removeItemModifier(modifier);
		delete modifier;
	}
	return 1;
}

EffectInterpreter* EffectLeechInterpreter::clone() const
{
	return new EffectLeechInterpreter(*this);
}
