#include "EffectEnergyTransferInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectEnergyTransferInterpreter::EffectEnergyTransferInterpreter(std::shared_ptr<Engine> engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectEnergyTransferInterpreter::~EffectEnergyTransferInterpreter(void)
{
}

bool EffectEnergyTransferInterpreter::addEffect(const Environment& environment)
{
	Environment::const_iterator Target = environment.find("Target");
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(CHARGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_ADD_RATE,
																		Self->second->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		std::dynamic_pointer_cast<Character>(Char->second));
		Target->second->addItemModifier(modifier);
	}
	return 1;
}

bool EffectEnergyTransferInterpreter::removeEffect(const Environment& environment)
{
	Environment::const_iterator Target = environment.find("Target");
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();
	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(CHARGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_ADD_RATE,
																		Self->second->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		std::dynamic_pointer_cast<Character>(Char->second));
		Target->second->removeItemModifier(modifier);
	}
	return 1;
}
