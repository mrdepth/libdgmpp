#include "EffectPrototype.h"
#include "Engine.h"

using namespace dgmpp;

std::shared_ptr<EffectPrototype> EffectPrototype::getEffectPrototype(std::shared_ptr<Engine> const& engine, EffectID effectID)
{
	auto& reusableEffectPrototypes = engine->getReusableEffectPrototypes();
	auto i = reusableEffectPrototypes.find(effectID);
	if (i == reusableEffectPrototypes.end()) {
		auto effectPrototype = std::make_shared<EffectPrototype>(engine, effectID);
		reusableEffectPrototypes[effectID] = effectPrototype;
		return effectPrototype;
	}
	else
		return i->second;
}

EffectPrototype::EffectPrototype(std::shared_ptr<Engine> const& engine, EffectID effectID) : engine_(engine), effectID_(effectID), isAssistance_(false), isOffensive_(false)
{
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT effectCategory, isOffensive, isAssistance, effectName FROM dgmEffects WHERE effectID = ?");
	stmt->bindInt(1, static_cast<int>(effectID));
	
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	
	if (result->next())
	{
		category_ = static_cast<Effect::Category>(result->getInt(0));
		bool isAssistance = result->getInt(2) != 0;
		bool isOffensive = result->getInt(1) != 0;
		effectName_ = result->getText(3);
		for (auto &i: effectName_)
		{
			char c = i;
			if (!((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
				i = ' ';
		}
		isAssistance_ = isAssistance;
		isOffensive_ = isOffensive;
	}
	
	stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT a.modifierID, domain, type, modifiedAttributeID, modifyingAttributeID, association, requiredID FROM dgmModifiers AS a, dgmEffectModifiers AS b WHERE a.modifierID=b.modifierID and b.effectID = ?");
	stmt->bindInt(1, static_cast<int>(effectID));
	
	result = engine->getSqlConnector()->exec(stmt);
	auto& reusableModifierPrototypes = engine->getReusableModifierPrototypes();
	while (result->next())
	{
		ModifierID modifierID = static_cast<ModifierID>(result->getInt(0));
		
		auto i = reusableModifierPrototypes.find(modifierID);
		if (i == reusableModifierPrototypes.end()) {
			auto modifierPrototype = std::make_shared<ModifierPrototype>();
			modifierPrototype->domain = static_cast<Modifier::Domain>(result->getInt(1));
			modifierPrototype->type = static_cast<Modifier::Type>(result->getInt(2));
			modifierPrototype->modifiedAttributeID = static_cast<AttributeID>(result->getInt(3));
			modifierPrototype->modifyingAttributeID = static_cast<AttributeID>(result->getInt(4));
			modifierPrototype->association = static_cast<Modifier::Association>(result->getInt(5));
			modifierPrototype->requiredID = result->getInt(6);
			modifierPrototypes_.push_back(modifierPrototype);
			reusableModifierPrototypes[modifierID] = modifierPrototype;
		}
		else
			modifierPrototypes_.push_back(i->second);
	}
}

EffectPrototype::~EffectPrototype() {
	
}
