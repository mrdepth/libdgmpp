#pragma once
#include <stdexcept>
#include "types.h"
#include <sqlite3.h>
#include <cstdlib>

//#include "ThirdParty/sqlite3.h"


/*namespace eufe {

	class Compiler
	{
	public:

		//typedef boost::error_info<struct SqliteExceptionInfoTag, std::string> SqliteExceptionInfo;
		//struct SqliteException : virtual boost::exception {};
		//struct SqliteExpcetion: std::logic_error {};
		typedef std::runtime_error SqliteException;
		
		Compiler(const std::string& databasePath, const std::string& outputPath);
		~Compiler(void);
		void compile();
	private:

		typedef std::map<std::string, std::string> Row;
		typedef std::map<std::string, Row> RowsMap;
		
		typedef std::basic_string<Byte> MemoryBlock;
		typedef std::map<std::string, MemoryBlock> CompiledExpressionsMap;

		std::string databasePath_;
		std::string outputPath_;

		RowsMap expressions_;
		RowsMap operands_;
		RowsMap effects_;
		CompiledExpressionsMap compiledExpressionsMap_;

		
		
		MemoryBlock compileExpression(Row& expression);
		MemoryBlock compileEffect(Row& effect);
		
		size_t addExpression(Row& expression, CompiledExpressionsMap& expressionsMap);
		
		static Row callback(int argc, char** argv, char** azColName);
		static int callbackExpression(void* context, int argc, char** argv, char** azColName);
		static int callbackOperand(void* context, int argc, char** argv, char** azColName);
		static int callbackEffect(void* context, int argc, char** argv, char** azColName);

		std::string stringRepresentation(const MemoryBlock& memoryBlock);
	};

};
*/

namespace Compiler {
	void exec(const std::string sql, std::function<bool (sqlite3_stmt* stmt)> callback);
	int32_t getAttributeID(const std::string& attributeName);
	int32_t getGroupID(const std::string& groupName);
	int32_t getTypeID(const std::string& typeName);

	class AttributeID;
	class Attribute;
	class Association;
	class Domain;
	
	class GroupID {
	public:
		GroupID() : groupID_(0) {};
		GroupID(int32_t groupID) : groupID_(groupID) {};
	private:
		int32_t groupID_;
	};
	
	class TypeID {
	public:
		TypeID() : typeID_(0) {};
		TypeID(const std::string& domain) : typeID_(0), domain_(domain) {}
		TypeID(int32_t typeID) : typeID_(typeID) {};
	private:
		int32_t typeID_;
		std::string domain_;
	};
	
	class Domain {
	public:
		Domain() {};
		Domain(const std::string& domain) : domain_(domain) {};
		Domain(const Domain& other, const GroupID& groupID) : locationGroup_(groupID), domain_(other.domain_), requiredSkill_(other.requiredSkill_) {}
		Domain(const Domain& other, const TypeID& typeID) : requiredSkill_(typeID), domain_(other.domain_), locationGroup_(other.locationGroup_) {}
		
		Attribute getAttribute(const AttributeID& attributeID);
		TypeID getTypeID();
		Domain getLocationGroup(const GroupID& groupID);
		Domain getRequiredSkill(const TypeID& typeID);
		
	private:
		std::string domain_;
		GroupID locationGroup_;
		TypeID requiredSkill_;
	};
	
	class AttributeID {
	public:
		AttributeID() : attributeID_(0) {};
		AttributeID(int32_t attributeID) : attributeID_(attributeID) {};
	private:
		int32_t attributeID_;
	};

	class Attribute {
	public:
		Attribute() {};
		Attribute(const Domain& domain, const AttributeID& attributeID) : domain_(domain), attributeID_(attributeID) {};
		
		bool set(float value);
		bool inc(float value);
		bool dec(float value);
		bool dec(const AttributeID& attributeID);
		bool inc(const AttributeID& attributeID);
		bool set(const AttributeID& attributeID);
		Association getAssociation(const std::string& name);
	private:
		AttributeID attributeID_;
		Domain domain_;
	};
	
	typedef std::string AssociationName;

	class Association {
	public:
		Association() {};
		Association(const Attribute& attribute, const std::string& name) : attribute_(attribute), name_(name) {};
		
		bool addItemModifier(const AttributeID attributeID);
		bool addLocationGroupModifier(const AttributeID attributeID);
		bool addLocationModifier(const AttributeID attributeID);
		bool addLocationRequiredSkillModifier(const AttributeID attributeID);
		bool addOwnerRequiredSkillModifier(const AttributeID attributeID);
	private:
		Attribute attribute_;
		std::string name_;
	};
	
