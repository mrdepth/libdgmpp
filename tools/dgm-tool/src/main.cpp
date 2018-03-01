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
#include "modifiersdump.hpp"

extern void compile (SQLiteDatabase& database);

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
	<< "namespace dgmpp {" << std::endl
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
	<< "namespace dgmpp {" << std::endl
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
	enum Type {
		self,
		character,
		ship,
		gang,
		area,
		target,
		other,
		structure
	};
	
	Domain(Type i): val(i) {};
	std::string to_str () const {
		switch (val) {
			case Type::self:
				return "self";
			case Type::character:
				return "character";
			case Type::ship:
				return "ship";
			case Type::gang:
				return "gang";
			case Type::area:
				return "area";
			case Type::target:
				return "target";
			case Type::other:
				return "other";
			case Type::structure:
				return  "structure";
			default:
				throw 0;
		}
	}
	Type val;
};

struct ModifierType {
	enum Type {
		item,
		location,
		locationGroup,
		locationRequiredSkill,
		ownerRequiredSkill,
		locationRequiredDomainSkill,
	};
	
	ModifierType(Type i): val(i) {};
	std::string to_str () const {
		switch (val) {
			case Type::item:
				return "item";
			case Type::location:
				return "location";
			case Type::locationGroup:
				return "locationGroup";
			case Type::locationRequiredSkill:
				return "locationRequiredSkill";
			case Type::ownerRequiredSkill:
				return "ownerRequiredSkill";
			case Type::locationRequiredDomainSkill:
				return  "locationRequiredDomainSkill";
			default:
				throw 0;
		}
	}
	Type val;
};

struct Association {
	enum Type {
		preAssignment,
		modAdd,
		modSub,
		preDiv,
		preMul,
		postPercent,
		postDiv,
		postMul,
		postAssignment,
		skillTime,
		addRate,
		subRate
	};
	
	Association(Type i): val(i) {};
	std::string to_str () const {
		switch (val) {
			case Type::preAssignment:
				return "preAssignment";
			case Type::modAdd:
				return "modAdd";
			case Type::modSub:
				return "modSub";
			case Type::preDiv:
				return "preDiv";
			case Type::preMul:
				return "preMul";
			case Type::postPercent:
				return "postPercent";
			case Type::postDiv:
				return "postDiv";
			case Type::postMul:
				return "postMul";
			case Type::postAssignment:
				return "postAssignment";
			case Type::skillTime:
				return "skillTime";
			case Type::addRate:
				return "addRate";
			case Type::subRate:
				return  "subRate";
			default:
				throw 0;
		}
	}
	Type val;
};

std::string modifier(const ModifierType& type, const Association& association, const Domain& domain, const Name& modified, const Name& modifying, const Optional<std::string>& groupName, const Optional<std::string>& typeName, const Optional<int>& requiredID) {
	std::stringstream str;
	str
	<< "{MetaInfo::Modifier::ModifierType::" << type.to_str()
	<< ", MetaInfo::Modifier::Association::" << association.to_str()
	<< ", MetaInfo::Modifier::Domain::" << domain.to_str()
	<< ", AttributeID::" << modified
	<< ", AttributeID::" << modifying;
	
	switch (type.val) {
		case 2:
			str << ", GroupID::" << Name(*groupName);
			break;
		case 3:
		case 4:
			str << ", TypeID::" << Name(*typeName);
			break;
		case 5:
			str << ", MetaInfo::Modifier::Domain::" << Domain(static_cast<Domain::Type>(*requiredID)).to_str();
			break;
		default:
			break;
	}
	str << "}";
	return str.str();
}

