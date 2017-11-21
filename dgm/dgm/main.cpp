//
//  main.cpp
//  dgm
//
//  Created by Artem Shimanski on 31.10.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

#include <iostream>
#include "SQLiteDatabase.hpp"
#include <regex>
#include <map>
#include <sstream>
#include <list>
#include <set>

class Name {
public:
	Name(const std::string& str) {
		auto& s = str_;
		s = str;
		s = std::regex_replace(s, std::regex("(\\\\u.{4})"), "");
		s = std::regex_replace(s, std::regex("[^a-zA-Z0-9]"), "");
		if (std::regex_match(s, std::regex("^[A-Z][^A-Z]+.*"))) {
			s[0] = std::tolower(s[0]);
		}
		if (std::regex_match(s, std::regex("^\\d.*"))) {
			s = "_" + s;
		}
	};
	bool operator <(const Name& other) const {
		return str_ < other.str_;
	}
	inline const std::string& to_str() const {
		return str_;
	}
	
	bool operator == (const Name& other) {
		return other.str_ == str_;
	}
private:
	std::string str_;
};

std::ostream& operator<<(std::ostream& stream, const Name& name) {
	return stream << name.to_str();
}

void dumpAttributeTypes(SQLiteDatabase& database) {
	auto result = database.fetch<std::string, Optional<std::string>, double, bool, bool>("select a.attributeName, b.attributeName as maxAttributeName, a.defaultValue, a.stackable, a.highIsGood from dgmAttributeTypes as a left join dgmAttributeTypes as b on a.maxAttributeID = b.attributeID group by a.attributeName order by a.rowid");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"\n" << std::endl
	<< "namespace dgmpp2 {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Attributes {" << std::endl;
	//<< "		constexpr MetaInfo::Attribute attributes[] {" << std::endl;
	
	std::list<std::string> names;
	
	while (auto row = result.next()) {
		auto attributeName = Name(row.get<0>());
		auto c1 = row.get<1>();
		auto maxAttributeName = Name(c1 ? *c1 : "none");
		auto defaultValue = row.get<2>();
		auto isStackable = row.get<3>();
		auto highIsGood = row.get<4>();
		
		std::cout << "\t\t\t"
		<< "constexpr MetaInfo::Attribute " << attributeName << " = {AttributeID::" << attributeName << ", AttributeID::" << maxAttributeName << ", " << defaultValue << ", " << isStackable << ", " << highIsGood << "};" << std::endl;
		names.push_back(attributeName.to_str());
	}
	
	std::cout << "\t\t}\n" << std::endl
//	<< "using namespace Attributes;" << std::endl
	<< "		constexpr const MetaInfo::Attribute* attributes[] {" << std::endl;
	
	std::transform(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, ", "), [](const auto& i) {
		return "&Attributes::" + i;
	});
	
	std::cout << "\t\t};" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
}

auto attribute(const Name& attributeName, double value, int rowID) {
	std::stringstream str;
//	str << "\t\t\t\t{attributes[" << rowID - 1 << "], " << value << "}, //" << attributeName ;
	str << "_A(&Attributes::" << attributeName << ", " << value << ")";
	return str.str();
}

auto dumpItemAttributes(SQLiteDatabase& database, int typeID) {
	auto result = database.fetch<std::string, double, int>("select attributeName, value, a.rowid from dgmAttributeTypes as a, dgmTypeAttributes as b where a.attributeID=b.attributeID and b.typeID = " + std::to_string(typeID) + " order by a.attributeID");
	
	std::list<std::string> attributes;
	while (auto row = result.next()) {
		auto attributeName = Name(row.get<0>());
		
		if (attributeName.to_str() == "radius" ||
			attributeName.to_str() == "mass" ||
			attributeName.to_str() == "volume" ||
			attributeName.to_str() == "capacity" ||
			attributeName.to_str() == "raceID") {
			continue;
		}
		auto value = row.get<1>();
		auto rowID = row.get<2>();
		attributes.push_back(attribute(attributeName, value, rowID));
	}
	return attributes;
}

