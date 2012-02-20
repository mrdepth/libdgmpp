#include "EffectEnergyDestabilizationNewInterpreter.h"
#include "Engine.h"
#include "Item.h"
#include "Attribute.h"
#include "Modifier.h"
#include "Character.h"

using namespace eufe;

EffectEnergyDestabilizationNewInterpreter::EffectEnergyDestabilizationNewInterpreter(Engine* engine, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
}

EffectEnergyDestabilizationNewInterpreter::~EffectEnergyDestabilizationNewInterpreter(void)
{
}

bool EffectEnergyDestabilizationNewInterpreter::addEffect(Environment* environment)
{
	if (environment->find("Target") != environment->end())
	{
		(*environment)["Target"]->addItemModifier(boost::shared_ptr<Modifier>(new Modifier(CHARGE_ATTRIBUTE_ID,
																						   Modifier::ASSOCIATION_SUB_RATE,
																						   (*environment)["Self"]->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID).get(),
																						   isAssistance_,
																						   isOffensive_,
																						   dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

bool EffectEnergyDestabilizationNewInterpreter::removeEffect(Environment* environment)
{
	if (environment->find("Target") != environment->end())
	{
		(*environment)["Target"]->removeItemModifier(boost::shared_ptr<Modifier>(new Modifier(CHARGE_ATTRIBUTE_ID,
																							  Modifier::ASSOCIATION_SUB_RATE,
																							  (*environment)["Self"]->getAttribute(ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID).get(),
																							  isAssistance_,
																							  isOffensive_,
																							  dynamic_cast<Character*>((*environment)["Char"]))));
	}
	return 1;
}

EffectInterpreter* EffectEnergyDestabilizationNewInterpreter::clone() const
{
	return new EffectEnergyDestabilizationNewInterpreter(*this);
}
