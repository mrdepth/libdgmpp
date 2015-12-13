#include "EffectHullRepairInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectHullRepairInterpreter::EffectHullRepairInterpreter(std::shared_ptr<Engine> const& engine, bool isProjected, bool isAssistance, bool isOffensive) : engine_(engine), isProjected_(isProjected), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectHullRepairInterpreter::~EffectHullRepairInterpreter(void)
{
}

bool EffectHullRepairInterpreter::addEffect(const Environment& environment)
{
	//const char* key = isProjected_ ? "Target" : "Ship";
	
	//Environment::const_iterator Target = environment.find(key);
	//Environment::const_iterator Self = environment.find("Self");
	//Environment::const_iterator Char = environment.find("Char");
	//Environment::const_iterator end = environment.end();
	
	auto Target = isProjected_ ? environment.target : environment.ship;
	auto Self = environment.self;
	auto Char = environment.character;
	Item* end = nullptr;

	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(DAMAGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_SUB_RATE,
																		Self->getAttribute(STRUCTURE_DAMAGE_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		dynamic_cast<Character*>(Char));
		Target->addItemModifier(modifier);
	}
	return 1;
}

bool EffectHullRepairInterpreter::removeEffect(const Environment& environment)
{
	/*const char* key = isProjected_ ? "Target" : "Ship";
	
	Environment::const_iterator Target = environment.find(key);
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator end = environment.end();*/
	auto Target = isProjected_ ? environment.target : environment.ship;
	auto Self = environment.self;
	auto Char = environment.character;
	Item* end = nullptr;

	if (Target != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(DAMAGE_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_SUB_RATE,
																		Self->getAttribute(STRUCTURE_DAMAGE_AMOUNT_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		dynamic_cast<Character*>(Char));
		Target->removeItemModifier(modifier);
	}
	return 1;
}
