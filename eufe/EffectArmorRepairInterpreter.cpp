#include "EffectArmorRepairInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectArmorRepairInterpreter::EffectArmorRepairInterpreter(Engine* engine, bool isProjected, bool isAssistance, bool isOffensive) : engine_(engine), isProjected_(isProjected), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectArmorRepairInterpreter::~EffectArmorRepairInterpreter(void)
{
}

bool EffectArmorRepairInterpreter::addEffect(Environment* environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";
	if (environment->find(key) != environment->end())
	{
		(*environment)[key]->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_DAMAGE_ATTRIBUTE_ID,
																					  Modifier::ASSOCIATION_SUB_RATE,
																					  (*environment)["Self"]->getAttribute(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID).get(),
																					  isAssistance_,
																					  isOffensive_,
																					  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

bool EffectArmorRepairInterpreter::removeEffect(Environment* environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";
	if (environment->find(key) != environment->end())
	{
		(*environment)[key]->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(ARMOR_DAMAGE_ATTRIBUTE_ID,
																					  Modifier::ASSOCIATION_SUB_RATE,
																					  (*environment)["Self"]->getAttribute(ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID).get(),
																					  isAssistance_,
																					  isOffensive_,
																					  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

EffectInterpreter* EffectArmorRepairInterpreter::clone() const
{
	return new EffectArmorRepairInterpreter(*this);
}