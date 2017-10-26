//
//  main.cpp
//  idsdump
//
//  Created by Artem Shimanski on 26.10.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

#include <iostream>
#include <sqlite3.h>
#include <functional>
#include <regex>
#include <algorithm>
#include <set>

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

std::string normalize(std::string s) {
	s = std::regex_replace(s, std::regex("(\\\\u.{4})"), "");
	s = std::regex_replace(s, std::regex("[^a-zA-Z0-9]"), "");
	if (std::regex_match(s, std::regex("^[A-Z][^A-Z]+.*"))) {
		s[0] = std::tolower(s[0]);
	}
	if (std::regex_match(s, std::regex("^\\d.*"))) {
		s = "_" + s;
	}
	return s;

}

int main(int argc, const char * argv[]) {
	const char* databasePath = argv[1];
	const char* name = argv[2];
	const char* sql = argv[3];
	

	sqlite3_open(databasePath, &db);
	
	std::cout << "#pragma once\n\n"
	"namespace dgmpp {\n"
	"\tenum class " << name << ": int {\n"
	"\t\tnone = 0";
	
	std::set<std::string> set;
	
	exec(sql, [&](sqlite3_stmt* stmt) -> bool {
		int id = sqlite3_column_int(stmt, 0);
		std::string name = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 1));
		
		name = normalize(name);
		if (set.find(name) == set.end()) {
			std::cout << ",\n\t\t" << name << " = " << id;
			set.insert(name);
		}
		return true;
	});

	
	std::cout << "\n\t};\n" << "}";
	
	/*exec("select effectID, effectName from dgmEffects order by effectID", [&](sqlite3_stmt* stmt) -> bool {
		int effectID = sqlite3_column_int(stmt, 0);
		std::string effectName = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 1));
		
		effectName = normalize(effectName);
		std::cout << effectName << " = " << effectID << "," << std::endl;
		return true;
	});
	
	exec("select attributeID, attributeName from dgmAttributeTypes order by attributeID", [&](sqlite3_stmt* stmt) -> bool {
		int attributeID = sqlite3_column_int(stmt, 0);
		std::string attributeName = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 1));
		
		attributeName = normalize(attributeName);
		std::cout << attributeName << " = " << attributeID << "," << std::endl;
		return true;
	});

	
	exec("SELECT groupID, groupName, COUNT(*) c FROM invGroups WHERE categoryID NOT IN (1,2) GROUP BY groupName ORDER BY groupID", [&](sqlite3_stmt* stmt) -> bool {
		int groupID = sqlite3_column_int(stmt, 0);
		std::string groupName = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 1));
		
		groupName = normalize(groupName);
		std::cout << groupName << " = " << groupID << "," << std::endl;
		return true;
	});


	exec("select typeID, typeName from invTypes where published = 1 OR groupID = 1 order by typeID", [&](sqlite3_stmt* stmt) -> bool {
		int typeID = sqlite3_column_int(stmt, 0);
		std::string typeName = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 1));
		
		typeName = normalize(typeName);
		std::cout << typeName << " = " << typeID << "," << std::endl;
		return true;
	});*/
	return 0;
}
