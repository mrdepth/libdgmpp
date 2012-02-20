#include "EffectSlotModifierInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectSlotModifierInterpreter::EffectSlotModifierInterpreter(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectSlotModifierInterpreter::~EffectSlotModifierInterpreter(void)
{
}

bool EffectSlotModifierInterpreter::addEffect(Environment* environment)
{
	if (environment->find("Ship") != environment->end())
	{
		Item* ship = (*environment)["Ship"];
		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(HI_SLOTS_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_MOD_ADD,
																	   (*environment)["Self"]->getAttribute(HI_SLOT_MODIFIER_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));

		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(MED_SLOTS_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_MOD_ADD,
																	   (*environment)["Self"]->getAttribute(MED_SLOT_MODIFIER_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));

		ship->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(LOW_SLOTS_ATTRIBUTE_ID,
																	   Modifier::ASSOCIATION_MOD_ADD,
																	   (*environment)["Self"]->getAttribute(LOW_SLOT_MODIFIER_ATTRIBUTE_ID).get(),
																	   isAssistance_,
																	   isOffensive_,
																	   dynamic_cast<Character*>((*environment)["Char"]))));
}
	return 1;
}

bool EffectSlotModifierInterpreter::removeEffect(Environment* environment)
{
	if (environment->find("Ship") != environment->end())
	{
		Item* ship = (*environment)["Ship"];
		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(HI_SLOTS_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_MOD_ADD,
																		  (*environment)["Self"]->getAttribute(HI_SLOT_MODIFIER_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));
		
		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(MED_SLOTS_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_MOD_ADD,
																		  (*environment)["Self"]->getAttribute(MED_SLOT_MODIFIER_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));
		
		ship->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(LOW_SLOTS_ATTRIBUTE_ID,
																		  Modifier::ASSOCIATION_MOD_ADD,
																		  (*environment)["Self"]->getAttribute(LOW_SLOT_MODIFIER_ATTRIBUTE_ID).get(),
																		  isAssistance_,
																		  isOffensive_,
																		  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

EffectInterpreter* EffectSlotModifierInterpreter::clone() const
{
	return new EffectSlotModifierInterpreter(*this);
}
