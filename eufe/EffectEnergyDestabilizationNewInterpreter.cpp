#include "EffectEnergyDestabilizationNewInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectEnergyDestabilizationNewInterpreter::EffectEnergyDestabilizationNewInterpreter(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectEnergyDestabilizationNewInterpreter::~EffectEnergyDestabilizationNewInterpreter(void)
{
}


bool EffectEnergyDestabilizationNewInterpreter::addEffect(const Environment& environment)
{
	/*Environment::const_iterator Target = environment.find("Target");
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();*/
	auto Target = environment.target;
	auto Self = environment.self;
	auto Char = environment.character;
	Item* end = nullptr;

	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(CHARGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_SUB_RATE,
																		Self->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		dynamic_cast<Character*>(Char));
		Target->addItemModifier(modifier);
	}
	return 1;
}

bool EffectEnergyDestabilizationNewInterpreter::removeEffect(const Environment& environment)
{
	/*Environment::const_iterator Target = environment.find("Target");
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();*/
	auto Target = environment.target;
	auto Self = environment.self;
	auto Char = environment.character;
	Item* end = nullptr;

	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(CHARGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_SUB_RATE,
																		Self->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		dynamic_cast<Character*>(Char));
		Target->removeItemModifier(modifier);
	}
	return 1;
}