auto dumpItemEffects(SQLiteDatabase& database, int typeID) {
	auto result = database.fetch<std::string, int>("SELECT effectName, a.rowid FROM dgmEffects AS a, dgmTypeEffects AS b WHERE a.effectID = b.effectID AND b.typeID = " + std::to_string(typeID) + " order by effectCategory");
	
	std::list<std::string> effects;
	while (auto row = result.next()) {
		auto effectName = Name(row.get<0>());
		auto rowID = row.get<1>();
		
		std::stringstream str;
//		str << "\t\t\t\t{effects[" << rowID - 1 << "]}, //" << effectName ;
		str << "&Effects::" << effectName ;

		effects.push_back(str.str());
	}
	return effects;
}

auto dumpItemRequiredSkills(SQLiteDatabase& database, int typeID) {
	auto result = database.fetch<std::string>("SELECT a.typeName FROM invTypes AS a, dgmTypeAttributes AS b WHERE b.attributeID IN (SELECT attributeID from dgmAttributeTypes WHERE attributeName LIKE \"requiredSkill_\") AND a.typeID=b.value AND b.typeID=" + std::to_string(typeID) + " ORDER BY b.attributeID");
	
	std::list<std::string> skills;
	while (auto row = result.next()) {
		auto typeName = Name(row.get<0>());
		
		std::stringstream str;
		str << "TypeID::" << typeName;
		
		skills.push_back(str.str());
	}
	return skills;
}

void dumpItems(SQLiteDatabase& database) {
	auto result = database.fetch<int, std::string, std::string, std::string, Optional<double>, Optional<double>, Optional<double>, Optional<double>, Optional<int>>("select typeID, typeName, b.groupName, c.categoryName, radius, mass, volume, capacity, raceID from invTypes as a, invGroups as b, invCategories as c where a.groupID=b.groupID and b.categoryID=c.categoryID order by typeID");

	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"" << std::endl
	<< "#include \"Attributes.hpp\"" << std::endl
	<< "#include \"Effects.hpp\"\n" << std::endl
	<< "namespace dgmpp2 {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Types {" << std::endl
	<< "			using namespace MetaInfo;" << std::endl;
//	<< "		constexpr MetaInfo::Type types[] {" << std::endl;

	std::cout << "\t\t\t"
	<< "constexpr auto none = MakeType(TypeID::none, GroupID::corporation, CategoryID::owner, _attributes(), _effects(), _typeIDs());" << std::endl;

	
	auto radiusID = database.fetch<int>("select rowid from dgmAttributeTypes where attributeName == \"radius\"").next().get<0>();
	auto massID = database.fetch<int>("select rowid from dgmAttributeTypes where attributeName == \"mass\"").next().get<0>();
	auto volumeID = database.fetch<int>("select rowid from dgmAttributeTypes where attributeName == \"volume\"").next().get<0>();
	auto capacityID = database.fetch<int>("select rowid from dgmAttributeTypes where attributeName == \"capacity\"").next().get<0>();
	auto raceIDID = database.fetch<int>("select rowid from dgmAttributeTypes where attributeName == \"raceID\"").next().get<0>();
	
//	int n = 0;
	std::list<std::string> names = {"none"};
	std::set<std::string> unique = {"none"};
	
	
	while (auto row = result.next()) {
//		if (n++ > 100)
//			break;
		
		auto typeID = row.get<0>();
		auto base = Name(row.get<1>()).to_str();
		if (base.empty())
			continue;
		
		auto groupName = Name(row.get<2>());
		auto categoryName = Name(row.get<3>());
		auto radius = row.get<4>();
		auto mass = row.get<5>();
		auto volume = row.get<6>();
		auto capacity = row.get<7>();
		auto raceID = row.get<8>();
		auto attributes = dumpItemAttributes(database, typeID);
		
		auto typeName = base;
		int i = 1;
		while (unique.find(typeName) != unique.end()) {
			typeName = base + "_" + std::to_string(i++);
		}
		unique.insert(typeName);

		if (radius && *radius > 0)
			attributes.push_front(attribute(Name("radius"), *radius, radiusID));
		if (mass && *mass > 0)
			attributes.push_front(attribute(Name("mass"), *mass, massID));
		if (volume && *volume > 0)
			attributes.push_front(attribute(Name("volume"), *volume, volumeID));
		if (capacity && *capacity > 0)
			attributes.push_front(attribute(Name("capacity"), *capacity, capacityID));
		if (raceID && *raceID > 0)
			attributes.push_front(attribute(Name("raceID"), *raceID, raceIDID));

		std::cout << "\t\t\t"
		<< "constexpr auto " << typeName << " = MakeType(TypeID::" << typeName << ", GroupID::" << groupName << ", CategoryID::" << categoryName;
		
		std::cout << ",\n				_attributes(";
		bool isFirst = true;
		for (const auto& i: attributes) {
			if (!isFirst) {
				std::cout << ", ";
			}
			isFirst = false;
			std::cout << i;
		}
		
		std::cout << "),\n				_effects(";
		isFirst = true;
		for (const auto& i: dumpItemEffects(database, typeID)) {
			if (!isFirst) {
				std::cout << ", ";
			}
			isFirst = false;
			std::cout << i;
		}
		
		std::cout << "),\n				_typeIDs(";
		isFirst = true;
		for (const auto& i: dumpItemRequiredSkills(database, typeID)) {
			if (!isFirst) {
				std::cout << ", ";
			}
			isFirst = false;
			std::cout << i;
		}
		std::cout << "));" << std::endl;
		names.push_back(typeName);
	}
	
	std::cout << "\t\t}\n" << std::endl
//	<< "using namespace Types;" << std::endl
	<< "		constexpr const MetaInfo::Type* types[] {" << std::endl;

	std::transform(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, ", "), [](const auto& i) {
		return "&Types::" + i;
	});

	
	std::cout << "\t\t};" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
}

