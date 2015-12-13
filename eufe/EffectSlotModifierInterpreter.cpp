#include "EffectSlotModifierInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectSlotModifierInterpreter::EffectSlotModifierInterpreter(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectSlotModifierInterpreter::~EffectSlotModifierInterpreter(void)
{
}

bool EffectSlotModifierInterpreter::addEffect(const Environment& environment)
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
		std::shared_ptr<Modifier> modifierHiSlot = std::make_shared<Modifier>(HI_SLOTS_ATTRIBUTE_ID,
																			  Modifier::ASSOCIATION_MOD_ADD,
																			  Self->getAttribute(HI_SLOT_MODIFIER_ATTRIBUTE_ID),
																			  isAssistance_,
																			  isOffensive_,
																			  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierMedSlot = std::make_shared<Modifier>(MED_SLOTS_ATTRIBUTE_ID,
																			   Modifier::ASSOCIATION_MOD_ADD,
																			   Self->getAttribute(MED_SLOT_MODIFIER_ATTRIBUTE_ID),
																			   isAssistance_,
																			   isOffensive_,
																			   dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierLowSlot = std::make_shared<Modifier>(LOW_SLOTS_ATTRIBUTE_ID,
																			   Modifier::ASSOCIATION_MOD_ADD,
																			   Self->getAttribute(LOW_SLOT_MODIFIER_ATTRIBUTE_ID),
																			   isAssistance_,
																			   isOffensive_,
																			   dynamic_cast<Character*>(Char));

		Ship->addItemModifier(modifierHiSlot);
		Ship->addItemModifier(modifierMedSlot);
		Ship->addItemModifier(modifierLowSlot);
	}
	return 1;
}

bool EffectSlotModifierInterpreter::removeEffect(const Environment& environment)
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
		std::shared_ptr<Modifier> modifierHiSlot = std::make_shared<Modifier>(HI_SLOTS_ATTRIBUTE_ID,
																			  Modifier::ASSOCIATION_MOD_ADD,
																			  Self->getAttribute(HI_SLOT_MODIFIER_ATTRIBUTE_ID),
																			  isAssistance_,
																			  isOffensive_,
																			  dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierMedSlot = std::make_shared<Modifier>(MED_SLOTS_ATTRIBUTE_ID,
																			   Modifier::ASSOCIATION_MOD_ADD,
																			   Self->getAttribute(MED_SLOT_MODIFIER_ATTRIBUTE_ID),
																			   isAssistance_,
																			   isOffensive_,
																			   dynamic_cast<Character*>(Char));
		
		std::shared_ptr<Modifier> modifierLowSlot = std::make_shared<Modifier>(LOW_SLOTS_ATTRIBUTE_ID,
																			   Modifier::ASSOCIATION_MOD_ADD,
																			   Self->getAttribute(LOW_SLOT_MODIFIER_ATTRIBUTE_ID),
																			   isAssistance_,
																			   isOffensive_,
																			   dynamic_cast<Character*>(Char));
		
		Ship->removeItemModifier(modifierHiSlot);
		Ship->removeItemModifier(modifierMedSlot);
		Ship->removeItemModifier(modifierLowSlot);
	}
	return 1;
}
