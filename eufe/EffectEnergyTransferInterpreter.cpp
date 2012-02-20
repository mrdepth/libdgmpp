#include "EffectEnergyTransferInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectEnergyTransferInterpreter::EffectEnergyTransferInterpreter(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectEnergyTransferInterpreter::~EffectEnergyTransferInterpreter(void)
{
}

bool EffectEnergyTransferInterpreter::addEffect(Environment* environment)
{
	if (environment->find("Target") != environment->end())
	{
		(*environment)["Target"]->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(CHARGE_ATTRIBUTE_ID,
																						   Modifier::ASSOCIATION_ADD_RATE,
																						   (*environment)["Self"]->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID).get(),
																						   isAssistance_,
																						   isOffensive_,
																						   dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

bool EffectEnergyTransferInterpreter::removeEffect(Environment* environment)
{
	if (environment->find("Target") != environment->end())
	{
		(*environment)["Target"]->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(CHARGE_ATTRIBUTE_ID,
																							  Modifier::ASSOCIATION_ADD_RATE,
																							  (*environment)["Self"]->getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID).get(),
																							  isAssistance_,
																							  isOffensive_,
																							  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

EffectInterpreter* EffectEnergyTransferInterpreter::clone() const
{
	return new EffectEnergyTransferInterpreter(*this);
}
