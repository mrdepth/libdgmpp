#include "EffectHardPointModifierEffectInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectHardPointModifierEffectInterpreter::EffectHardPointModifierEffectInterpreter(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectHardPointModifierEffectInterpreter::~EffectHardPointModifierEffectInterpreter(void)
{
}

bool EffectHardPointModifierEffectInterpreter::addEffect(const Environment& environment)
{
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto Ship = environment.find("Ship");
	auto end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		Modifier* modifierLauncher = new Modifier(LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID,
												  Modifier::ASSOCIATION_MOD_ADD,
												  Self->second->getAttribute(LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
												  isAssistance_,
												  isOffensive_,
												  dynamic_cast<Character*>(Char->second));
		
		Modifier* modifierTurrent = new Modifier(TURRET_SLOTS_LEFT_ATTRIBUTE_ID,
												 Modifier::ASSOCIATION_MOD_ADD,
												 Self->second->getAttribute(TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
												 isAssistance_,
												 isOffensive_,
												 dynamic_cast<Character*>(Char->second));
		
		Ship->second->addItemModifier(modifierLauncher);
		Ship->second->addItemModifier(modifierTurrent);
	}
	return 1;
}

bool EffectHardPointModifierEffectInterpreter::removeEffect(const Environment& environment)
{
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto Ship = environment.find("Ship");
	auto end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		Modifier* modifierLauncher = new Modifier(LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID,
												  Modifier::ASSOCIATION_MOD_ADD,
												  Self->second->getAttribute(LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
												  isAssistance_,
												  isOffensive_,
												  dynamic_cast<Character*>(Char->second));
		
		Modifier* modifierTurrent = new Modifier(TURRET_SLOTS_LEFT_ATTRIBUTE_ID,
												 Modifier::ASSOCIATION_MOD_ADD,
												 Self->second->getAttribute(TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
												 isAssistance_,
												 isOffensive_,
												 dynamic_cast<Character*>(Char->second));
		
		Ship->second->removeItemModifier(modifierLauncher);
		Ship->second->removeItemModifier(modifierTurrent);

		delete modifierLauncher;
		delete modifierTurrent;
	}
	return 1;
}

EffectInterpreter* EffectHardPointModifierEffectInterpreter::clone() const
{
	return new EffectHardPointModifierEffectInterpreter(*this);
}
