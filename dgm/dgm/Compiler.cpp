//
//  Compiler.cpp
//  dgm
//
//  Created by Artem Shimanski on 28.11.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

#include "Compiler.hpp"
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <memory>
#include <typeinfo>
#include <type_traits>
#include <set>

namespace Compiler {
	sqlite3 *db = NULL;
	void exec(const std::string sql, std::function<bool (sqlite3_stmt* stmt)> callback) {
		sqlite3_stmt* stmt = NULL;
		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		if (stmt) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				if (callback && !callback(stmt))
				break;
			}
			sqlite3_finalize(stmt);
		}
	}
	
	int32_t getAttributeID(const std::string& attributeName) {
		std::stringstream s;
		s << "select attributeID from dgmAttributeTypes where attributeName= \"" << attributeName << "\"";
		int32_t attributeID = 0;
		exec(s.str(), [&](sqlite3_stmt * stmt) -> bool {
			attributeID = sqlite3_column_int(stmt, 0);
			return false;
		});
		return attributeID;
	}
	
	int32_t getGroupID(const std::string& groupName) {
		std::stringstream s;
		s << "select groupID from invGroups where groupName= \"" << groupName << "\"";
		int32_t groupID = 0;
		exec(s.str(), [&](sqlite3_stmt * stmt) -> bool {
			groupID = sqlite3_column_int(stmt, 0);
			return false;
		});
		return groupID;
	}
	
	int32_t getTypeID(const std::string& typeName) {
		std::stringstream s;
		s << "select typeID from invTypes where typeName= \"" << typeName << "\"";
		int32_t typeID = 0;
		exec(s.str(), [&](sqlite3_stmt * stmt) -> bool {
			typeID = sqlite3_column_int(stmt, 0);
			return false;
		});
		return typeID;
	}
	
	DomainType getDomainID(const std::string& domain) {
		if (domain == "Self")
			return DomainType::self;
		else if (domain == "Char")
			return DomainType::character;
		else if (domain == "Ship")
			return DomainType::ship;
		else if (domain == "Target")
			return DomainType::target;
		else if (domain == "Area")
			return DomainType::area;
		else if (domain == "Other")
			return DomainType::other;
		else if (domain == "Gang")
			return DomainType::gang;
		else if (domain == "Structure")
			return DomainType::structure;
		else
			throw std::bad_typeid();
	}
	
	AssociationType getAssociationID(const std::string& association) {
		if (association == "PreAssignment")
			return AssociationType::preAssignment;
		else if (association == "PreDiv")
			return AssociationType::preDiv;
		else if (association == "PreMul")
			return AssociationType::preMul;
		else if (association == "ModAdd")
			return AssociationType::modAdd;
		else if (association == "ModSub")
			return AssociationType::modSub;
		else if (association == "PostPercent")
			return AssociationType::postPercent;
		else if (association == "PostMul")
			return AssociationType::postMul;
		else if (association == "PostDiv")
			return AssociationType::postDiv;
		else if (association == "PostAssignment")
			return AssociationType::postAssignment;
		else if (association == "9")
			return AssociationType::skillTime;
		else if (association == "AddRate")
			return AssociationType::addRate;
		else if (association == "SubRate")
			return AssociationType::subRate;
		else
			throw std::bad_typeid();
	}
	
	
	int32_t currentExpressionID;
	std::map<int32_t, std::set<Modifier>> modifiers;
	std::map<int32_t, std::list<Mutator>> mutators;
	std::set<Modifier> uniqueModifiers;
	
	
	Attribute Domain::getAttribute(const AttributeID& attributeID) {
		return Attribute(*this, attributeID);
	}
	
	TypeID Domain::getTypeID() {
		return TypeID(domain);
	}
	
	Domain Domain::getLocationGroup(const GroupID& groupID) {
		return Domain(*this, groupID);
	}
	
	Domain Domain::getRequiredSkill(const TypeID& typeID) {
		return Domain(*this, typeID);
	}
	
	bool Attribute::set(float value) {
		throw *this;
		//		mutators[currentExpressionID].push_back(Mutator(*this, value, Mutator::MutatorTypeSet));
		//		return true;
	}
	bool Attribute::inc(float value) {
		throw *this;
		//		mutators[currentExpressionID].push_back(Mutator(*this, value, Mutator::MutatorTypeInc));
		//		return true;
	}
	bool Attribute::dec(float value) {
		throw *this;
		//		mutators[currentExpressionID].push_back(Mutator(*this, value, Mutator::MutatorTypeDec));
		//		return true;
	}
	bool Attribute::dec(const AttributeID& attributeID) {
		throw *this;
		//		mutators[currentExpressionID].push_back(Mutator(*this, attributeID, Mutator::MutatorTypeDec));
		//		return true;
	}
	bool Attribute::inc(const AttributeID& attributeID) {
		throw *this;
		//		mutators[currentExpressionID].push_back(Mutator(*this, attributeID, Mutator::MutatorTypeInc));
		//		return true;
	}
	bool Attribute::set(const AttributeID& attributeID) {
		throw *this;
		//		mutators[currentExpressionID].push_back(Mutator(*this, attributeID, Mutator::MutatorTypeSet));
		//		return true;
	}
	Association Attribute::getAssociation(const std::string& name) {
		return Association(*this, name);
	}
	
	bool Association::addItemModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(ModifierType::item, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addLocationGroupModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(ModifierType::locationGroup, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addLocationModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(ModifierType::location, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addLocationRequiredSkillModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(attribute.domain.requiredSkill.typeID > 0 ? ModifierType::locationRequiredSkill : ModifierType::locationRequiredDomainSkill, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addOwnerRequiredSkillModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(attribute.domain.requiredSkill.typeID > 0 ? ModifierType::ownerRequiredSkill : ModifierType::locationRequiredDomainSkill, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	
	std::ostream& operator<<(std::ostream& os, const Modifier& modifier) {
		os << "INSERT INTO dgmModifiers VALUES ("
		<< modifier.modifierID << ","
		<< static_cast<int>(getDomainID(modifier.modifiedAssociation.attribute.domain.domain)) << ","
		<< modifier.type << ","
		<< modifier.modifiedAssociation.attribute.attributeID.attributeID << ","
		<< modifier.modifyingAttributeID.attributeID << ","
		<< static_cast<int>(getAssociationID(modifier.modifiedAssociation.name)) << ",";
		switch (modifier.type) {
			case ModifierType::item:
			case ModifierType::location:
				os << "NULL";
				break;
			case ModifierType::locationGroup:
				os << modifier.modifiedAssociation.attribute.domain.locationGroup.groupID;
				break;
			case ModifierType::locationRequiredSkill:
			case ModifierType::ownerRequiredSkill:
				os << modifier.modifiedAssociation.attribute.domain.requiredSkill.typeID;
				break;
			case ModifierType::locationRequiredDomainSkill:
				os << static_cast<int>(getDomainID(modifier.modifiedAssociation.attribute.domain.requiredSkill.domain));
				break;
			default:
				throw std::bad_typeid();
				break;
		}
		os << ");";
		
		return os;
	}
	
	
	std::map<int32_t, std::shared_ptr<Expression>> expressions;
	
}

void compile (SQLiteDatabase& database) {
	std::cout << "CREATE TABLE \"dgmModifiers\" (\n\
	\"modifierID\"  INTEGER NOT NULL,\n\
	\"domain\"  INTEGER NOT NULL,\n\
	\"type\"  INTEGER NOT NULL,\n\
	\"modifiedAttributeID\"  INTEGER NOT NULL,\n\
	\"modifyingAttributeID\"  INTEGER NOT NULL,\n\
	\"association\"  INTEGER NOT NULL,\n\
	\"requiredID\"  DEFAULT NULL,\n\
	PRIMARY KEY (\"modifierID\"));" << std::endl;
	
	std::cout << "CREATE TABLE \"dgmEffectModifiers\" (\n\
	\"effectID\"  INTEGER NOT NULL,\n\
	\"modifierID\"  INTEGER NOT NULL,\n\
	PRIMARY KEY (\"effectID\", \"modifierID\"));" << std::endl;

	
	using namespace Compiler;
	{
		auto result = database.fetch<int, int, int, int, Optional<std::string>, std::string, int, int, int>("select expressionID, operandID, arg1, arg2, expressionValue, expressionName, expressionTypeID, expressionGroupID, expressionAttributeID from dgmExpressions");
		
		while (auto row = result.next()) {
			auto expression = std::make_shared<Expression>();
			expression->operandID = row.get<1>();
			expression->arg1 = row.get<2>();
			expression->arg2 = row.get<3>();
			expression->value = row.get<4>() ? *row.get<4>() : "";
			expression->name = row.get<5>();
			expression->typeID = row.get<6>();
			expression->groupID = row.get<7>();
			expression->attributeID = row.get<8>();
			expressions[row.get<0>()] = expression;
		}
	}

	{

		auto result = database.fetch<int, int, std::string>("select a.effectID, preExpression, effectName from dgmEffects as a, dgmTypeEffects as b where a.effectID=b.effectID group by a.effectID");
		
		while (auto row = result.next()) {
			auto effectID = row.get<0>();
			auto preExpression = row.get<1>();
			
			try {
				currentExpressionID = preExpression;
				if (mutators.find((currentExpressionID)) == mutators.end() && modifiers.find(currentExpressionID) == modifiers.end())
				expressions[currentExpressionID]->exec();
				
				for (const auto& modifier: modifiers[preExpression]) {
					std::cout << "INSERT INTO dgmEffectModifiers VALUES (" << effectID << "," << modifier.modifierID << ");" << std::endl;
				}
			} catch (...) {
				std::cout << row.get<2>() << std::endl;
			}
			
		}

	}
	
	for (const auto& modifier: uniqueModifiers)
		std::cout << modifier << std::endl;
	
}
