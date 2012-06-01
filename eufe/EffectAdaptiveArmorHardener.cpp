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

bool EffectAdaptiveArmorHardener::addEffect(Environment* environment)
{
	if (environment->find("Ship") != environment->end())
	{
		Item* ship = (*environment)["Ship"];
		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_POST_MUL,
																	   (*environment)["Self"]->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));
		
		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_POST_MUL,
																	   (*environment)["Self"]->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));

		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_POST_MUL,
																	   (*environment)["Self"]->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));

		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_POST_MUL,
																	   (*environment)["Self"]->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));
}
	return 1;
}

bool EffectAdaptiveArmorHardener::removeEffect(Environment* environment)
{
	if (environment->find("Ship") != environment->end())
	{
		Item* ship = (*environment)["Ship"];
		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  (*environment)["Self"]->getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));
		
		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  (*environment)["Self"]->getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));

		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  (*environment)["Self"]->getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));

		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_POST_MUL,
																		  (*environment)["Self"]->getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));
}
	return 1;
}

EffectInterpreter* EffectAdaptiveArmorHardener::clone() const
{
	return new EffectAdaptiveArmorHardener(*this);
}
