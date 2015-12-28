//
//  main.m
//  modifiersdump
//
//  Created by Артем Шиманский on 15.12.15.
//
//

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
	for (auto modifier: split(modifierInfo, "-")) {
		std::map<std::string, std::string> m;
		for (auto row: split(modifier, "\n")) {
			if (row.length() == 0)
				continue;
			auto parts = split(row, ":");
			auto key = parts[0];
			auto value = parts[1];
			m[key] = value;
		}
		modifiers.push_back(m);
	}
	return modifiers;
}

std::set<std::string> domains;
std::set<std::string> funcs;

std::string association(const std::string& operatorID) {
	int i = std::atoi(operatorID.c_str());
	const char* v[] = {"PreAssignment", "PreMul", "PreDiv", "ModAdd", "ModSub", "PostMul", "PostDiv", "PostPercent", "PostAssignment"};
	return v[i + 1];
}

std::string attr(const std::string& attributeID) {
	std::stringstream sql;
	sql << "select attributeName from dgmAttributeTypes where attributeID = " << attributeID;
	std::string attributeName;
	exec(sql.str(), [&] (sqlite3_stmt *stmt) -> bool {
		attributeName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		return false;
	});
	return attributeName;
}

std::string group(const std::string& groupID) {
	std::stringstream sql;
	sql << "select groupName from invGroups where groupID = " << groupID;
	std::string groupName;
	exec(sql.str(), [&] (sqlite3_stmt *stmt) -> bool {
		groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		return false;
	});
	return groupName;
}

std::string type(const std::string& typeID) {
	std::stringstream sql;
	sql << "select typeName from invTypes where typeID = " << typeID;
	std::string typeName;
	exec(sql.str(), [&] (sqlite3_stmt *stmt) -> bool {
		typeName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		return false;
	});
	return typeName;
}

std::string domain(const std::string& domain) {
	if (domain == "charID")
		return "Char";
	else if (domain == "shipID")
		return "Ship";
	else if (domain == "targetID")
		return "Target";
	else if (domain == "null")
		return "Self";
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
	else
		assert(0);
}

std::vector<std::string> processModifier(const std::map<std::string, std::string>& modifier) {
	auto d = domain(modifier.at("domain"));
	auto pref = preFunc(modifier.at("func"));
	auto postf = postFunc(modifier.at("func"));
	auto assoc = association(modifier.at("operator"));
	auto modifiedAttribute = attr(modifier.at("modifiedAttributeID"));
	auto modifyingAttribute = attr(modifier.at("modifyingAttributeID"));

	domains.insert(d);
	
	std::stringstream pre;
	std::stringstream post;
	
	if (pref == "AIM") {
		pre << "DefEnv(\"" << d << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << pref << "(\"" << modifyingAttribute << "\")";
		post << "DefEnv(\"" << d << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << postf << "(\"" << modifyingAttribute << "\")";
	}
	else if (pref == "ALGM") {
		pre << "DefEnv(\"" << d << "\").locationGroup(\"" << group(modifier.at("groupID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << pref << "(\"" << modifyingAttribute << "\")";
		post << "DefEnv(\"" << d << "\").locationGroup(\"" << group(modifier.at("groupID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << postf << "(\"" << modifyingAttribute << "\")";
	}
	else if (pref == "ALRSM" || pref == "AORSM") {
		pre << "DefEnv(\"" << d << "\").locationSkill(\"" << type(modifier.at("skillTypeID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << pref << "(\"" << modifyingAttribute << "\")";
		post << "DefEnv(\"" << d << "\").locationSkill(\"" << type(modifier.at("skillTypeID")) << "\").attr(\"" << modifiedAttribute << "\").assoc(\"" << assoc << "\")." << postf << "(\"" << modifyingAttribute << "\")";
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

std::string process(const int effectID, std::string effectName, const std::string& modifierInfo) {
	std::vector<std::vector<std::string>> modifiers;
	for (auto m: parse(modifierInfo)) {
		auto v = processModifier(m);
		modifiers.push_back(v);
	}
	auto v = comb(modifiers);
	std::stringstream s;
	s << "update(\"" << effectName << "\",\n\t" << v[0] << ",\n\t" << v[1] << ");\n\n";
	return s.str();
}


int main(int argc, const char * argv[]) {
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
}
