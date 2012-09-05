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

bool EffectSlotModifierInterpreter::addEffect(const Environment& environment)
{
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator Ship = environment.find("Ship");
	Environment::const_iterator end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		Modifier* modifierHiSlot = new Modifier(HI_SLOTS_ATTRIBUTE_ID,
												Modifier::ASSOCIATION_MOD_ADD,
												Self->second->getAttribute(HI_SLOT_MODIFIER_ATTRIBUTE_ID),
												isAssistance_,
												isOffensive_,
												dynamic_cast<Character*>(Char->second));

		Modifier* modifierMedSlot = new Modifier(MED_SLOTS_ATTRIBUTE_ID,
												Modifier::ASSOCIATION_MOD_ADD,
												Self->second->getAttribute(MED_SLOT_MODIFIER_ATTRIBUTE_ID),
												isAssistance_,
												isOffensive_,
												dynamic_cast<Character*>(Char->second));

		Modifier* modifierLowSlot = new Modifier(LOW_SLOTS_ATTRIBUTE_ID,
												Modifier::ASSOCIATION_MOD_ADD,
												Self->second->getAttribute(LOW_SLOT_MODIFIER_ATTRIBUTE_ID),
												isAssistance_,
												isOffensive_,
												dynamic_cast<Character*>(Char->second));

		Ship->second->addItemModifier(modifierHiSlot);
		Ship->second->addItemModifier(modifierMedSlot);
		Ship->second->addItemModifier(modifierLowSlot);
	}
	return 1;
}

bool EffectSlotModifierInterpreter::removeEffect(const Environment& environment)
{
	Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator Ship = environment.find("Ship");
	Environment::const_iterator end = environment.end();
	if (Ship != end && Self != end && Char != end) {
		Modifier* modifierHiSlot = new Modifier(HI_SLOTS_ATTRIBUTE_ID,
												Modifier::ASSOCIATION_MOD_ADD,
												Self->second->getAttribute(HI_SLOT_MODIFIER_ATTRIBUTE_ID),
												isAssistance_,
												isOffensive_,
												dynamic_cast<Character*>(Char->second));
		
		Modifier* modifierMedSlot = new Modifier(MED_SLOTS_ATTRIBUTE_ID,
												 Modifier::ASSOCIATION_MOD_ADD,
												 Self->second->getAttribute(MED_SLOT_MODIFIER_ATTRIBUTE_ID),
												 isAssistance_,
												 isOffensive_,
												 dynamic_cast<Character*>(Char->second));
		
		Modifier* modifierLowSlot = new Modifier(LOW_SLOTS_ATTRIBUTE_ID,
												 Modifier::ASSOCIATION_MOD_ADD,
												 Self->second->getAttribute(LOW_SLOT_MODIFIER_ATTRIBUTE_ID),
												 isAssistance_,
												 isOffensive_,
												 dynamic_cast<Character*>(Char->second));
		
		Ship->second->removeItemModifier(modifierHiSlot);
		Ship->second->removeItemModifier(modifierMedSlot);
		Ship->second->removeItemModifier(modifierLowSlot);
		delete modifierHiSlot;
		delete modifierMedSlot;
		delete modifierLowSlot;
	}
	return 1;
}


EffectInterpreter* EffectSlotModifierInterpreter::clone() const
{
	return new EffectSlotModifierInterpreter(*this);
}
