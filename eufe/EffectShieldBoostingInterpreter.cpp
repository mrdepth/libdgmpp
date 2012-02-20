#include "EffectShieldBoostingInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectShieldBoostingInterpreter::EffectShieldBoostingInterpreter(Engine* engine, bool isProjected, bool isAssistance, bool isOffensive) : engine_(engine), isProjected_(isProjected), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectShieldBoostingInterpreter::~EffectShieldBoostingInterpreter(void)
{
}

bool EffectShieldBoostingInterpreter::addEffect(Environment* environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";
	if (environment->find(key) != environment->end())
	{
		(*environment)[key]->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(SHIELD_CHARGE_ATTRIBUTE_ID,
																					  Modifier::ASSOCIATION_ADD_RATE,
																					  (*environment)["Self"]->getAttribute(SHIELD_BONUS_ATTRIBUTE_ID).get(),
																					  isAssistance_,
																					  isOffensive_,
																					  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

bool EffectShieldBoostingInterpreter::removeEffect(Environment* environment)
{
	const char* key = isProjected_ ? "Target" : "Ship";
	if (environment->find(key) != environment->end())
	{
		(*environment)[key]->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(SHIELD_CHARGE_ATTRIBUTE_ID,
																						 Modifier::ASSOCIATION_ADD_RATE,
																						 (*environment)["Self"]->getAttribute(SHIELD_BONUS_ATTRIBUTE_ID).get(),
																						 isAssistance_,
																						 isOffensive_,
																						 dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

EffectInterpreter* EffectShieldBoostingInterpreter::clone() const
{
	return new EffectShieldBoostingInterpreter(*this);
}
