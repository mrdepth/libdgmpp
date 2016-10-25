//
//  main.cpp
//  dbpatch
//
//  Created by Artem Shimanski on 26.12.14.
//
//

#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <sqlite3.h>

sqlite3 *db = NULL;
int userExpressoinID = 20000;

std::ostream& operator << (std::ostream& os, class Expression& exp);


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
	else {
		std::cout << "error:" << sqlite3_errmsg(db) << std::endl;
		throw std::bad_exception();
	}
}

class Operator {
public:
	std::string name_;
protected:
	Operator(const std::string& name) : name_(name) {};
};

template <typename T> class Operator1: public Operator {
public:
	Operator1(const std::string& name, const T& arg1) : Operator(name), arg1_(arg1) {};
	T arg1_;
};

template <typename T1, typename T2> class Operator2 : public Operator {
public:
	Operator2(const std::string& name, const T1& arg1, const T2& arg2) : Operator(name), arg1_(arg1), arg2_(arg2) {};
	T1 arg1_;
	T2 arg2_;
};

class DefAttr : public Operator1<std::string> {
public:
	DefAttr(const std::string& env) : Operator1("DEFATTRIBUTE", env) {};
};

class DefInt : public Operator1<int> {
public:
	DefInt(int value) : Operator1("DEFINT", value) {};
};

template <typename T> class Modifier : public Operator2<T, DefAttr> {
public:
	Modifier(const std::string& name, const T& arg1, const DefAttr& arg2) : Operator2<T, DefAttr>(name, arg1, arg2) {};
};

class DefAssoc : public Operator1<std::string> {
public:
	DefAssoc(const std::string& env) : Operator1("DEFASSOCIATION", env) {};
};