void dumpIDs(SQLiteDatabase& database, const std::string& name, const std::string& sql) {
	auto result = database.fetch<int, std::string>(sql);

	std::cout << "#pragma once\n\n"
	"namespace dgmpp {\n"
	"\tenum class " << name << ": unsigned short {\n"
	"\t\tnone = 0";

	std::set<std::string> unique;

	while (auto row =  result.next()) {
		auto id = row.get<0>();
		auto base = Name(row.get<1>()).to_str();
		if (name.empty())
			continue;
		auto name = base;
		int i = 1;
		while (unique.find(name) != unique.end()) {
			name = base + "_" + std::to_string(i++);
		}
		
		std::cout << ",\n\t\t" << name << " = " << id;
		unique.insert(name);
	}
	std::cout << "\n\t};\n" << "}" << std::endl;
}

struct Domain {
	Domain(int i): val(i) {};
	std::string to_str () {
		switch (val) {
			case 0:
				return "self";
			case 1:
				return "character";
			case 2:
				return "ship";
			case 3:
				return "gang";
			case 4:
				return "area";
			case 5:
				return "target";
			case 6:
				return "other";
			case 7:
				return  "structure";
			default:
				throw 0;
		}
	}
	int val;
};

struct ModifierType {
	ModifierType(int i): val(i) {};
	std::string to_str () {
		switch (val) {
			case 0:
				return "item";
			case 1:
				return "location";
			case 2:
				return "locationGroup";
			case 3:
				return "locationRequiredSkill";
			case 4:
				return "ownerRequiredSkill";
			case 5:
				return  "locationRequiredDomainSkill";
			default:
				throw 0;
		}
	}
	int val;
};

