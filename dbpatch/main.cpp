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
	//protected:
	T arg1_;
};

template <typename T1, typename T2> class Operator2 : public Operator {
public:
	Operator2(const std::string& name, const T1& arg1, const T2& arg2) : Operator(name), arg1_(arg1), arg2_(arg2) {};
	//protected:
	T1 arg1_;
	T2 arg2_;
};

class DefAttr : public Operator1<std::string> {
public:
	DefAttr(const std::string& env) : Operator1("DEFATTRIBUTE", env) {};
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

template <typename T> class LS : public Operator2<T, DefType>{
public:
	LS(const T& arg1, const DefType& arg2) : Operator2<T, DefType>("LS", arg1, arg2) {};
	ATT<LS<T> > attr(const std::string& attr) {
		return ATT<LS<T> >(*this, DefAttr(attr));
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
				"\"eufe\"" << ", " <<
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
				"\"eufe\"" << ", " <<
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
				"\"eufe\"" << ", " <<
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

template <typename T> Expression& operator << (Expression& expression, const Operator1<T>& o) {
	expression.expressionValue = o.arg1_;
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

int patch(const char* databasePath) {
	int res = sqlite3_open(databasePath, &db);
	if (!db)
		return res;
	
	sqlite3_exec(db, "delete from dgmExpressions where expressionID >= 20000", NULL, NULL, NULL);
	
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
	
	return 0;
}

int main(int argc, const char * argv[]) {
	if (argc == 2)
		return patch(argv[1]);
	else
		return 1;
}
