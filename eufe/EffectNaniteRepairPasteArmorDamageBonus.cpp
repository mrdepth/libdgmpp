#include "EffectNaniteRepairPasteArmorDamageBonus.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectNaniteRepairPasteArmorDamageBonus::EffectNaniteRepairPasteArmorDamageBonus(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectNaniteRepairPasteArmorDamageBonus::~EffectNaniteRepairPasteArmorDamageBonus(void)
{
}

bool EffectNaniteRepairPasteArmorDamageBonus::addEffect(const Environment& environment)
{
	/*Environment::const_iterator Self = environment.find("Self");
	Environment::const_iterator Char = environment.find("Char");
	Environment::const_iterator Other = environment.find("Other");
	Environment::const_iterator end = environment.end();*/
	auto Self = environment.self;
	auto Char = environment.character;
	auto Other = environment.other;
	Item* end = nullptr;

	if (Self != end && Char != end && Other != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_POST_MUL,
																		Other->getAttribute(CHARGE_ARMOR_DAMAGE_MULTIPLIER_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		dynamic_cast<Character*>(Char));
		Other->addItemModifier(modifier);
	}
	return 1;
}

bool EffectNaniteRepairPasteArmorDamageBonus::removeEffect(const Environment& environment)
{
	/*Environment::const_iterator Self = environment.find("Self");
	 Environment::const_iterator Char = environment.find("Char");
	 Environment::const_iterator Other = environment.find("Other");
	 Environment::const_iterator end = environment.end();*/
	auto Self = environment.self;
	auto Char = environment.character;
	auto Other = environment.other;
	Item* end = nullptr;
	
	if (Self != end && Char != end && Other != end) {
		std::shared_ptr<Modifier> modifier = std::make_shared<Modifier>(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID,
																		Modifier::ASSOCIATION_POST_MUL,
																		Other->getAttribute(CHARGE_ARMOR_DAMAGE_MULTIPLIER_ATTRIBUTE_ID),
																		isAssistance_,
																		isOffensive_,
																		dynamic_cast<Character*>(Char));
		Other->removeItemModifier(modifier);
	}
	return 1;
}