struct Association {
	Association(int i): val(i) {};
	std::string to_str () {
		switch (val) {
			case 0:
				return "preAssignment";
			case 1:
				return "modAdd";
			case 2:
				return "modSub";
			case 3:
				return "preDiv";
			case 4:
				return "preMul";
			case 5:
				return "postPercent";
			case 6:
				return "postDiv";
			case 7:
				return "postMul";
			case 8:
				return "postAssignment";
			case 9:
				return "skillTime";
			case 10:
				return "addRate";
			case 11:
				return  "subRate";
			default:
				throw 0;
		}
	}
	int val;
};

void dumpModifiers(SQLiteDatabase& database) {
	auto result = database.fetch<int, int, int, std::string, std::string, int, Optional<std::string>, Optional<std::string>, Optional<int>>("select a.modifierID, domain, type, b.attributeName as modified, c.attributeName as modifying, association, d.typeName, e.groupName, a.requiredID from dgmModifiers as a left join dgmAttributeTypes as b on a.modifiedAttributeID=b.attributeID left join dgmAttributeTypes as c on a.modifyingAttributeID=c.attributeID left join invTypes as d on a.requiredID=d.typeID left join invGroups as e on a.requiredID=e.groupID order by modifierID");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"\n" << std::endl
	<< "namespace dgmpp2 {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Modifiers {" << std::endl;
//	<< "		constexpr MetaInfo::Modifier modifiers[] {" << std::endl;

	
	while (auto row = result.next()) {
		auto modifierID = row.get<0>();
		auto domain = Domain(row.get<1>());
		auto type = ModifierType(row.get<2>());
		auto modified = Name(row.get<3>());
		auto modifying = Name(row.get<4>());
		auto association = Association(row.get<5>());
		auto typeName = row.get<6>();
		auto groupName = row.get<7>();
		auto requiredID = row.get<8>();

		std::cout << "\t\t\t"
		<< "constexpr MetaInfo::Modifier modifier" << modifierID << " = {MetaInfo::Modifier::ModifierType::" << type.to_str()
		<< ", MetaInfo::Modifier::Association::" << association.to_str()
		<< ", MetaInfo::Modifier::Domain::" << domain.to_str()
		<< ", AttributeID::" << modified
		<< ", AttributeID::" << modifying;

		switch (type.val) {
			case 2:
				std::cout << ", GroupID::" << Name(*groupName);
				break;
			case 3:
			case 4:
				std::cout << ", TypeID::" << Name(*typeName);
				break;
			case 5:
				std::cout << ", MetaInfo::Modifier::Domain::" << Domain(*requiredID).to_str();
				break;
			default:
				break;
		}
		std::cout << "};" << std::endl;

	}
	
	std::cout
	<< "		}" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
}

struct EffectCategory {
	EffectCategory(int i): val(i) {};
	std::string to_str () {
		switch (val) {
			case 0:
				return "generic";
			case 1:
				return "active";
			case 2:
				return "target";
			case 4:
				return "passive";
			case 5:
				return "overloaded";
			case 6:
				return "dungeon";
			case 7:
				return "system";
			default:
				throw 0;
		}
	}
	int val;
};

