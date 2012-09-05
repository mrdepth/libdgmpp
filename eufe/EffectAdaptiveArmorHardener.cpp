#include "EffectAdaptiveArmorHardener.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectAdaptiveArmorHardener::EffectAdaptiveArmorHardener(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
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
		Modifier* modifierEm = new Modifier(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));

		Modifier* modifierEx = new Modifier(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));

		Modifier* modifierKi = new Modifier(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));

		Modifier* modifierTh = new Modifier(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));

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
		Modifier* modifierEm = new Modifier(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));
		
		Modifier* modifierEx = new Modifier(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));
		
		Modifier* modifierKi = new Modifier(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));
		
		Modifier* modifierTh = new Modifier(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
											Modifier::ASSOCIATION_POST_MUL,
											Self->second->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID),
											isAssistance_,
											isOffensive_,
											dynamic_cast<Character*>(Char->second));
		
		Ship->second->removeItemModifier(modifierEm);
		Ship->second->removeItemModifier(modifierEx);
		Ship->second->removeItemModifier(modifierKi);
		Ship->second->removeItemModifier(modifierTh);
		
		delete modifierEm;
		delete modifierEx;
		delete modifierKi;
		delete modifierTh;
	}
	return 1;
}

EffectInterpreter* EffectAdaptiveArmorHardener::clone() const
{
	return new EffectAdaptiveArmorHardener(*this);
}
