#include "EffectAdaptiveArmorHardener.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectAdaptiveArmorHardener::EffectAdaptiveArmorHardener(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectAdaptiveArmorHardener::~EffectAdaptiveArmorHardener(void)
{
}

bool EffectAdaptiveArmorHardener::addEffect(const Environment& environment)
{
	//Environment::const_iterator Self = environment.find("Self");
	//Environment::const_iterator Char = environment.find("Char");
	//Environment::const_iterator Ship = environment.find("Ship");
	//Environment::const_iterator end = environment.end();
	auto Self = environment.self;
	auto Char = environment.character;
	auto Ship = environment.ship;
	Item* end = nullptr;
	
	if (Ship != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifierEm = std::make_shared<Modifier>(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierEx = std::make_shared<Modifier>(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierKi = std::make_shared<Modifier>(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierTh = std::make_shared<Modifier>(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));

		Ship->addItemModifier(modifierEm);
		Ship->addItemModifier(modifierEx);
		Ship->addItemModifier(modifierKi);
		Ship->addItemModifier(modifierTh);
	}
	return 1;
}

bool EffectAdaptiveArmorHardener::removeEffect(const Environment& environment)
{
//	Environment::const_iterator Self = environment.find("Self");
//	Environment::const_iterator Char = environment.find("Char");
//	Environment::const_iterator Ship = environment.find("Ship");
//	Environment::const_iterator end = environment.end();
	auto Self = environment.self;
	auto Char = environment.character;
	auto Ship = environment.ship;
	Item* end = nullptr;

	if (Ship != end && Self != end && Char != end) {
		std::shared_ptr<Modifier> modifierEm = std::make_shared<Modifier>(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierEx = std::make_shared<Modifier>(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierKi = std::make_shared<Modifier>(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierTh = std::make_shared<Modifier>(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  Self->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>(Char));
		
		Ship->removeItemModifier(modifierEm);
		Ship->removeItemModifier(modifierEx);
		Ship->removeItemModifier(modifierKi);
		Ship->removeItemModifier(modifierTh);
	}
	return 1;
}