void dumpEffects(SQLiteDatabase& database) {
	auto result = database.fetch<int, std::string, int, bool, bool>("SELECT effectID, effectName, effectCategory, isOffensive, isAssistance FROM dgmEffects ORDER BY rowid");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"" << std::endl
	<< "#include \"Modifiers.hpp\"\n" << std::endl
	<< "namespace dgmpp2 {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Effects {" << std::endl
	<< "			using namespace MetaInfo;" << std::endl;
//	<< "			using namespace Modifiers;" << std::endl;
//	<< "		constexpr MetaInfo::Effect effects[] {" << std::endl;
	
	
	while (auto row = result.next()) {
		auto effectID = row.get<0>();
		auto effectName = Name(row.get<1>());
		auto category = EffectCategory(row.get<2>());
		auto isOffensive = row.get<3>();
		auto isAssistance = row.get<4>();

		std::cout << "\t\t\t"
		<< "constexpr auto " << effectName << " = MakeEffect(EffectID::" << effectName
		<< ", MetaInfo::Effect::Category::" << category.to_str()
		<< ", " << isOffensive
		<< ", " << isAssistance
		<< ", _modifiers(";
		
		auto result = database.fetch<int>("SELECT modifierID FROM dgmEffectModifiers WHERE effectID == " + std::to_string(effectID) + " ORDER BY modifierID");
//		std::cout << "\t\t\t\t";
		bool isFirst = true;
		while (auto row = result.next()) {
			if (!isFirst) {
				std::cout << ", ";
			}
			std::cout << "&Modifiers::modifier" << row.get<0>();
			isFirst = false;
		}
		
		std::cout << "));" << std::endl;
	}
	
	std::cout
	<< "		}" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
}

void dumpSkills(SQLiteDatabase& database) {
	auto result = database.fetch<std::string>("SELECT typeName FROM invTypes AS a, invGroups AS b WHERE a.groupID=b.groupID and b.categoryID=16 ORDER BY a.rowID");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"Types.hpp\"\n" << std::endl
	<< "namespace dgmpp2 {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		constexpr const MetaInfo::Type* skills[] = {" << std::endl;
	
	std::set<std::string> unique;

	while (auto row = result.next()) {
		auto base = Name(row.get<0>()).to_str();
		if (base.empty())
			continue;

		auto typeName = base;
		int i = 1;
		while (unique.find(typeName) != unique.end()) {
			typeName = base + "_" + std::to_string(i++);
		}
		unique.insert(typeName);

		std::cout << "\t\t\t"
		<< "&Types::" << typeName << "," << std::endl;
	}
	
	std::cout
	<< "		};" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
}

int main(int argc, const char * argv[]) {
	if (argc == 3) {
		std::cout << std::boolalpha;
		
		std::string databasePath = argv[1];
		std::string action = argv[2];
		auto database = SQLiteDatabase(databasePath);
		
		if (action == "--attributeIDs") {
			dumpIDs(database, "AttributeID", "SELECT attributeID, attributeName FROM dgmAttributeTypes ORDER BY attributeID");
			return 0;
		}
		else if (action == "--typeIDs") {
			dumpIDs(database, "TypeID", "SELECT typeID, typeName FROM invTypes ORDER BY typeID");
			return 0;
		}
		else if (action == "--groupIDs") {
			dumpIDs(database, "GroupID", "SELECT groupID, groupName FROM invGroups GROUP BY groupName ORDER BY groupID");
			return 0;
		}
		else if (action == "--categoryIDs") {
			dumpIDs(database, "CategoryID", "SELECT categoryID, categoryName FROM invCategories ORDER BY categoryID");
			return 0;
		}
		else if (action == "--effectIDs") {
			dumpIDs(database, "EffectID", "SELECT effectID, effectName FROM dgmEffects ORDER BY effectID");
			return 0;
		}
		else if (action == "--attributes") {
			dumpAttributeTypes(database);
			return 0;
		}
		else if (action == "--types") {
			dumpItems(database);
			return 0;
		}
		else if (action == "--modifiers") {
			dumpModifiers(database);
			return 0;
		}
		else if (action == "--effects") {
			dumpEffects(database);
			return 0;
		}
		else if (action == "--skills") {
			dumpSkills(database);
			return 0;
		}
	}
	
	std::cout << "\
usage: dgm database_path action\n\
actions:\n\
	--attributeIDs\n\
	--typeIDs\n\
	--groupIDs\n\
	--categoryIDs\n\
	--effectIDs\n\
	--attributes\n\
	--types\n\
	--modifiers\n\
	--effects" << std::endl;
	
	return 1;
}
