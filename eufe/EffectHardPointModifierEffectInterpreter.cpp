#include "EffectHardPointModifierEffectInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectHardPointModifierEffectInterpreter::EffectHardPointModifierEffectInterpreter(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectHardPointModifierEffectInterpreter::~EffectHardPointModifierEffectInterpreter(void)
{
}

bool EffectHardPointModifierEffectInterpreter::addEffect(const Environment& environment)
{
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator Ship = environment.find("Ship");
	Environment::const_iterator end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifierLauncher = std::make_shared<Modifier>(LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID,
																				Modifier::ASSOCIATION_MOD_ADD,
																				Self->second->getAttribute(LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
																				isAssistance_,
																				isOffensive_,
																				std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierTurrent = std::make_shared<Modifier>(TURRET_SLOTS_LEFT_ATTRIBUTE_ID,
																			   Modifier::ASSOCIATION_MOD_ADD,
																			   Self->second->getAttribute(TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
																			   isAssistance_,
																			   isOffensive_,
																			   std::dynamic_pointer_cast<Character>(Char->second));
		
		Ship->second->addItemModifier(modifierLauncher);
		Ship->second->addItemModifier(modifierTurrent);
	}
	return 1;
}

bool EffectHardPointModifierEffectInterpreter::removeEffect(const Environment& environment)
{
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator Ship = environment.find("Ship");
	Environment::const_iterator end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifierLauncher = std::make_shared<Modifier>(LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID,
																				Modifier::ASSOCIATION_MOD_ADD,
																				Self->second->getAttribute(LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
																				isAssistance_,
																				isOffensive_,
																				std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierTurrent = std::make_shared<Modifier>(TURRET_SLOTS_LEFT_ATTRIBUTE_ID,
																			   Modifier::ASSOCIATION_MOD_ADD,
																			   Self->second->getAttribute(TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID),
																			   isAssistance_,
																			   isOffensive_,
																			   std::dynamic_pointer_cast<Character>(Char->second));
		
		Ship->second->removeItemModifier(modifierLauncher);
		Ship->second->removeItemModifier(modifierTurrent);

	}
	return 1;
}
