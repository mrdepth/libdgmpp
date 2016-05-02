#include "Compiler.h"
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <cstdlib>
#include <limits>
#include <sstream>
#include "Modifier.h"
#include <memory>
#include <typeinfo>
#include <type_traits>

using namespace dgmpp;


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
	
	dgmpp::Modifier::Domain getDomainID(const std::string& domain) {
		if (domain == "Self")
			return dgmpp::Modifier::DOMAIN_SELF;
		else if (domain == "Char")
			return dgmpp::Modifier::DOMAIN_CHAR;
		else if (domain == "Ship")
			return dgmpp::Modifier::DOMAIN_SHIP;
		else if (domain == "Target")
			return dgmpp::Modifier::DOMAIN_TARGET;
		else if (domain == "Area")
			return dgmpp::Modifier::DOMAIN_AREA;
		else if (domain == "Other")
			return dgmpp::Modifier::DOMAIN_OTHER;
		else if (domain == "Gang")
			return dgmpp::Modifier::DOMAIN_GANG;
		else if (domain == "Structure")
			return dgmpp::Modifier::DOMAIN_STRUCTURE;
		else
			throw std::bad_typeid();
	}
	
	dgmpp::Modifier::Association getAssociationID(const std::string& association) {
		if (association == "PreAssignment")
			return dgmpp::Modifier::ASSOCIATION_PRE_ASSIGNMENT;
		else if (association == "PreDiv")
			return dgmpp::Modifier::ASSOCIATION_PRE_DIV;
		else if (association == "PreMul")
			return dgmpp::Modifier::ASSOCIATION_PRE_MUL;
		else if (association == "ModAdd")
			return dgmpp::Modifier::ASSOCIATION_MOD_ADD;
		else if (association == "ModSub")
			return dgmpp::Modifier::ASSOCIATION_MOD_SUB;
		else if (association == "PostPercent")
			return dgmpp::Modifier::ASSOCIATION_POST_PERCENT;
		else if (association == "PostMul")
			return dgmpp::Modifier::ASSOCIATION_POST_MUL;
		else if (association == "PostDiv")
			return dgmpp::Modifier::ASSOCIATION_POST_DIV;
		else if (association == "PostAssignment")
			return dgmpp::Modifier::ASSOCIATION_POST_ASSIGNMENT;
		else if (association == "9")
			return dgmpp::Modifier::ASSOCIATION_SKILL_TIME;
		else if (association == "AddRate")
			return dgmpp::Modifier::ASSOCIATION_ADD_RATE;
		else if (association == "SubRate")
			return dgmpp::Modifier::ASSOCIATION_SUB_RATE;
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
		auto modifier = uniqueModifiers.emplace(dgmpp::Modifier::ITEM_MODIFIER, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addLocationGroupModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(dgmpp::Modifier::LOCATION_GROUP_MODIFIER, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addLocationModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(dgmpp::Modifier::LOCATION_MODIFIER, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addLocationRequiredSkillModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(attribute.domain.requiredSkill.typeID > 0 ? dgmpp::Modifier::LOCATION_REQUIRED_SKILL_MODIFIER : dgmpp::Modifier::LOCATION_REQUIRED_DOMAIN_SKILL_MODIFIER, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	bool Association::addOwnerRequiredSkillModifier(const AttributeID attributeID) {
		auto modifier = uniqueModifiers.emplace(attribute.domain.requiredSkill.typeID > 0 ? dgmpp::Modifier::OWNER_REQUIRED_SKILL_MODIFIER : dgmpp::Modifier::LOCATION_REQUIRED_DOMAIN_SKILL_MODIFIER, *this, attributeID, uniqueModifiers.size() + 1);
		modifiers[currentExpressionID].insert(*modifier.first);
		return true;
	}
	
	std::ostream& operator<<(std::ostream& os, const Modifier& modifier) {
		os << "INSERT INTO dgmModifiers VALUES ("
		<< modifier.modifierID << ","
		<< getDomainID(modifier.modifiedAssociation.attribute.domain.domain) << ","
		<< modifier.type << ","
		<< modifier.modifiedAssociation.attribute.attributeID.attributeID << ","
		<< modifier.modifyingAttributeID.attributeID << ","
		<< getAssociationID(modifier.modifiedAssociation.name) << ",";
		switch (modifier.type) {
			case dgmpp::Modifier::ITEM_MODIFIER:
			case dgmpp::Modifier::LOCATION_MODIFIER:
				os << "NULL";
				break;
			case dgmpp::Modifier::LOCATION_GROUP_MODIFIER:
				os << modifier.modifiedAssociation.attribute.domain.locationGroup.groupID;
				break;
			case dgmpp::Modifier::LOCATION_REQUIRED_SKILL_MODIFIER:
			case dgmpp::Modifier::OWNER_REQUIRED_SKILL_MODIFIER:
				os << modifier.modifiedAssociation.attribute.domain.requiredSkill.typeID;
				break;
			case dgmpp::Modifier::LOCATION_REQUIRED_DOMAIN_SKILL_MODIFIER:
				os << getDomainID(modifier.modifiedAssociation.attribute.domain.requiredSkill.domain);
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

using namespace Compiler;


int main(int argc, char* argv[])
{
	
	if (argc != 3) {
		std::cout<<"Usage: compiler source_database.sqlite output_dir"<<std::endl;
		return 0;
	}
	const char* databasePath = argv[1];
	sqlite3_open(databasePath, &db);
	
	exec("select expressionID, operandID, arg1, arg2, expressionValue, expressionName, expressionTypeID, expressionGroupID, expressionAttributeID from dgmExpressions", [&](sqlite3_stmt* stmt) -> bool {
		auto expression = std::make_shared<Expression>();
		expression->operandID = sqlite3_column_int(stmt, 1);
		expression->arg1 = sqlite3_column_int(stmt, 2);
		expression->arg2 = sqlite3_column_int(stmt, 3);
		expression->value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)) ?: "";
		expression->name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)) ?: "";
		expression->typeID = sqlite3_column_int(stmt, 6);
		expression->groupID = sqlite3_column_int(stmt, 7);
		expression->attributeID = sqlite3_column_int(stmt, 8);
		expressions[sqlite3_column_int(stmt, 0)] = expression;
		return true;
	});
	
	std::string outDir = argv[2];
	std::ofstream modifiersStream;
	modifiersStream.open(outDir + "/dgmModifiers.sql");
	modifiersStream << "CREATE TABLE \"dgmModifiers\" (\
	\"modifierID\"  INTEGER NOT NULL,\
	\"domain\"  INTEGER NOT NULL,\
	\"type\"  INTEGER NOT NULL,\
	\"modifiedAttributeID\"  INTEGER NOT NULL,\
	\"modifyingAttributeID\"  INTEGER NOT NULL,\
	\"association\"  INTEGER NOT NULL,\
	\"requiredID\"  DEFAULT NULL,\
	PRIMARY KEY (\"modifierID\"));" << std::endl;
	
	std::ofstream effectModifiersStream;
	effectModifiersStream.open(outDir + "/dgmEffectModifiers.sql");
	effectModifiersStream << "CREATE TABLE \"dgmEffectModifiers\" (\
	\"effectID\"  INTEGER NOT NULL,\
	\"modifierID\"  INTEGER NOT NULL,\
	PRIMARY KEY (\"effectID\", \"modifierID\"));" << std::endl;

	
	exec("select a.effectID, preExpression, effectName from dgmEffects as a, dgmTypeEffects as b where a.effectID=b.effectID group by a.effectID", [&](sqlite3_stmt* stmt) -> bool {
		int32_t effectID = sqlite3_column_int(stmt, 0);
		int32_t preExpression = sqlite3_column_int(stmt, 1);
		currentExpressionID = preExpression;
		
		try {
			if (mutators.find((preExpression)) == mutators.end() && modifiers.find(preExpression) == modifiers.end())
				expressions[preExpression]->exec();
			
			for (const auto& modifier: modifiers[preExpression]) {
				effectModifiersStream << "INSERT INTO dgmEffectModifiers VALUES (" << effectID << "," << modifier.modifierID << ");" << std::endl;
			}
		} catch (...) {
			std::cout << sqlite3_column_text(stmt, 2) << std::endl;
		}
		return true;
	});
	for (const auto& modifier: uniqueModifiers)
		modifiersStream << modifier << std::endl;;

	modifiersStream.close();
	effectModifiersStream.close();
	
	return 0;
}