	class Value {
	public:
		enum ValueType {
			VALUE_TYPE_UNKNOWN,
			VALUE_TYPE_INT,
			VALUE_TYPE_FLOAT,
			VALUE_TYPE_BOOL,
			VALUE_TYPE_STRING
		};
		Value() : valueType_(VALUE_TYPE_UNKNOWN) {};
		Value(int v) : i_(v), valueType_(VALUE_TYPE_INT) {};
		Value(bool v) : b_(v), valueType_(VALUE_TYPE_BOOL) {};
		Value(float v) : f_(v), valueType_(VALUE_TYPE_FLOAT) {};
		Value(double v) : f_(v), valueType_(VALUE_TYPE_FLOAT) {};
		Value(const std::string& v) : s_(v), valueType_(VALUE_TYPE_STRING) {};
		
		operator float();
		explicit operator bool ();
		explicit operator int();
		operator const std::string&();
		
	private:
		union {
			int i_;
			float f_;
			bool b_;
		};
		std::string s_;
		ValueType valueType_;
	};
	
	class Argument  {
	public:
		enum ArgumentType {
			ARGUMENT_TYPE_ASSOCIATION_NAME,
			ARGUMENT_TYPE_ATTRIBUTE_ID,
			ARGUMENT_TYPE_ATTRIBUTE,
			ARGUMENT_TYPE_VALUE,
			ARGUMENT_TYPE_ASSOCIATION,
			ARGUMENT_TYPE_DOMAIN,
			ARGUMENT_TYPE_GROUP_ID,
			ARGUMENT_TYPE_TYPE_ID
		};
		
		template<typename V> Argument(V v) : Argument(Value(v)) {};
		
		Argument(const AssociationName& v): associationName_(v), argumentType_(ARGUMENT_TYPE_ASSOCIATION_NAME) {};
		Argument(const AttributeID& v): attributeID_(v), argumentType_(ARGUMENT_TYPE_ATTRIBUTE_ID) {};
		Argument(const Attribute& v): attribute_(v), argumentType_(ARGUMENT_TYPE_ATTRIBUTE) {};
		Argument(const Value& v): value_(v), argumentType_(ARGUMENT_TYPE_VALUE) {};
		Argument(const Association& v): association_(v), argumentType_(ARGUMENT_TYPE_ASSOCIATION) {};
		Argument(const Domain& v): domain_(v), argumentType_(ARGUMENT_TYPE_DOMAIN) {};
		Argument(const GroupID& v): groupID_(v), argumentType_(ARGUMENT_TYPE_GROUP_ID) {};
		Argument(const TypeID& v): typeID_(v), argumentType_(ARGUMENT_TYPE_TYPE_ID) {};
		
		explicit operator AssociationName& () {
			assert(argumentType_ == ARGUMENT_TYPE_ASSOCIATION_NAME);
			return associationName_;
		}
		explicit operator AttributeID& () {
			assert(argumentType_ == ARGUMENT_TYPE_ATTRIBUTE_ID);
			return attributeID_;
		}
		explicit operator Attribute& () {
			assert(argumentType_ == ARGUMENT_TYPE_ATTRIBUTE);
			return attribute_;
		}
		explicit operator Value& () {
			assert(argumentType_ == ARGUMENT_TYPE_VALUE);
			return value_;
		}
		explicit operator Association& () {
			assert(argumentType_ == ARGUMENT_TYPE_ASSOCIATION);
			return association_;
		}
		explicit operator Domain& () {
			assert(argumentType_ == ARGUMENT_TYPE_DOMAIN);
			return domain_;
		}
		explicit operator GroupID& () {
			assert(argumentType_ == ARGUMENT_TYPE_GROUP_ID);
			return groupID_;
		}
		explicit operator TypeID& () {
			assert(argumentType_ == ARGUMENT_TYPE_TYPE_ID);
			return typeID_;
		}
		
	private:
		AssociationName associationName_;
		AttributeID attributeID_;
		Attribute attribute_;
		Value value_;
		Association association_;
		Domain domain_;
		GroupID groupID_;
		TypeID typeID_;
		ArgumentType argumentType_;
	};
	
	//typedef std::function<Argument(const class Expression& expression)> Operand;
	/*
	 argumentCategory:
	 0: none
	 1: string
	 2: attributeID
	 3: attribute
	 4: value
	 5: association
	 6: domain(item)
	 8: groupID
	 9: typeID
	 */
	
	class Expression;
	typedef std::function<Argument(const Expression&)> Operator;
	
	template<int N> Argument operand(const class Expression& expression) {
		assert(0);
	};

	template<int N> Operator getOperator(int n);

	template<int N> Operator getOperator(int n) {
		if (n == N)
			return operand<N>;
		else
			return getOperator<N-1>(n);
	}
	
	template<> Operator getOperator<0>(int n) {
		assert(0);
	}
	
	extern std::map<int32_t, std::shared_ptr<Expression>> expressions;


	class Expression {
	public:
		Argument exec() {
			return getOperator<74>(operandID)(*this);
		}
		
		//private:
		int32_t expressionID;
		int32_t arg1;
		int32_t arg2;
		int32_t typeID;
		int32_t groupID;
		int32_t attributeID;
		int16_t operandID;
		std::string value;
		std::string name;
	};
	
#include "Operands.hpp"

};