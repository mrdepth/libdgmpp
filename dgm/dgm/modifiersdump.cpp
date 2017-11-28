//
//  modifiersdump.cpp
//  dgm
//
//  Created by Artem Shimanski on 28.11.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

#include "modifiersdump.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <sqlite3.h>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <fstream>

void replace(std::string& src, const std::string& what, const std::string& to) {
	size_t pos = src.find(what);
	while (pos != std::string::npos) {
		src.replace(pos, what.size(), to);
		pos = src.find(what);
	}
}

std::vector<std::string> split(const std::string& src, const std::string& delim) {
	std::vector<std::string> v;
	size_t start = 0;
	size_t pos = src.find(delim, start);
	while (pos != std::string::npos) {
		if (pos - start > 0)
		v.push_back(src.substr(start, pos - start));
		start = pos + delim.length();
		pos = src.find(delim, start);
	}
	v.push_back(src.substr(start));
	return v;
}

std::vector<std::map<std::string, std::string>> parse(std::string modifierInfo) {
	replace(modifierInfo, "\\n", "\n");
	replace(modifierInfo, "\\r", "");
	replace(modifierInfo, " ", "");
	
	std::vector<std::map<std::string, std::string>> modifiers;
	std::map<std::string, std::string> m;
	
	for (auto row: split(modifierInfo, "\n")) {
		if (row.length() == 0 || row[0] == '#')
		continue;
		if (row[0] == '-') {
			if (m.size() > 0)
			modifiers.push_back(m);
			m.clear();
			row.erase(row.begin());
		}
		
		auto parts = split(row, ":");
		assert(parts.size() == 2);
		auto key = parts[0];
		auto value = parts[1];
		m[key] = value;
		
	}
	
	if (m.size() > 0)
	modifiers.push_back(m);
	
	/*std::vector<std::map<std::string, std::string>> modifiers;
	 for (auto modifier: split(modifierInfo, "-")) {
	 std::map<std::string, std::string> m;
	 for (auto row: split(modifier, "\n")) {
	 if (row.length() == 0 || row[0] == '#')
	 continue;
	 auto parts = split(row, ":");
	 auto key = parts[0];
	 auto value = parts[1];
	 m[key] = value;
	 }
	 if (m.size() > 0)
	 modifiers.push_back(m);
	 }*/
	return modifiers;
}

std::set<std::string> domains;
std::set<std::string> funcs;

std::string association(const std::string& operatorID) {
	int i = std::atoi(operatorID.c_str());
	const char* v[] = {"PreAssignment", "PreMul", "PreDiv", "ModAdd", "ModSub", "PostMul", "PostDiv", "PostPercent", "PostAssignment"};
	return v[i + 1];
}

std::string attr(SQLiteDatabase& database, const std::string& attributeID) {
	return database.fetch<std::string>("select attributeName from dgmAttributeTypes where attributeID = " + attributeID).next().get<0>();
}

std::string group(SQLiteDatabase& database, const std::string& groupID) {
	return database.fetch<std::string>("select groupName from invGroups where groupID = " + groupID).next().get<0>();
}

std::string type(SQLiteDatabase& database, const std::string& typeID) {
	return database.fetch<std::string>("select typeName from invTypes where typeID = " + typeID).next().get<0>();
}

std::string domain(const std::string& domain) {
	if (domain == "charID")
	return "Char";
	else if (domain == "shipID")
	return "Ship";
	else if (domain == "targetID" || domain == "target")
	return "Target";
	else if (domain == "null" || domain == "itemID")
	return "Self";
	else if (domain == "otherID")
	return "Other";
	else if (domain == "gangID")
	return "Gang";
	else if (domain == "structureID")
	return "Structure";
	else
	assert(0);
}

std::string preFunc(const std::string& func) {
	if (func == "ItemModifier")
	return "AIM";
	else if (func == "LocationGroupModifier")
	return "ALGM";
	else if (func == "LocationRequiredSkillModifier")
	return "ALRSM";
	else if (func == "OwnerRequiredSkillModifier")
	return "AORSM";
	else if (func == "GangItemModifier")
	return "AGIM";
	else if (func == "GangRequiredSkillModifier")
	return "AGRSM";
	else if (func == "EffectStopper")
	return "$SKIP";
	else
	assert(0);
}