void dumpModifiers(SQLiteDatabase& database) {
	auto result = database.fetch<int, int, int, std::string, std::string, int, Optional<std::string>, Optional<std::string>, Optional<int>>("select a.modifierID, domain, type, b.attributeName as modified, c.attributeName as modifying, association, d.typeName, e.groupName, a.requiredID from dgmModifiers as a left join dgmAttributeTypes as b on a.modifiedAttributeID=b.attributeID left join dgmAttributeTypes as c on a.modifyingAttributeID=c.attributeID left join invTypes as d on a.requiredID=d.typeID left join invGroups as e on a.requiredID=e.groupID order by modifierID");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"\n" << std::endl
	<< "namespace dgmpp {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Modifiers {" << std::endl;
//	<< "		constexpr MetaInfo::Modifier modifiers[] {" << std::endl;

	
	while (auto row = result.next()) {
		auto modifierID = row.get<0>();
		auto domain = Domain(static_cast<Domain::Type>(row.get<1>()));
		auto type = ModifierType(static_cast<ModifierType::Type>(row.get<2>()));
		auto modified = Name(row.get<3>());
		auto modifying = Name(row.get<4>());
		auto association = Association(static_cast<Association::Type>(row.get<5>()));
		auto typeName = row.get<6>();
		auto groupName = row.get<7>();
		auto requiredID = row.get<8>();
		
		std::cout << "\t\t\t"
		<< "constexpr MetaInfo::Modifier modifier" << modifierID << " = " << modifier(type, association, domain, modified, modifying, groupName, typeName, requiredID) << ";" << std::endl;

		/*std::cout << "\t\t\t"
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
		std::cout << "};" << std::endl;*/

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
	<< "namespace dgmpp {" << std::endl
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
	<< "namespace dgmpp {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		constexpr const MetaInfo::Type* skills_array[] = {" << std::endl;
	
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

void dumpWafrareBuffs(SQLiteDatabase& database) {
	auto result = database.fetch<std::string, int>("select substr(attributeName, 12, 1), value from dgmAttributeTypes as a, dgmTypeAttributes as b where a.attributeID=b.attributeID and a.attributeName like \"warfareBuff%ID\" and value > 0 order by value");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"" << std::endl
	<< "#include \"Modifiers.hpp\"\n" << std::endl
	<< "namespace dgmpp {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace WafrareBuffs {" << std::endl
	<< "			using namespace MetaInfo;" << std::endl;

	
	std::list<std::string> names;

	while (auto row = result.next()) {
		auto group = row.get<0>();
		auto buffID = row.get<1>();
		
		std::string id;
		std::string modifyingAttributeID;
		std::vector<std::string> modifiers;
		
		switch (buffID) {
		case 10://shieldHarmonizingChargeBuff1 = 10,
				id = "shieldHarmonizingChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"shieldEmDamageResonance", "shieldKineticDamageResonance", "shieldThermalDamageResonance", "shieldExplosiveDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 11://activeShieldingChargeBuff1 = 11,
				id = "activeShieldingChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"capacitorNeed", "duration"}) {
					for (auto skillID: {"shieldOperation", "shieldEmissionSystems"}) {
						modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, makeOptional<std::string>(skillID), nullopt));
					}
				}
				break;
		case 12://shieldExtensionChargeBuff1 = 12,
				id = "shieldExtensionChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("shieldCapacity"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 13://armorEnergizingChargeBuff1 = 13,
				id = "armorEnergizingChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorEmDamageResonance", "armorKineticDamageResonance", "armorThermalDamageResonance", "armorExplosiveDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 14://rapidRepairChargeBuff1 = 14,
				id = "rapidRepairChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"capacitorNeed", "duration"}) {
					for (auto skillID: {"repairSystems", "remoteArmorRepairSystems"}) {
						modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, makeOptional<std::string>(skillID), nullopt));
					}
				}
				break;
		case 15://armorReinforcementChargeBuff1 = 15,
				id = "armorReinforcementChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("armorHP"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 16://sensorOptimizationChargeBuff1 = 16,
				id = "sensorOptimizationChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("scanResolution"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 17://electronicSuperiorityChargeBuff1 = 17,
				id = "electronicSuperiorityChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"maxRange", "falloffEffectiveness"}) {
					for (auto groupID: {"ECM", "sensorDampener", "weaponDisruptor", "targetPainter"}) {
						modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationGroup), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), makeOptional<std::string>(groupID), nullopt, nullopt));
					}
				}
				
				for (auto attributeID: {"scanGravimetricStrengthBonus", "scanLadarStrengthBonus", "scanMagnetometricStrengthBonus", "scanRadarStrengthBonus"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationGroup), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), makeOptional<std::string>("ECM"), nullopt, nullopt));
				}
				
				for (auto attributeID: {"missileVelocityBonus", "explosionDelayBonus", "aoeVelocityBonus", "falloffBonus", "maxRangeBonus", "aoeCloudSizeBonus", "trackingSpeedBonus"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationGroup), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), makeOptional<std::string>("weaponDisruptor"), nullopt, nullopt));
				}

				for (auto attributeID: {"maxTargetRangeBonus", "scanResolutionBonus"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationGroup), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), makeOptional<std::string>("sensorDampener"), nullopt, nullopt));
				}

				modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationGroup), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("signatureRadiusBonus"), Name(modifyingAttributeID), makeOptional<std::string>("targetPainter"), nullopt, nullopt));

				break;
		case 18://electronicHardeningChargeBuff1 = 18,
				id = "electronicHardeningChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"scanGravimetricStrength", "scanRadarStrength", "scanLadarStrength", "scanMagnetometricStrength"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 19://electronicHardeningChargeBuff2 = 19,
				id = "electronicHardeningChargeBuff2";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"sensorDampenerResistance", "weaponDisruptionResistance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 20://evasiveManeuversChargeBuff1 = 20,
				id = "evasiveManeuversChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("signatureRadius"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 21://interdictionManeuversChargeBuff1 = 21,
				id = "interdictionManeuversChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto groupID: {"stasisWeb", "warpScrambler"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationGroup), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("maxRange"), Name(modifyingAttributeID), makeOptional<std::string>(groupID), nullopt, nullopt));
				}
				break;
		case 22://rapidDeploymentChargeBuff1 = 22,
				id = "rapidDeploymentChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto skillID: {"afterburner", "highSpeedManeuvering"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("speedFactor"), Name(modifyingAttributeID), nullopt, makeOptional<std::string>(skillID), nullopt));
				}
				break;
		case 23://miningLaserFieldEnhancementChargeBuff1 = 23,
				id = "miningLaserFieldEnhancementChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto skillID: {"mining", "iceHarvesting", "gasCloudHarvesting"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("maxRange"), Name(modifyingAttributeID), nullopt, makeOptional<std::string>(skillID), nullopt));
				}
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("surveyScanRange"), Name(modifyingAttributeID), nullopt, makeOptional<std::string>("CPUManagement"), nullopt));
				break;
		case 24://miningLaserOptimizationChargeBuff1 = 24,
				id = "miningLaserOptimizationChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"capacitorNeed", "duration"}) {
					for (auto skillID: {"mining", "iceHarvesting", "gasCloudHarvesting"}) {
						modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, makeOptional<std::string>(skillID), nullopt));
					}
				}
				break;
		case 25://miningEquipmentPreservationChargeBuff1 = 25,
				id = "miningEquipmentPreservationChargeBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("crystalVolatilityChance"), Name(modifyingAttributeID), nullopt, makeOptional<std::string>("mining"), nullopt));
				break;
		case 26://sensorOptimizationChargeBuff2 = 26,
				id = "sensorOptimizationChargeBuff2";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("maxTargetRange"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 39://amarrPhenomenaGeneratorBuff1 = 39,
				id = "amarrPhenomenaGeneratorBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("rechargeRate"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 40://amarrPhenomenaGeneratorBuff2 = 40,
				id = "amarrPhenomenaGeneratorBuff2";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorKineticDamageResonance", "shieldKineticDamageResonance", "kineticDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 41://amarrPhenomenaGeneratorBuff3 = 41,
				id = "amarrPhenomenaGeneratorBuff3";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorEmDamageResonance", "shieldEmDamageResonance", "emDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 42://gallentePhenomenaGeneratorBuff1 = 42,
				id = "gallentePhenomenaGeneratorBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("armorHP"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 43://gallentePhenomenaGeneratorBuff2 = 43,
				id = "gallentePhenomenaGeneratorBuff2";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorExplosiveDamageResonance", "shieldExplosiveDamageResonance", "explosiveDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 44://gallentePhenomenaGeneratorBuff3 = 44,
				id = "gallentePhenomenaGeneratorBuff3";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorThermalDamageResonance", "shieldThermalDamageResonance", "thermalDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 45://minmatarPhenomenaGeneratorBuff1 = 45,
				id = "minmatarPhenomenaGeneratorBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("signatureRadius"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 46://minmatarPhenomenaGeneratorBuff2 = 46,
				id = "minmatarPhenomenaGeneratorBuff2";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorThermalDamageResonance", "shieldThermalDamageResonance", "thermalDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 47://minmatarPhenomenaGeneratorBuff3 = 47,
				id = "minmatarPhenomenaGeneratorBuff3";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorExplosiveDamageResonance", "shieldExplosiveDamageResonance", "explosiveDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 48://caldariPhenomenaGeneratorBuff1 = 48,
				id = "caldariPhenomenaGeneratorBuff1";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("shieldCapacity"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 49://caldariPhenomenaGeneratorBuff2 = 49,
				id = "caldariPhenomenaGeneratorBuff2";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorEmDamageResonance", "shieldEmDamageResonance", "emDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 50://caldariPhenomenaGeneratorBuff3 = 50,
				id = "caldariPhenomenaGeneratorBuff3";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto attributeID: {"armorKineticDamageResonance", "shieldKineticDamageResonance", "kineticDamageResonance"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name(attributeID), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				}
				break;
		case 51://amarrPhenomenaGeneratorBuff4 = 51,
				id = "amarrPhenomenaGeneratorBuff4";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("maxVelocity"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		case 52://gallentePhenomenaGeneratorBuff4 = 52,
				id = "gallentePhenomenaGeneratorBuff4";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("shieldBonus"), Name(modifyingAttributeID), nullopt, makeOptional<std::string>("shieldEmissionSystems"), nullopt));
				break;
		case 53://caldariPhenomenaGeneratorBuff4 = 53,
				id = "caldariPhenomenaGeneratorBuff4";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationRequiredSkill), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("armorDamageAmount"), Name(modifyingAttributeID), nullopt, makeOptional<std::string>("remoteArmorRepairSystems"), nullopt));
				break;
		case 54://minmatarPhenomenaGeneratorBuff4 = 54,
				id = "minmatarPhenomenaGeneratorBuff4";
				modifyingAttributeID = "warfareBuff" + group + "Value";
				for (auto groupID: {"energyWeapon", "hybridWeapon"}) {
					modifiers.push_back(modifier(ModifierType(ModifierType::Type::locationGroup), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("maxRange"), Name(modifyingAttributeID), makeOptional<std::string>(groupID), nullopt, nullopt));
				}
				break;
		case 60://evasiveManeuversChargeBuff2 = 60
				id = "evasiveManeuversChargeBuff2";
				modifyingAttributeID = "warfareBuff" + group + "Multiplier";
				modifiers.push_back(modifier(ModifierType(ModifierType::Type::item), Association(Association::Type::postPercent), Domain(Domain::Type::ship), Name("agility"), Name(modifyingAttributeID), nullopt, nullopt, nullopt));
				break;
		default:
			throw 0;
		}
		
		int i = 0;
		std::list<std::string> mnames;
		for (auto modifier: modifiers) {
			auto modifierID = id + "_modifier" + std::to_string(i++);
			std::cout << "\t\t\t"
			<< "constexpr MetaInfo::Modifier " << modifierID << " = " << modifier << ";" << std::endl;
			mnames.push_back(modifierID);
		}
		
		std::cout << "\t\t\t"
		<< "constexpr auto " << id << " = MakeBuff(WarfareBuffID::" << id
		<< ", AttributeID::" << Name(modifyingAttributeID).to_str()
		<< ", _modifiers(";
		bool isFirst = true;
		for (auto modifier: mnames) {
			if (!isFirst) {
				std::cout << ", " << std::endl;
			}
			std::cout << "&" << modifier;
			isFirst = false;
		}
		std::cout << "));" << std::endl;
		
		names.push_back(id);
	}
	
	std::cout << "\t\t}\n" << std::endl
	//	<< "using namespace Types;" << std::endl
	<< "		constexpr const MetaInfo::WarfareBuff* warfareBuffs[] {" << std::endl;
	
	std::transform(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, ", "), [](const auto& i) {
		return "&WafrareBuffs::" + i;
	});
	
	
	std::cout << "};" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
}

