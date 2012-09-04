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

bool EffectHardPointModifierEffectInterpreter::addEffect(Environment* environment)
{
	if (environment->find("Ship") != environment->end())
	{
		Item* ship = (*environment)["Ship"];
		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_MOD_ADD,
																	   (*environment)["Self"]->getAttribute(LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));
		
		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(TURRET_SLOTS_LEFT_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_MOD_ADD,
																	   (*environment)["Self"]->getAttribute(TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

bool EffectHardPointModifierEffectInterpreter::removeEffect(Environment* environment)
{
	if (environment->find("Ship") != environment->end())
	{
		Item* ship = (*environment)["Ship"];
		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_MOD_ADD,
																		  (*environment)["Self"]->getAttribute(LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));
		
		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(TURRET_SLOTS_LEFT_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_MOD_ADD,
																		  (*environment)["Self"]->getAttribute(TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

EffectInterpreter* EffectHardPointModifierEffectInterpreter::clone() const
{
	return new EffectHardPointModifierEffectInterpreter(*this);
}
