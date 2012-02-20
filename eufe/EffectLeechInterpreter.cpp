#include "EffectLeechInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectLeechInterpreter::EffectLeechInterpreter(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectLeechInterpreter::~EffectLeechInterpreter(void)
{
}

bool EffectLeechInterpreter::addEffect(Environment* environment)
{
	if (environment->find("Target") != environment->end())
	{
		(*environment)["Target"]->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(CHARGE_ATTRIBUTE_ID,
																						   Modifier::ASSOCIATION_SUB_RATE,
																						   (*environment)["Self"]->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID).get(),
																						   isAssistance_,
																						   isOffensive_,
																						   dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

bool EffectLeechInterpreter::removeEffect(Environment* environment)
{
	if (environment->find("Target") != environment->end())
	{
		(*environment)["Target"]->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(CHARGE_ATTRIBUTE_ID,
																							  Modifier::ASSOCIATION_SUB_RATE,
																							  (*environment)["Self"]->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID).get(),
																							  isAssistance_,
																							  isOffensive_,
																							  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

EffectInterpreter* EffectLeechInterpreter::clone() const
{
	return new EffectLeechInterpreter(*this);
}