void dumpCommodities(SQLiteDatabase& database) {
	database.fetch<>("CREATE TEMP TABLE temp.tiers as SELECT typeID, 1 as \"tier\" FROM planetSchematicsTypeMap WHERE typeID not in (SELECT typeID FROM planetSchematicsTypeMap WHERE isInput = 0) GROUP BY typeID").next();
	
	for (int i = 2; i <= 5; i++) {
		database.fetch<>("INSERT INTO temp.tiers SELECT typeID, " + std::to_string(i) + " AS \"tier\" FROM planetSchematicsTypeMap WHERE schematicID in (SELECT schematicID FROM planetSchematicsTypeMap WHERE typeID in (SELECT typeID FROM tiers WHERE tier = " + std::to_string(i - 1) + ") AND isInput=1) AND isInput = 0  GROUP BY typeID").next();
	}
	
	auto result = database.fetch<std::string, int, double>("SELECT typeName, tier, volume FROM tiers as a, invTypes as b WHERE a.typeID=b.typeID GROUP BY a.typeID HAVING MAX(tier) order by a.typeID");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"\n" << std::endl
	<< "namespace dgmpp {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Commodities {" << std::endl;

	std::list<std::string> names;
	
	while (auto row = result.next()) {
		auto typeName = Name(row.get<0>());
		auto tier = row.get<1>();
		auto volume = row.get<2>();
		std::cout << "\t\t\t"
		<< "constexpr MetaInfo::Commodity " << typeName.to_str() << " = {TypeID::" << typeName.to_str() << ", MetaInfo::Commodity::Tier::";
		switch (tier) {
			case 1:
				std::cout << "raw";
				break;
			case 2:
				std::cout << "tier1";
				break;
			case 3:
				std::cout << "tier2";
				break;
			case 4:
				std::cout << "tier3";
				break;
			case 5:
				std::cout << "tier4";
				break;
			default:
				std::cout << "unknown";
				break;
		}
		std::cout << ", " << volume << "};" << std::endl;
		
		names.push_back(typeName.to_str());
	}
	
	std::cout << "\t\t}\n" << std::endl
	<< "		constexpr const MetaInfo::Commodity* commodities[] {" << std::endl;
	
	std::transform(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, ", "), [](const auto& i) {
		return "&Commodities::" + i;
	});
	
	std::cout << "\t\t};" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;

}