template <typename T> class EFF : public Operator2<DefAssoc, T> {
public:
	EFF(const DefAssoc& arg1, const T& arg2) : Operator2<DefAssoc, T>("EFF", arg1, arg2) {};
	Modifier<EFF<T> > AGGM(const std::string& attr) {
		return Modifier<EFF<T> >("AGGM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > AGIM(const std::string& attr) {
		return Modifier<EFF<T> >("AGIM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > AGORSM(const std::string& attr) {
		return Modifier<EFF<T> >("AGORSM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > AGRSM(const std::string& attr) {
		return Modifier<EFF<T> >("AGRSM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > AIM(const std::string& attr) {
		return Modifier<EFF<T> >("AIM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > ALGM(const std::string& attr) {
		return Modifier<EFF<T> >("ALGM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > ALM(const std::string& attr) {
		return Modifier<EFF<T> >("ALM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > ALRSM(const std::string& attr) {
		return Modifier<EFF<T> >("ALRSM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > AORSM(const std::string& attr) {
		return Modifier<EFF<T> >("AORSM", *this, DefAttr(attr));
	}
	
	Modifier<EFF<T> > RGGM(const std::string& attr) {
		return Modifier<EFF<T> >("RGGM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RGIM(const std::string& attr) {
		return Modifier<EFF<T> >("RGIM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RGORSM(const std::string& attr) {
		return Modifier<EFF<T> >("RGORSM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RGRSM(const std::string& attr) {
		return Modifier<EFF<T> >("RGRSM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RIM(const std::string& attr) {
		return Modifier<EFF<T> >("RIM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RLGM(const std::string& attr) {
		return Modifier<EFF<T> >("RLGM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RLM(const std::string& attr) {
		return Modifier<EFF<T> >("RLM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RLRSM(const std::string& attr) {
		return Modifier<EFF<T> >("RLRSM", *this, DefAttr(attr));
	}
	Modifier<EFF<T> > RORSM(const std::string& attr) {
		return Modifier<EFF<T> >("RORSM", *this, DefAttr(attr));
	}
};

template <typename T> class ATT : public Operator2<T, DefAttr>{
public:
	ATT(const T& arg1, const DefAttr& arg2) : Operator2<T, DefAttr>("ATT", arg1, arg2) {};
	EFF<ATT<T> > assoc(const std::string& assoc) {
		return EFF<ATT<T> >(DefAssoc(assoc), *this);
	}
};

class DefType : public Operator1<std::string> {
public:
	DefType(const std::string& type) : Operator1("DEFTYPEID", type) {};
};

class DefGroup : public Operator1<std::string> {
public:
	DefGroup(const std::string& type) : Operator1("DEFGROUP", type) {};
};

template <typename T> class LS : public Operator2<T, DefType>{
public:
	LS(const T& arg1, const DefType& arg2) : Operator2<T, DefType>("LS", arg1, arg2) {};
	ATT<LS<T> > attr(const std::string& attr) {
		return ATT<LS<T> >(*this, DefAttr(attr));
	}
};

template <typename T> class LG : public Operator2<T, DefGroup>{
public:
	LG(const T& arg1, const DefGroup& arg2) : Operator2<T, DefGroup>("LG", arg1, arg2) {};
	ATT<LG<T> > attr(const std::string& attr) {
		return ATT<LG<T> >(*this, DefAttr(attr));
	}
};


class DefEnv : public Operator1<std::string> {
public:
	DefEnv(const std::string& env) : Operator1("DEFENVIDX", env) {};
	ATT<DefEnv> attr(const std::string& attr) {
		return ATT<DefEnv>(*this, DefAttr(attr));
	}
	LS<DefEnv> locationSkill(const std::string& skill) {
		return LS<DefEnv>(*this, DefType(skill));
	}
	LG<DefEnv> locationGroup(const std::string& group) {
		return LG<DefEnv>(*this, DefGroup(group));
	}
};

template <typename T1, typename T2> class COMBINE : public Operator2<T1, T2>{
public:
	COMBINE(const T1& arg1, const T2& arg2) : Operator2<T1, T2>("COMBINE", arg1, arg2) {};
};

template <typename T> std::ostream& operator << (std::ostream& os, const Operator1<T>& o) {
	os << "{Operator: " << o.name_ << ",\n" <<
	"\texpressionValue:" << o.arg1_ << "}" << std::endl;
	return os;
}

template <typename T1, typename T2> std::ostream& operator << (std::ostream& os, const Operator2<T1, T2>& o) {
	os << "{Operator: " << o.name_ << ",\n" <<
	"\targ1:" << o.arg1_ << ",\n" <<
	"\targ2:" << o.arg2_ << "}" << std::endl;
	return os;
}

template <typename T1, typename T2> COMBINE<T1, T2> COMB(const T1& arg1, const T2& arg2) {
	return COMBINE<T1, T2>(arg1, arg2);
}

class Expression {
public:
	Expression() : arg1(NULL), arg2(NULL), expressionID_(0), operatorID(0), expressionTypeID_(0), expressionGroupID_(0), expressionAttributeID_(0) {};
	std::string expressionValue;
	
	Expression* arg1;
	Expression* arg2;
	int operatorID;
	std::string operatorName;
	
	int expressionID() {
		if (!expressionID_)
			expressionID_ = findExpression();
		return expressionID_;
	}
	
	int expressionTypeID() {
		if (!expressionTypeID_) {
			std::stringstream os;
			os << "select typeID from invTypes where typeName = \"" << expressionValue << "\"";
			expressionTypeID_ = -1;
			exec(os.str(), [&](sqlite3_stmt* stmt) -> bool {
				expressionTypeID_ = sqlite3_column_int(stmt, 0);
				return false;
			});
		}
		return expressionTypeID_ > 0 ? expressionTypeID_ : 0;
	}
	
	int expressionGroupID() {
		if (!expressionGroupID_) {
			std::stringstream os;
			os << "select groupID from invGroups where groupName = \"" << expressionValue << "\"";
			expressionGroupID_ = -1;
			exec(os.str(), [&](sqlite3_stmt* stmt) -> bool {
				expressionGroupID_ = sqlite3_column_int(stmt, 0);
				return false;
			});
		}
		return expressionGroupID_ > 0 ? expressionGroupID_ : 0;
	}
	
	int expressionAttributeID(){
		if (!expressionAttributeID_) {
			std::stringstream os;
			os << "select attributeID from dgmAttributeTypes  where attributeName = \"" << expressionValue << "\"";
			expressionAttributeID_ = -1;
			exec(os.str(), [&](sqlite3_stmt* stmt) -> bool {
				expressionAttributeID_ = sqlite3_column_int(stmt, 0);
				return false;
			});
		}
		return expressionAttributeID_ > 0 ? expressionAttributeID_ : 0;
	}
	
	int findExpression() {
		std::stringstream os;
		if (arg1 && arg2) {
			os << "select expressionID from dgmExpressions where operandID = " << operatorID << " and arg1 = " << arg1->expressionID() << " and arg2 = " << arg2->expressionID();
		}
		else if (operatorName == "DEFATTRIBUTE") {
			os << "select expressionID from dgmExpressions where operandID = " << operatorID << " and expressionAttributeID = " << expressionAttributeID();
		}
		else if (operatorName == "DEFTYPEID") {
			os << "select expressionID from dgmExpressions where operandID = " << operatorID << " and expressionTypeID = " << expressionTypeID();
		}
		else if (operatorName == "DEFGROUP") {
			os << "select expressionID from dgmExpressions where operandID = " << operatorID << " and expressionGroupID = " << expressionGroupID();
		}
		else {
			os << "select expressionID from dgmExpressions where operandID = " << operatorID << " and expressionValue = \"" << expressionValue << "\"";
		}
		int expressionID = 0;
		exec(os.str().c_str(), [&](sqlite3_stmt* stmt) -> bool {
			expressionID = sqlite3_column_int(stmt, 0);
			return false;
		});
		
		if (!expressionID) {
			expressionID = userExpressoinID++;
			if (arg1 && arg2) {
				std::stringstream os;
				os << "insert into dgmExpressions (expressionID, operandID, arg1, arg2, description, expressionName) values (" <<
				expressionID << ", " <<
				operatorID << ", " <<
				arg1->expressionID() << ", " <<
				arg2->expressionID() << ", " <<
				"\"dgmpp\"" << ", " <<
				"\"" << *this << "\"" << ")";
				exec(os.str(), [](sqlite3_stmt* stmt) -> bool {
					return false;
				});
			}
			else if (operatorName == "DEFATTRIBUTE") {
				std::stringstream os;
				os << "insert into dgmExpressions (expressionID, operandID, expressionAttributeID, description, expressionName) values (" <<
				expressionID << ", " <<
				operatorID << ", " <<
				expressionAttributeID() << ", " <<
				"\"dgmpp\"" << ", " <<
				"\"" << *this << "\"" << ")";
				exec(os.str(), [](sqlite3_stmt* stmt) -> bool {
					return false;
				});
			}
			else if (operatorName == "DEFTYPEID") {
				std::stringstream os;
				os << "insert into dgmExpressions (expressionID, operandID, expressionTypeID, description, expressionName) values (" <<
				expressionID << ", " <<
				operatorID << ", " <<
				expressionTypeID() << ", " <<
				"\"dgmpp\"" << ", " <<
				"\"" << *this << "\"" << ")";
				exec(os.str(), [](sqlite3_stmt* stmt) -> bool {
					return false;
				});
			}
			else if (operatorName == "DEFGROUP") {
				std::stringstream os;
				os << "insert into dgmExpressions (expressionID, operandID, expressionGroupID, description, expressionName) values (" <<
				expressionID << ", " <<
				operatorID << ", " <<
				expressionGroupID() << ", " <<
				"\"dgmpp\"" << ", " <<
				"\"" << *this << "\"" << ")";
				exec(os.str(), [](sqlite3_stmt* stmt) -> bool {
					return false;
				});
			}
			else {
				std::stringstream os;
				os << "insert into dgmExpressions (expressionID, operandID, expressionValue, description, expressionName) values (" <<
				expressionID << ", " <<
				operatorID << ", " <<
				'"' << expressionValue << "\", " <<
				"\"dgmpp\"" << ", " <<
				"\"" << *this << "\"" << ")";
				exec(os.str(), [](sqlite3_stmt* stmt) -> bool {
					return false;
				});
			}
		}
		
		return expressionID;
	}
	
private:
	int expressionID_;
	int expressionTypeID_;
	int expressionGroupID_;
	int expressionAttributeID_;
};

int operatorID(const std::string& operatorName) {
	std::stringstream os;
	os << "select operandID from dgmOperands where operandKey = \"" << operatorName << "\"";
	int operandID = 0;
	exec(os.str().c_str(), [&](sqlite3_stmt* stmt) -> bool {
		operandID = sqlite3_column_int(stmt, 0);
		return false;
	});
	return operandID;
}

template <typename T> std::string to_str(const T& t) {
	return std::to_string(t);
}

template <> std::string to_str<std::string>(const std::string& t) {
	return t;
}

template <typename T> Expression& operator << (Expression& expression, const Operator1<T>& o) {
	expression.expressionValue = to_str(o.arg1_);
	expression.operatorID = operatorID(o.name_);
	expression.operatorName = o.name_;
	expression.expressionID();
	return expression;
}

template <typename T1, typename T2> Expression& operator << (Expression& expression, const Operator2<T1, T2>& o) {
	expression.operatorID = operatorID(o.name_);
	expression.operatorName = o.name_;
	expression.arg1 = new Expression();
	(*expression.arg1) << o.arg1_;
	expression.arg2 = new Expression();
	(*expression.arg2) << o.arg2_;
	expression.expressionID();
	return expression;
}

std::ostream& operator << (std::ostream& os, Expression& exp) {
	std::stringstream sql;
	sql << "select format from dgmOperands where operandID = " << exp.operatorID;
	std::string format;
	
	exec(sql.str(), [&](sqlite3_stmt* stmt)->bool {
		format = (const char*) sqlite3_column_text(stmt, 0);
		return false;
	});
	auto pos = format.find("%(arg1)s");
	if (pos != std::string::npos) {
		std::stringstream s;
		s << *exp.arg1;
		format.replace(pos, 8, s.str());
	}
	
	pos = format.find("%(arg2)s");
	if (pos != std::string::npos) {
		std::stringstream s;
		s << *exp.arg2;
		format.replace(pos, 8, s.str());
	}
	
	pos = format.find("%(value)s");
	if (pos != std::string::npos) {
		std::stringstream s;
		s << exp.expressionValue;
		format.replace(pos, 9, s.str());
	}
	
	return os << format;
}

template <typename T1, typename T2> void update(const std::string& effectName, T1 pre, T2 post) {
	Expression preExpression;
	Expression postExpression;
	preExpression << pre;
	postExpression << post;
	
	std::stringstream os;
	os << "update dgmEffects set preExpression = " << preExpression.expressionID() << " where effectID in (select effectID from dgmEffects where effectName = \"" << effectName << "\")";
	exec(os.str(), nullptr);
	
	os.str("");
	os << "update dgmEffects set postExpression = " << postExpression.expressionID() << " where effectID in (select effectID from dgmEffects where effectName = \"" << effectName << "\")";
	exec(os.str(), nullptr);
}

void addEffect(int32_t effectID, const std::string& effectName, int32_t effectCategory, bool isOffensive, bool isAssistance) {
	std::stringstream os;
	os << "INSERT INTO \"dgmEffects\" (effectID,effectName,effectCategory,preExpression,postExpression,description,isOffensive,isAssistance)\
	VALUES (\"" << effectID << "\",\"" << effectName << "\"," << effectCategory << ",131, 131, \"dgmpp\"," << isOffensive << "," << isAssistance << ");";
	exec(os.str(), nullptr);
}

void addAttribute(int32_t attributeID, const std::string& attributeName, int32_t attributeCategory, int32_t unitID, bool stackable, bool highIsGood, double defaultValue = 0.0) {
	std::stringstream os;
	os << "INSERT INTO \"dgmAttributeTypes\" (attributeID,attributeName,attributeCategory,published,unitID,defaultValue,displayName,description,stackable,highIsGood,categoryID,iconID)\
	VALUES (" << attributeID << ", \"" << attributeName << "\"," << attributeCategory << ",0, " << unitID << ", " << defaultValue << ", NULL, \"dgmpp\", " << stackable << "," << highIsGood << ", NULL, NULL);";
	exec(os.str(), nullptr);
}

void addItemEffect(const std::string& typeName, int32_t effectID) {
	std::stringstream os;
	os << "INSERT INTO dgmTypeEffects SELECT typeID, " << effectID << " as effectID, 1 as isDefault FROM invTypes WHERE typeName = \"" << typeName << "\";";
	exec(os.str(), nullptr);
}

void addEffectGroup(int32_t groupID, int32_t effectID) {
	std::stringstream os;
	os << "INSERT INTO dgmTypeEffects SELECT typeID, " << effectID << " as effectID, 1 as isDefault FROM invTypes WHERE groupID = " << groupID << ";";
	exec(os.str(), nullptr);
}

void addEffectCategory(int32_t categoryID, int32_t effectID) {
	std::stringstream os;
	os << "INSERT INTO dgmTypeEffects SELECT typeID, " << effectID << " as effectID, 1 as isDefault FROM invTypes WHERE groupID IN (SELECT groupID FROM invGroups WHERE categoryID = " << categoryID << ");";
	exec(os.str(), nullptr);
}

void addItemAttribute(const std::string& typeName, int32_t attributeID, float value) {
	std::stringstream os;
	os << "INSERT INTO dgmTypeAttributes SELECT typeID, " << attributeID << " as attributeID," << value << " as value FROM invTypes WHERE typeName = \"" << typeName << "\";";
	exec(os.str(), nullptr);
}

void addAttributeGroup(int32_t groupID, int32_t attributeID, float value) {
	std::stringstream os;
	os << "INSERT INTO dgmTypeAttributes SELECT typeID, " << attributeID << " as attributeID," << value << " as value FROM invTypes WHERE groupID = " << groupID << ";";
	exec(os.str(), nullptr);
}

int32_t getTypeID(const std::string& typeName) {
	std::stringstream os;
	os << "SELECT typeID FROM invTypes WHERE typeName = \"" << typeName << "\";";
	int32_t typeID = 0;
	exec(os.str(), [&](sqlite3_stmt* stmt) -> bool {
		typeID = sqlite3_column_int(stmt, 0);
		return false;
	});
	return typeID;
}

int32_t getEffectID(const std::string& effectName) {
	std::stringstream os;
	os << "SELECT effectID FROM dgmEffects WHERE effectName = \"" << effectName << "\";";
	int32_t effectID = 0;
	exec(os.str(), [&](sqlite3_stmt* stmt) -> bool {
		effectID = sqlite3_column_int(stmt, 0);
		return false;
	});
	return effectID;
}

int32_t getAttributeID(const std::string& attributeName) {
	std::stringstream os;
	os << "SELECT attributeID FROM dgmAttributeTypes WHERE attributeName = \"" << attributeName << "\";";
	int32_t attributeID = 0;
	exec(os.str(), [&](sqlite3_stmt* stmt) -> bool {
		attributeID = sqlite3_column_int(stmt, 0);
		return false;
	});
	return attributeID;
}

int patch(const char* databasePath) {
	int res = sqlite3_open(databasePath, &db);
	if (!db)
		return res;
	
	sqlite3_exec(db, "delete from dgmExpressions where expressionID >= 20000", NULL, NULL, NULL);
	sqlite3_exec(db, "delete from dgmEffects where effectID >= 10000", NULL, NULL, NULL);
	sqlite3_exec(db, "delete from dgmTypeEffects where effectID >= 10000", NULL, NULL, NULL);
	sqlite3_exec(db, "delete from dgmAttributeTypes where attributeID >= 10000", NULL, NULL, NULL);
	sqlite3_exec(db, "delete from dgmTypeAttributes where attributeID >= 10000", NULL, NULL, NULL);
	
	addEffect(10000, "characterDamageMissiles", 0, 0, 0);
	addItemEffect("CharacterStatic", getEffectID("characterDamageMissiles"));
	
	sqlite3_exec(db, "DELETE FROM dgmTypeEffects WHERE effectID=3461;", NULL, NULL, NULL);
	addEffectGroup(899, 3461);

	addEffect(10002, "tacticalMode", 0, 0, 0);
	addAttribute(10000, "tacticalModes", 4, 122, 1, 1);
	
	addItemEffect("Confessor Defense Mode", getEffectID("tacticalMode"));
	addItemEffect("Confessor Sharpshooter Mode", getEffectID("tacticalMode"));
	addItemEffect("Confessor Propulsion Mode", getEffectID("tacticalMode"));
	addItemAttribute("Confessor Defense Mode", getAttributeID("canFitShipType1"), getTypeID("Confessor"));
	addItemAttribute("Confessor Sharpshooter Mode", getAttributeID("canFitShipType1"), getTypeID("Confessor"));
	addItemAttribute("Confessor Propulsion Mode", getAttributeID("canFitShipType1"), getTypeID("Confessor"));
	addItemAttribute("Confessor", getAttributeID("tacticalModes"), 1);
	
	addItemEffect("Svipul Defense Mode", getEffectID("tacticalMode"));
	addItemEffect("Svipul Sharpshooter Mode", getEffectID("tacticalMode"));
	addItemEffect("Svipul Propulsion Mode", getEffectID("tacticalMode"));
	addItemAttribute("Svipul Defense Mode", getAttributeID("canFitShipType1"), getTypeID("Svipul"));
	addItemAttribute("Svipul Sharpshooter Mode", getAttributeID("canFitShipType1"), getTypeID("Svipul"));
	addItemAttribute("Svipul Propulsion Mode", getAttributeID("canFitShipType1"), getTypeID("Svipul"));
	addItemAttribute("Svipul", getAttributeID("tacticalModes"), 1);

	addItemEffect("Jackdaw Defense Mode", getEffectID("tacticalMode"));
	addItemEffect("Jackdaw Sharpshooter Mode", getEffectID("tacticalMode"));
	addItemEffect("Jackdaw Propulsion Mode", getEffectID("tacticalMode"));
	addItemAttribute("Jackdaw Defense Mode", getAttributeID("canFitShipType1"), getTypeID("Jackdaw"));
	addItemAttribute("Jackdaw Sharpshooter Mode", getAttributeID("canFitShipType1"), getTypeID("Jackdaw"));
	addItemAttribute("Jackdaw Propulsion Mode", getAttributeID("canFitShipType1"), getTypeID("Jackdaw"));
	addItemAttribute("Jackdaw", getAttributeID("tacticalModes"), 1);

	addItemEffect("Hecate Defense Mode", getEffectID("tacticalMode"));
	addItemEffect("Hecate Sharpshooter Mode", getEffectID("tacticalMode"));
	addItemEffect("Hecate Propulsion Mode", getEffectID("tacticalMode"));
	addItemAttribute("Hecate Defense Mode", getAttributeID("canFitShipType1"), getTypeID("Hecate"));
	addItemAttribute("Hecate Sharpshooter Mode", getAttributeID("canFitShipType1"), getTypeID("Hecate"));
	addItemAttribute("Hecate Propulsion Mode", getAttributeID("canFitShipType1"), getTypeID("Hecate"));
	addItemAttribute("Hecate", getAttributeID("tacticalModes"), 1);

	//Ancillary Armor Repairer fix
	addEffect(10001, "naniteRepairPasteArmorDamageBonus", 0, 0, 0);
	addEffect(10003, "fueledArmorRepairBonus", 0, 0, 0);
	addAttribute(10002, "chargedArmorDamageMultiplierPostDiv", 5, 0, 1, 1);
	exec("INSERT INTO dgmTypeAttributes SELECT typeID, 10002 as attributeID, value FROM dgmTypeAttributes WHERE attributeID=1886", nullptr);
	exec("INSERT INTO dgmTypeEffects SELECT typeID, 10003, 1 FROM dgmTypeEffects WHERE effectID=5275", nullptr);
	addItemEffect("Nanite Repair Paste", getEffectID("naniteRepairPasteArmorDamageBonus"));
	addItemAttribute("Nanite Repair Paste", getAttributeID("chargedArmorDamageMultiplierPostDiv"), 1);
	
	
	update("online",
		   COMB(
				DefEnv("Ship").attr("cpuLoad").assoc("ModAdd").AIM("cpu"),
				DefEnv("Ship").attr("powerLoad").assoc("ModAdd").AIM("power")),
		   COMB(
				DefEnv("Ship").attr("cpuLoad").assoc("ModAdd").RIM("cpu"),
				DefEnv("Ship").attr("powerLoad").assoc("ModAdd").RIM("power"))
		   );
	
	update("characterDamageMissiles",
		   COMB(
				COMB(
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("emDamage").assoc("PostMul").AORSM("missileDamageMultiplier"),
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("explosiveDamage").assoc("PostMul").AORSM("missileDamageMultiplier")),
				COMB(
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("kineticDamage").assoc("PostMul").AORSM("missileDamageMultiplier"),
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("thermalDamage").assoc("PostMul").AORSM("missileDamageMultiplier"))),
		   COMB(
				COMB(
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("emDamage").assoc("PostMul").RORSM("missileDamageMultiplier"),
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("explosiveDamage").assoc("PostMul").RORSM("missileDamageMultiplier")),
				COMB(
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("kineticDamage").assoc("PostMul").RORSM("missileDamageMultiplier"),
					 DefEnv("Char").locationSkill("Missile Launcher Operation").attr("thermalDamage").assoc("PostMul").RORSM("missileDamageMultiplier"))));
	
	update("slotModifier",
		   COMB(
				COMB(
					 DefEnv("Ship").attr("hiSlots").assoc("ModAdd").AIM("hiSlotModifier"),
					 DefEnv("Ship").attr("medSlots").assoc("ModAdd").AIM("medSlotModifier")),
				DefEnv("Ship").attr("lowSlots").assoc("ModAdd").AIM("lowSlotModifier")),
		   COMB(
				COMB(
					 DefEnv("Ship").attr("hiSlots").assoc("ModAdd").RIM("hiSlotModifier"),
					 DefEnv("Ship").attr("medSlots").assoc("ModAdd").RIM("medSlotModifier")),
				DefEnv("Ship").attr("lowSlots").assoc("ModAdd").RIM("lowSlotModifier")));
	
	update("hardPointModifierEffect",
		   COMB(
				DefEnv("Ship").attr("launcherSlotsLeft").assoc("ModAdd").AIM("launcherHardPointModifier"),
				DefEnv("Ship").attr("turretSlotsLeft").assoc("ModAdd").AIM("turretHardPointModifier")),
		   COMB(
				DefEnv("Ship").attr("launcherSlotsLeft").assoc("ModAdd").RIM("launcherHardPointModifier"),
				DefEnv("Ship").attr("turretSlotsLeft").assoc("ModAdd").RIM("turretHardPointModifier")));

	update("adaptiveArmorHardener",
		   COMB(
				COMB(
					 DefEnv("Ship").attr("armorEmDamageResonance").assoc("PostMul").AIM("armorEmDamageResonance"),
					 DefEnv("Ship").attr("armorExplosiveDamageResonance").assoc("PostMul").AIM("armorExplosiveDamageResonance")),
				COMB(
					 DefEnv("Ship").attr("armorKineticDamageResonance").assoc("PostMul").AIM("armorKineticDamageResonance"),
					 DefEnv("Ship").attr("armorThermalDamageResonance").assoc("PostMul").AIM("armorThermalDamageResonance"))),
		   
		   
		   COMB(
				COMB(
					 DefEnv("Ship").attr("armorEmDamageResonance").assoc("PostMul").RIM("armorEmDamageResonance"),
					 DefEnv("Ship").attr("armorExplosiveDamageResonance").assoc("PostMul").RIM("armorExplosiveDamageResonance")),
				COMB(
					 DefEnv("Ship").attr("armorKineticDamageResonance").assoc("PostMul").RIM("armorKineticDamageResonance"),
					 DefEnv("Ship").attr("armorThermalDamageResonance").assoc("PostMul").RIM("armorThermalDamageResonance"))));

	update("fueledArmorRepairBonus",
		   COMB(
				DefEnv("Self").attr("chargedArmorDamageMultiplier").assoc("PostDiv").AIM("chargedArmorDamageMultiplierPostDiv"),
				DefEnv("Self").attr("armorDamageAmount").assoc("PostMul").AIM("chargedArmorDamageMultiplier")
				),
		   COMB(
				DefEnv("Self").attr("chargedArmorDamageMultiplier").assoc("PostDiv").RIM("chargedArmorDamageMultiplierPostDiv"),
				DefEnv("Self").attr("armorDamageAmount").assoc("PostMul").RIM("chargedArmorDamageMultiplier")
		   ));
	update("naniteRepairPasteArmorDamageBonus",
		   DefEnv("Other").attr("chargedArmorDamageMultiplierPostDiv").assoc("PostAssignment").AIM("chargedArmorDamageMultiplierPostDiv"),
		   DefEnv("Other").attr("chargedArmorDamageMultiplierPostDiv").assoc("PostAssignment").RIM("chargedArmorDamageMultiplierPostDiv"));
	

	//Repairers
	//update("armorRepair", DefInt(1), DefInt(1));
	update("armorRepair",
		   DefEnv("Ship").attr("armorDamage").assoc("SubRate").AIM("armorDamageAmount"),
		   DefEnv("Ship").attr("armorDamage").assoc("SubRate").RIM("armorDamageAmount"));
	update("targetArmorRepair",
		   DefEnv("Target").attr("armorDamage").assoc("SubRate").AIM("armorDamageAmount"),
		   DefEnv("Target").attr("armorDamage").assoc("SubRate").RIM("armorDamageAmount"));
	update("remoteArmorRepairFalloff",
		   DefEnv("Target").attr("armorDamage").assoc("SubRate").AIM("armorDamageAmount"),
		   DefEnv("Target").attr("armorDamage").assoc("SubRate").RIM("armorDamageAmount"));
	update("fueledArmorRepair",
		   DefEnv("Ship").attr("armorDamage").assoc("SubRate").AIM("armorDamageAmount"),
		   DefEnv("Ship").attr("armorDamage").assoc("SubRate").RIM("armorDamageAmount"));
	
	update("shieldBoosting",
		   DefEnv("Ship").attr("shieldCharge").assoc("AddRate").AIM("shieldBonus"),
		   DefEnv("Ship").attr("shieldCharge").assoc("AddRate").RIM("shieldBonus"));
	update("shieldTransfer",
		   DefEnv("Target").attr("shieldCharge").assoc("AddRate").AIM("shieldBonus"),
		   DefEnv("Target").attr("shieldCharge").assoc("AddRate").RIM("shieldBonus"));
	update("remoteShieldTransferFalloff",
		   DefEnv("Target").attr("shieldCharge").assoc("AddRate").AIM("shieldBonus"),
		   DefEnv("Target").attr("shieldCharge").assoc("AddRate").RIM("shieldBonus"));
	update("fueledShieldBoosting",
		   DefEnv("Ship").attr("shieldCharge").assoc("AddRate").AIM("shieldBonus"),
		   DefEnv("Ship").attr("shieldCharge").assoc("AddRate").RIM("shieldBonus"));
	

	update("structureRepair",
		   DefEnv("Ship").attr("damage").assoc("SubRate").AIM("structureDamageAmount"),
		   DefEnv("Ship").attr("damage").assoc("SubRate").RIM("structureDamageAmount"));
	update("remoteHullRepair",
		   DefEnv("Target").attr("damage").assoc("SubRate").AIM("structureDamageAmount"),
		   DefEnv("Target").attr("damage").assoc("SubRate").RIM("structureDamageAmount"));
	update("remoteHullRepairFalloff",
		   DefEnv("Target").attr("damage").assoc("SubRate").AIM("structureDamageAmount"),
		   DefEnv("Target").attr("damage").assoc("SubRate").RIM("structureDamageAmount"));


	//Energy Transfers
	update("energyTransfer",
		   DefEnv("Target").attr("charge").assoc("AddRate").AIM("powerTransferAmount"),
		   DefEnv("Target").attr("charge").assoc("AddRate").RIM("powerTransferAmount"));
	update("energyDestabilizationNew",
		   DefEnv("Target").attr("charge").assoc("SubRate").AIM("powerTransferAmount"),
		   DefEnv("Target").attr("charge").assoc("SubRate").RIM("powerTransferAmount"));
	update("energyNosferatuFalloff",
		   DefEnv("Target").attr("charge").assoc("SubRate").AIM("powerTransferAmount"),
		   DefEnv("Target").attr("charge").assoc("SubRate").RIM("powerTransferAmount"));
	
	//Confessor
	update("modeVelocityPostDiv",
		   DefEnv("Ship").attr("maxVelocity").assoc("PostDiv").AIM("modeVelocityPostDiv"),
		   DefEnv("Ship").attr("maxVelocity").assoc("PostDiv").RIM("modeVelocityPostDiv"));
	
	update("modeAgilityPostDiv",
		   DefEnv("Ship").attr("agility").assoc("PostDiv").AIM("modeAgilityPostDiv"),
		   DefEnv("Ship").attr("agility").assoc("PostDiv").RIM("modeAgilityPostDiv"));
	
	update("modeArmorResonancePostDiv",
		   COMB(
				COMB(
					 DefEnv("Ship").attr("armorEmDamageResonance").assoc("PostDiv").AIM("modeEmResistancePostDiv"),
					 DefEnv("Ship").attr("armorExplosiveDamageResonance").assoc("PostDiv").AIM("modeExplosiveResistancePostDiv")),
				COMB(
					 DefEnv("Ship").attr("armorKineticDamageResonance").assoc("PostDiv").AIM("modeKineticResistancePostDiv"),
					 DefEnv("Ship").attr("armorThermalDamageResonance").assoc("PostDiv").AIM("modeThermicResistancePostDiv"))),
		   
		   
		   COMB(
				COMB(
					 DefEnv("Ship").attr("armorEmDamageResonance").assoc("PostDiv").RIM("modeEmResistancePostDiv"),
					 DefEnv("Ship").attr("armorExplosiveDamageResonance").assoc("PostDiv").RIM("modeExplosiveResistancePostDiv")),
				COMB(
					 DefEnv("Ship").attr("armorKineticDamageResonance").assoc("PostDiv").RIM("modeKineticResistancePostDiv"),
					 DefEnv("Ship").attr("armorThermalDamageResonance").assoc("PostDiv").RIM("modeThermicResistancePostDiv"))));
	
	
	update("modeSigRadiusPostDiv",
		   DefEnv("Ship").attr("signatureRadius").assoc("PostDiv").AIM("modeSignatureRadiusPostDiv"),
		   DefEnv("Ship").attr("signatureRadius").assoc("PostDiv").RIM("modeSignatureRadiusPostDiv"));
	
	update("shipModeScanResPostDiv",
		   DefEnv("Ship").attr("scanResolution").assoc("PostDiv").AIM("modeScanResPostDiv"),
		   DefEnv("Ship").attr("scanResolution").assoc("PostDiv").RIM("modeScanResPostDiv"));
	
	update("shipModeScanStrengthPostDiv",
		   DefEnv("Ship").attr("scanRadarStrength").assoc("PostDiv").AIM("modeRadarStrengthPostDiv"),
		   DefEnv("Ship").attr("scanRadarStrength").assoc("PostDiv").RIM("modeRadarStrengthPostDiv"));
	
	update("shipModeSETOptimalRangePostDiv",
		   DefEnv("Ship").locationSkill("Small Energy Turret").attr("maxRange").assoc("PostDiv").ALRSM("modeMaxRangePostDiv"),
		   DefEnv("Ship").locationSkill("Small Energy Turret").attr("maxRange").assoc("PostDiv").RLRSM("modeMaxRangePostDiv"));
	
	update("shipModeMaxTargetRangePostDiv",
		   DefEnv("Ship").attr("maxTargetRange").assoc("PostDiv").AIM("modeMaxTargetRangePostDiv"),
		   DefEnv("Ship").attr("maxTargetRange").assoc("PostDiv").RIM("modeMaxTargetRangePostDiv"));

	//Svipul
	update("modeShieldResonancePostDiv",
		   COMB(
				COMB(
					 DefEnv("Ship").attr("shieldEmDamageResonance").assoc("PostDiv").AIM("modeEmResistancePostDiv"),
					 DefEnv("Ship").attr("shieldExplosiveDamageResonance").assoc("PostDiv").AIM("modeExplosiveResistancePostDiv")),
				COMB(
					 DefEnv("Ship").attr("shieldKineticDamageResonance").assoc("PostDiv").AIM("modeKineticResistancePostDiv"),
					 DefEnv("Ship").attr("shieldThermalDamageResonance").assoc("PostDiv").AIM("modeThermicResistancePostDiv"))),
		   
		   
		   COMB(
				COMB(
					 DefEnv("Ship").attr("shieldEmDamageResonance").assoc("PostDiv").RIM("modeEmResistancePostDiv"),
					 DefEnv("Ship").attr("shieldExplosiveDamageResonance").assoc("PostDiv").RIM("modeExplosiveResistancePostDiv")),
				COMB(
					 DefEnv("Ship").attr("shieldKineticDamageResonance").assoc("PostDiv").RIM("modeKineticResistancePostDiv"),
					 DefEnv("Ship").attr("shieldThermalDamageResonance").assoc("PostDiv").RIM("modeThermicResistancePostDiv"))));
	
	update("shipModeSPTTrackingPostDiv",
		   DefEnv("Ship").locationSkill("Small Projectile Turret").attr("trackingSpeed").assoc("PostDiv").ALRSM("modeTrackingPostDiv"),
		   DefEnv("Ship").locationSkill("Small Projectile Turret").attr("trackingSpeed").assoc("PostDiv").RLRSM("modeTrackingPostDiv"));
	update("modeMWDSigRadiusPostDiv",
		   DefEnv("Ship").locationSkill("High Speed Maneuvering").attr("signatureRadiusBonus").assoc("PostDiv").ALRSM("modeMWDSigPenaltyPostDiv"),
		   DefEnv("Ship").locationSkill("High Speed Maneuvering").attr("signatureRadiusBonus").assoc("PostDiv").RLRSM("modeMWDSigPenaltyPostDiv"));
	
	//Jackdaw
	update("shipModeMissileVelocityPostDiv",
		   DefEnv("Char").locationSkill("Missile Launcher Operation").attr("maxVelocity").assoc("PostDiv").AORSM("modeMaxRangePostDiv"),
		   DefEnv("Char").locationSkill("Missile Launcher Operation").attr("maxVelocity").assoc("PostDiv").RORSM("modeMaxRangePostDiv"));
	
    //Hecate
    update("modeHullResonancePostDiv",
           COMB(
                COMB(
                     DefEnv("Ship").attr("emDamageResonance").assoc("PostDiv").AIM("modeEmResistancePostDiv"),
                     DefEnv("Ship").attr("explosiveDamageResonance").assoc("PostDiv").AIM("modeExplosiveResistancePostDiv")),
                COMB(
                     DefEnv("Ship").attr("kineticDamageResonance").assoc("PostDiv").AIM("modeKineticResistancePostDiv"),
                     DefEnv("Ship").attr("thermalDamageResonance").assoc("PostDiv").AIM("modeThermicResistancePostDiv"))),
           
           
           COMB(
                COMB(
                     DefEnv("Ship").attr("emDamageResonance").assoc("PostDiv").RIM("modeEmResistancePostDiv"),
                     DefEnv("Ship").attr("explosiveDamageResonance").assoc("PostDiv").RIM("modeExplosiveResistancePostDiv")),
                COMB(
                     DefEnv("Ship").attr("kineticDamageResonance").assoc("PostDiv").RIM("modeKineticResistancePostDiv"),
                     DefEnv("Ship").attr("thermalDamageResonance").assoc("PostDiv").RIM("modeThermicResistancePostDiv"))));

    update("modeArmorRepDurationPostDiv",
           DefEnv("Ship").locationSkill("Repair Systems").attr("duration").assoc("PostDiv").ALRSM("modeArmorRepDurationPostDiv"),
           DefEnv("Ship").locationSkill("Repair Systems").attr("duration").assoc("PostDiv").RLRSM("modeArmorRepDurationPostDiv"));

    update("modeMWDBoostPostDiv",
           DefEnv("Ship").locationSkill("High Speed Maneuvering").attr("speedFactor").assoc("PostDiv").ALRSM("modeMWDVelocityPostDiv"),
           DefEnv("Ship").locationSkill("High Speed Maneuvering").attr("speedFactor").assoc("PostDiv").RLRSM("modeMWDVelocityPostDiv"));

    update("modeMWDCapPostDiv",
           DefEnv("Ship").locationSkill("High Speed Maneuvering").attr("capacitorNeed").assoc("PostDiv").ALRSM("modeMWDCapPostDiv"),
           DefEnv("Ship").locationSkill("High Speed Maneuvering").attr("capacitorNeed").assoc("PostDiv").RLRSM("modeMWDCapPostDiv"));

    update("shipModeSHTOptimalRangePostDiv",
           DefEnv("Ship").locationSkill("Small Hybrid Turret").attr("maxRange").assoc("PostDiv").ALRSM("modeMaxRangePostDiv"),
           DefEnv("Ship").locationSkill("Small Hybrid Turret").attr("maxRange").assoc("PostDiv").RLRSM("modeMaxRangePostDiv"));
	
	
	addAttribute(576, "speedBoostFactorCalc", 9, 0, 1, 1, 0.01);
	addAttribute(578, "speedBoostFactorCalc2", 9, 0, 1, 1, 1.0);
	addEffect(710, "speedBoostFactorCalculator", 0, 0, 0);
	addEffect(712, "speedBoostFactorCalculator2", 0, 0, 0);
	addEffect(1171, "massFactor", 0, 0, 0);
	addEffectGroup(46, 710);
	addEffectGroup(46, 712);
	
	update("speedBoostFactorCalculator",
		   COMB(
				DefEnv("Self").attr("speedBoostFactorCalc").assoc("PostMul").AIM("speedFactor"),
				DefEnv("Self").attr("speedBoostFactorCalc").assoc("PostMul").AIM("speedBoostFactor")),
		   COMB(
				DefEnv("Self").attr("speedBoostFactorCalc").assoc("PostMul").RIM("speedFactor"),
				DefEnv("Self").attr("speedBoostFactorCalc").assoc("PostMul").RIM("speedBoostFactor")));
	
	update("speedBoostFactorCalculator2",
		   DefEnv("Self").attr("speedBoostFactorCalc2").assoc("ModAdd").AIM("speedBoostFactorCalc"),
		   DefEnv("Self").attr("speedBoostFactorCalc2").assoc("ModAdd").RIM("speedBoostFactorCalc"));

	
	update("moduleBonusAfterburner",
		   COMB(
				DefEnv("Ship").attr("maxVelocity").assoc("PostMul").AIM("speedBoostFactorCalc2"),
				DefEnv("Ship").attr("mass").assoc("ModAdd").AIM("massAddition")),
		   COMB(
				DefEnv("Ship").attr("maxVelocity").assoc("PostMul").RIM("speedBoostFactorCalc2"),
				DefEnv("Ship").attr("mass").assoc("ModAdd").RIM("massAddition")));

	

	update("moduleBonusMicrowarpdrive",
		   COMB(
				DefEnv("Ship").attr("maxVelocity").assoc("PostMul").AIM("speedBoostFactorCalc2"),
				COMB(
					 DefEnv("Ship").attr("mass").assoc("ModAdd").AIM("massAddition"),
					 DefEnv("Ship").attr("signatureRadius").assoc("PostPercent").AIM("signatureRadiusBonus")
					 )),
		   COMB(
				DefEnv("Ship").attr("maxVelocity").assoc("PostMul").RIM("speedBoostFactorCalc2"),
				COMB(
					 DefEnv("Ship").attr("mass").assoc("ModAdd").RIM("massAddition"),
					 DefEnv("Ship").attr("signatureRadius").assoc("PostPercent").RIM("signatureRadiusBonus")
					 )));
	
	update("massFactor",
		   DefEnv("Self").locationGroup("Propulsion Module").attr("speedBoostFactorCalc").assoc("PostDiv").ALGM("mass"),
		   DefEnv("Self").locationGroup("Propulsion Module").attr("speedBoostFactorCalc").assoc("PostDiv").RLGM("mass"));

	addEffectCategory(6, 1171);

	#include <dbpatch.h>
	
	//Suppress
/*	update("shieldBoostingForEntities", DefInt(1), DefInt(1));
	update("armorRepairForEntities", DefInt(1), DefInt(1));
	update("entityCapacitorDrain", DefInt(1), DefInt(1));
	update("entityShieldBoostingSmall", DefInt(1), DefInt(1));
	update("entityShieldBoostingMedium", DefInt(1), DefInt(1));
	update("entityShieldBoostingLarge", DefInt(1), DefInt(1));
	update("entityArmorRepairingSmall", DefInt(1), DefInt(1));
	update("entityArmorRepairingMedium", DefInt(1), DefInt(1));
	update("entityArmorRepairingLarge", DefInt(1), DefInt(1));*/
	update("energyDestabilizationForStructure", DefInt(1), DefInt(1));
	return 0;
}

int main(int argc, const char * argv[]) {
	if (argc == 2)
		return patch(argv[1]);
	else
		return 1;
}