std::string postFunc(const std::string& func) {
	if (func == "ItemModifier")
	return "RIM";
	else if (func == "LocationGroupModifier")
	return "RLGM";
	else if (func == "LocationRequiredSkillModifier")
	return "RLRSM";
	else if (func == "OwnerRequiredSkillModifier")
	return "RORSM";
	else if (func == "GangItemModifier")
	return "RGIM";
	else if (func == "GangRequiredSkillModifier")
	return "RGRSM";
	else if (func == "EffectStopper")
	return "$SKIP";
	else
	assert(0);
}

std::vector<std::string> processModifier(SQLiteDatabase& database, const std::map<std::string, std::string>& modifier) {
	auto d = modifier.find("domain") == modifier.end() ? domain("gangID") : domain(modifier.at("domain"));
	auto pref = preFunc(modifier.at("func"));
	if (pref == "$SKIP")
	return {};
	
	auto postf = postFunc(modifier.at("func"));
	auto assoc = association(modifier.at("operator"));
	auto modifiedAttribute = attr(database, modifier.at("modifiedAttributeID"));
	auto modifyingAttribute = attr(database, modifier.at("modifyingAttributeID"));
	
	
	domains.insert(d);
	
	std::stringstream pre;
	std::stringstream post;
	
	if (pref == "AIM" || pref == "AGIM") {
		pre << "DefEnv(\"" << d << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << pref << "(\"" << modifyingAttribute << "\")";
		post << "DefEnv(\"" << d << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << postf << "(\"" << modifyingAttribute << "\")";
	}
	else if (pref == "ALGM") {
		pre << "DefEnv(\"" << d << "\").locationGroup(\"" << group(database, modifier.at("groupID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << pref << "(\"" << modifyingAttribute << "\")";
		post << "DefEnv(\"" << d << "\").locationGroup(\"" << group(database, modifier.at("groupID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << postf << "(\"" << modifyingAttribute << "\")";
	}
	else if (pref == "ALRSM" || pref == "AORSM" || pref == "AGRSM" || pref == "AGORSM") {
		pre << "DefEnv(\"" << d << "\").locationSkill(\"" << type(database, modifier.at("skillTypeID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << pref << "(\"" << modifyingAttribute << "\")";
		post << "DefEnv(\"" << d << "\").locationSkill(\"" << type(database, modifier.at("skillTypeID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << postf << "(\"" << modifyingAttribute << "\")";
	}
	else
	assert(0);
	return {pre.str(), post.str()};
}

std::vector<std::string> comb(const std::vector<std::vector<std::string>>& v) {
	if (v.size() == 1) {
		return v[0];
	}
	else {
		std::vector<std::vector<std::string>> p1;
		std::vector<std::vector<std::string>> p2;
		auto mid = v.begin() + v.size() / 2;
		std::copy(v.begin(), mid, std::inserter(p1, p1.begin()));
		std::copy(mid, v.end(), std::inserter(p2, p2.begin()));
		
		std::vector<std::string> v1 = comb(p1);
		std::vector<std::string> v2 = comb(p2);
		std::stringstream pre;
		std::stringstream post;
		
		pre << "COMB(" << v1[0] << "," << v2[0] << ")";
		post << "COMB(" << v1[1] << "," << v2[1] << ")";
		return {pre.str(), post.str()};
	}
}

std::string process(SQLiteDatabase& database, const int effectID, std::string effectName, const std::string& modifierInfo) {
	std::vector<std::vector<std::string>> modifiers;
	for (auto m: parse(modifierInfo)) {
		auto v = processModifier(database, m);
		if (v.size() == 2)
		modifiers.push_back(v);
	}
	auto v = comb(modifiers);
	std::stringstream s;
	s << "{\nupdate(\"" << effectName << "\",\n\t" << v[0] << ",\n\t" << v[1] << ");\n}" << std::endl;
	return s.str();
}

void convertModifiers(SQLiteDatabase& database) {
	auto result = database.fetch<int, std::string, std::string>("select effectID, effectName, modifierInfo from dgmEffects where length(modifierInfo) > 0");
	while (auto row = result.next()) {
		std::cout << process(database, row.get<0>(), row.get<1>(), row.get<2>());
	}
}


/*int main(int argc, const char * argv[]) {
	const char* databasePath = argv[1];
	int res = sqlite3_open(databasePath, &db);
	
	
	std::ofstream os;
	os.open(argv[2]);
	
	exec("select effectID, effectName, modifierInfo from dgmEffects where length(modifierInfo) > 0;", [&](sqlite3_stmt* stmt) -> bool {
		os << process(sqlite3_column_int(stmt, 0), reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)), reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		return true;
	});
	os.close();
	return 0;
}*/