void dumpFacilities(SQLiteDatabase& database) {
	auto result = database.fetch<std::string, std::string, double>("select typeName, groupName, capacity from invTypes as a, invGroups as b where a.groupID=b.groupID and b.groupName in (\"Extractors\", \"Command Centers\", \"Processors\", \"Storage Facilities\", \"Spaceports\", \"Extractor Control Units\") order by typeID");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"MetaInfo.hpp\"\n" << std::endl
	<< "namespace dgmpp {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Facilities {" << std::endl;
	
	std::list<std::string> names;
	
	while (auto row = result.next()) {
		auto typeName = Name(row.get<0>());
		auto groupName = Name(row.get<1>());
		auto capacity = row.get<2>();
		
		std::cout << "\t\t\t"
		<< "constexpr MetaInfo::Facility " << typeName.to_str() << " = {TypeID::" << typeName.to_str() << ", GroupID::" << groupName.to_str() << ", " << capacity << "};" << std::endl;

		names.push_back(typeName.to_str());
	}
	
	std::cout << "\t\t}\n" << std::endl
	<< "		constexpr const MetaInfo::Facility* facilities[] {" << std::endl;
	
	std::transform(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, ", "), [](const auto& i) {
		return "&Facilities::" + i;
	});
	
	std::cout << "\t\t};" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
	
}

