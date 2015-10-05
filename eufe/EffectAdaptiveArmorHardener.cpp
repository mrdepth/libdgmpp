#include "EffectAdaptiveArmorHardener.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectAdaptiveArmorHardener::EffectAdaptiveArmorHardener(std::shared_ptr<Engine> engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectAdaptiveArmorHardener::~EffectAdaptiveArmorHardener(void)
{
}

bool EffectAdaptiveArmorHardener::addEffect(const Environment& environment)
{
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator Ship = environment.find("Ship");
	Environment::const_iterator end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifierEm = std::make_shared<Modifier>(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierEx = std::make_shared<Modifier>(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierKi = std::make_shared<Modifier>(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierTh = std::make_shared<Modifier>(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));

		Ship->second->addItemModifier(modifierEm);
		Ship->second->addItemModifier(modifierEx);
		Ship->second->addItemModifier(modifierKi);
		Ship->second->addItemModifier(modifierTh);
	}
	return 1;
}

bool EffectAdaptiveArmorHardener::removeEffect(const Environment& environment)
{
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator Ship = environment.find("Ship");
	Environment::const_iterator end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifierEm = std::make_shared<Modifier>(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierEx = std::make_shared<Modifier>(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierKi = std::make_shared<Modifier>(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));
		
		std::shared_ptr<Modifier> modifierTh = std::make_shared<Modifier>(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->second->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  std::dynamic_pointer_cast<Character>(Char->second));
		
		Ship->second->removeItemModifier(modifierEm);
		Ship->second->removeItemModifier(modifierEx);
		Ship->second->removeItemModifier(modifierKi);
		Ship->second->removeItemModifier(modifierTh);
	}
	return 1;
}
