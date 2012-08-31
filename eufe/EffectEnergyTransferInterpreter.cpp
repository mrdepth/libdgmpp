#include "EffectEnergyTransferInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectEnergyTransferInterpreter::EffectEnergyTransferInterpreter(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectEnergyTransferInterpreter::~EffectEnergyTransferInterpreter(void)
{
}

bool EffectEnergyTransferInterpreter::addEffect(const Environment& environment)
{
	auto Target = environment.find("Target");
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(CHARGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_ADD_RATE,
										  Self->second->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->addItemModifier(modifier);
	}
	return 1;
}

bool EffectEnergyTransferInterpreter::removeEffect(const Environment& environment)
{
	auto Target = environment.find("Target");
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	if (Target != end && Self != end && Char != end) {
		Modifier* modifier = new Modifier(CHARGE_ATTRIBUTE_ID,
										  Modifier::ASSOCIATION_ADD_RATE,
										  Self->second->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID),
										  isAssistance_,
										  isOffensive_,
										  dynamic_cast<Character*>(Char->second));
		Target->second->removeItemModifier(modifier);
		delete modifier;
	}
	return 1;
}

EffectInterpreter* EffectEnergyTransferInterpreter::clone() const
{
	return new EffectEnergyTransferInterpreter(*this);
}