void dumpSchematics(SQLiteDatabase& database) {
	auto result = database.fetch<int, std::string, int>("select schematicID, schematicName, cycleTime from planetSchematics order by schematicID");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "#include \"Commodities.hpp\"\n" << std::endl
	<< "namespace dgmpp {" << std::endl
	<< "	namespace SDE {" << std::endl
	<< "		namespace Schematics {" << std::endl
	<< "			using namespace std::chrono_literals;" << std::endl;
	
	std::list<std::string> names;
	
	while (auto row = result.next()) {
		auto schematicID = row.get<0>();
		auto schematicName = Name(row.get<1>());
		auto cycleTime = row.get<2>();
		
		auto outputRow = database.fetch<std::string, int>("select typeName, quantity from planetSchematicsTypeMap as a, invTypes as b where a.typeID=b.typeID and isInput = 0 and schematicID=" + std::to_string(schematicID)).next();
		auto output = "_C(&Commodities::" + Name(outputRow.get<0>()).to_str() + ", " + std::to_string(outputRow.get<1>()) + ")";
		
		auto result = database.fetch<std::string, int>("select typeName, quantity from planetSchematicsTypeMap as a, invTypes as b where a.typeID=b.typeID and isInput = 1 and schematicID=" + std::to_string(schematicID) + " order by a.typeID");
		std::list<std::string> inputs;
		while (auto row = result.next()) {
			inputs.push_back("_C(&Commodities::" + Name(row.get<0>()).to_str() + ", " + std::to_string(row.get<1>()) + ")");
		}
		
		std::cout << "\t\t\t"
		<< "constexpr auto " << schematicName.to_str() << " = MakeSchematic(SchematicID::" << schematicName.to_str() << ", " << cycleTime << "s, " << output << ", _inputs(";

		bool isFirst = true;
		for (auto& i: inputs) {
			if (!isFirst) {
				std::cout << ", ";
			}
			std::cout << i;
			isFirst = false;
		}
		std::cout << "));" << std::endl;
		
		names.push_back(schematicName.to_str());
	}
	
	std::cout << "\t\t}\n" << std::endl
	<< "		constexpr const MetaInfo::Schematic* schematics[] {" << std::endl;
	
	std::transform(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, ", "), [](const auto& i) {
		return "&Schematics::" + i;
	});
	
	std::cout << "\t\t};" << std::endl
	<< "	}" << std::endl
	<< "}" << std::endl;
	
}

void dumpVersion(SQLiteDatabase& database) {
	auto result = database.fetch<int, std::string>("select build, version from version");
	
	std::cout
	<< "#pragma once" << std::endl
	<< "namespace dgmpp {" << std::endl;
	
	std::list<std::string> names;
	
	if (auto row = result.next()) {
		auto build = row.get<0>();
		auto version = row.get<1>();
		std::cout << "\t" << "const auto sdeVersion = SDEVersion({" << build << ", \"" << version << "\"});" << std::endl;
	}
	
	std::cout << "}" << std::endl;
	
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
		else if (action == "--warfareBuffIDs") {
			dumpIDs(database, "WarfareBuffID", "select value, typeName || \"Buff\" || substr(attributeName, 12, 1) from invTypes as a, dgmTypeAttributes as b, dgmAttributeTypes as c where a.typeID=b.typeID and b.attributeID == c.attributeID and c.attributeName like \"warfareBuff%ID\" and value > 0 order by value");
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
		else if (action == "--warfareBuffs") {
			dumpWafrareBuffs(database);
			return 0;
		}
		else if (action == "--skills") {
			dumpSkills(database);
			return 0;
		}
		else if (action == "--convertModifiers") {
			convertModifiers(database);
			return 0;
		}
		else if (action == "--compile") {
			compile(database);
			return 0;
		}
		else if (action == "--commodities") {
			dumpCommodities(database);
			return 0;
		}
		else if (action == "--facilities") {
			dumpFacilities(database);
			return 0;
		}
		else if (action == "--schematicIDs") {
			dumpIDs(database, "SchematicID", "select schematicID, schematicName from planetSchematics order by schematicID");
			return 0;
		}
		else if (action == "--schematics") {
			dumpSchematics(database);
			return 0;
		}
		else if (action == "--version") {
			dumpVersion(database);
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
	--warfareBuffIDs\n\
	--attributes\n\
	--types\n\
	--modifiers\n\
	--effects\n\
	--warfareBuffs\n\
	--skills\n\
	--convertModifiers\n\
	--compile\n\
	--commodities\n\
	--facilities\n\
	--schematicIDs\n\
	--schematics\n\
	" << std::endl;
	
	return 1;
}
