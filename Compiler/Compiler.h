#pragma once
#include <stdexcept>
#include "types.h"
#include <sqlite3.h>
#include <cstdlib>
#include <iostream>
#include "Modifier.h"

namespace Compiler {
	void exec(const std::string sql, std::function<bool (sqlite3_stmt* stmt)> callback);
	int32_t getAttributeID(const std::string& attributeName);
	int32_t getGroupID(const std::string& groupName);
	int32_t getTypeID(const std::string& typeName);
	dgmpp::Modifier::Domain getDomainID(const std::string& domain);
	dgmpp::Modifier::Association getAssociationID(const std::string& association);
	std::ostream& operator<<(std::ostream& os, const class Modifier& modifier);

	template <size_t arg1, size_t ... others>
	struct static_max;
	
	template <size_t arg>
	struct static_max<arg>
	{
		static const size_t value = arg;
	};
	
	template <size_t arg1, size_t arg2, size_t ... others>
	struct static_max<arg1, arg2, others...>
	{
		static const size_t value = arg1 >= arg2 ? static_max<arg1, others...>::value :
		static_max<arg2, others...>::value;
	};
	
	template<typename... Ts>
	struct variant_helper;
	
	template<typename F, typename... Ts>
	struct variant_helper<F, Ts...> {
		inline static void destroy(size_t id, void * data)
		{
			if (id == typeid(F).hash_code())
				reinterpret_cast<F*>(data)->~F();
			else
				variant_helper<Ts...>::destroy(id, data);
		}
		
		inline static void move(size_t old_t, void * old_v, void * new_v)
		{
			if (old_t == typeid(F).hash_code())
				new (new_v) F(std::move(*reinterpret_cast<F*>(old_v)));
			else
				variant_helper<Ts...>::move(old_t, old_v, new_v);
		}
		
		inline static void copy(size_t old_t, const void * old_v, void * new_v)
		{
			if (old_t == typeid(F).hash_code())
				new (new_v) F(*reinterpret_cast<const F*>(old_v));
			else
				variant_helper<Ts...>::copy(old_t, old_v, new_v);
		}
		
		template<typename T>
		inline static typename std::enable_if<std::is_trivially_constructible<T, F>::value, T>::type
		cast(size_t typeID, const void* data) {
			if (typeID == typeid(F).hash_code()) {
				return static_cast<T>(*reinterpret_cast<const F*>(data));
			}
			else
				return variant_helper<Ts...>::template cast<T>(typeID, data);
		}
		
		template<typename T>
		inline static typename std::enable_if<!std::is_trivially_constructible<T, F>::value, T>::type
		cast(size_t typeID, const void* data) {
			throw std::bad_cast();
		}
	};
	

	template<typename... Ts>
	struct variant_contains;

	template<typename T1, typename T2, typename... Ts>
	struct variant_contains<T1, T2, Ts...> {
		static const bool value = std::is_same<T1, T2>::value ? true : variant_contains<T1, Ts...>::value;
	};
	
	template<typename T1, typename T2>
	struct variant_contains<T1, T2> {
		static const bool value = std::is_same<T1, T2>::value;
	};

	template<> struct variant_helper<>  {
		inline static void destroy(size_t id, void * data) { }
		inline static void move(size_t old_t, void * old_v, void * new_v) { }
		inline static void copy(size_t old_t, const void * old_v, void * new_v) { }
		template<typename T>
		inline static T cast(size_t typeID, const void* data) {return T();};

	};
	
	template<typename... Ts>
	struct variant {
	private:
		static const size_t data_size = static_max<sizeof(Ts)...>::value;
		static const size_t data_align = static_max<alignof(Ts)...>::value;
		
		using data_t = typename std::aligned_storage<data_size, data_align>::type;
		
		using helper_t = variant_helper<Ts...>;
		
		static inline size_t invalid_type() {
			return typeid(void).hash_code();
		}
		
		size_t type_id;
		data_t data;
	public:
		variant() : type_id(invalid_type()) {   }
		
		variant(const variant<Ts...>& old) : type_id(old.type_id)
		{
			helper_t::copy(old.type_id, &old.data, &data);
		}
		
		variant(variant<Ts...>&& old) : type_id(old.type_id)
		{
			helper_t::move(old.type_id, &old.data, &data);
		}
		
		
		template<typename T>
		variant(const T& value, typename std::enable_if<variant_contains<T, Ts...>::value>::type* = 0) : type_id(typeid(T).hash_code()) {
			helper_t::copy(type_id, &value, &data);
		}
		
		template<typename T>
		typename std::enable_if<variant_contains<T, Ts...>::value, variant<Ts...>&>::type operator=(const T& value) {
			set<T>(value);
		};
		
		// Serves as both the move and the copy asignment operator.
		variant<Ts...>& operator= (variant<Ts...> old)
		{
			std::swap(type_id, old.type_id);
			std::swap(data, old.data);
			
			return *this;
		}
		
		template<typename T>
		void is() {
			return (type_id == typeid(T).hash_code());
		}
		
		void valid() {
			return (type_id != invalid_type());
		}
		
		template<typename T, typename... Args>
		void set(Args&&... args)
		{
			// First we destroy the current contents
			helper_t::destroy(type_id, &data);
			new (&data) T(std::forward<Args>(args)...);
			type_id = typeid(T).hash_code();
		}
		
		template<typename T>
		T get() const
		{
			// It is a dynamic_cast-like behaviour
			if (type_id == typeid(T).hash_code())
				return *reinterpret_cast<const T*>(&data);
			else
				return helper_t::template cast<T>(type_id, &data);
		}
		
		~variant() {
			helper_t::destroy(type_id, &data);
		}
	};
	
	class AttributeID;
	class Attribute;
	class Association;
	class Domain;
	
	class GroupID {
	public:
		GroupID() : groupID(0) {};
		GroupID(int32_t groupID) : groupID(groupID) {};
//	private:
		int32_t groupID;
		bool operator == (const GroupID& other) const {
			return groupID == other.groupID;
		}
		bool operator > (const GroupID& other) const {
			return groupID > other.groupID;
		}
		bool operator < (const GroupID& other) const {
			return groupID < other.groupID;
		}
	};
	
	class TypeID {
	public:
		TypeID() : typeID(0) {};
		TypeID(const std::string& domain) : typeID(0), domain(domain) {}
		TypeID(int32_t typeID) : typeID(typeID) {};

		int32_t typeID;
		std::string domain;
		bool operator == (const TypeID& other) const {
			return typeID == other.typeID && domain == other.domain;
		}
		
		bool operator > (const TypeID& other) const {
			if (typeID == other.typeID)
				return domain > other.domain;
			else
				return typeID > other.typeID;
		}
		bool operator < (const TypeID& other) const {
			if (typeID == other.typeID)
				return domain < other.domain;
			else
				return typeID < other.typeID;
		}

	};
	
	class Domain {
	public:
		Domain() {};
		Domain(const std::string& domain) : domain(domain) {};
		Domain(const Domain& other, const GroupID& groupID) : locationGroup(groupID), domain(other.domain), requiredSkill(other.requiredSkill) {}
		Domain(const Domain& other, const TypeID& typeID) : requiredSkill(typeID), domain(other.domain), locationGroup(other.locationGroup) {}
		
		Attribute getAttribute(const AttributeID& attributeID);
		TypeID getTypeID();
		Domain getLocationGroup(const GroupID& groupID);
		Domain getRequiredSkill(const TypeID& typeID);
		
//	private:
		std::string domain;
		GroupID locationGroup;
		TypeID requiredSkill;
		bool operator == (const Domain& other) const {
			return domain == other.domain && locationGroup == other.locationGroup && requiredSkill == other.requiredSkill;
		}
		bool operator > (const Domain& other) const {
			if (domain == other.domain) {
				if (locationGroup == other.locationGroup)
					return requiredSkill > other.requiredSkill;
				else
					return locationGroup > other.locationGroup;
			}
			else
				return domain > other.domain;
		}

		bool operator < (const Domain& other) const {
			if (domain == other.domain) {
				if (locationGroup == other.locationGroup)
					return requiredSkill < other.requiredSkill;
				else
					return locationGroup < other.locationGroup;
			}
			else
				return domain < other.domain;
		}
};
	
	class AttributeID {
	public:
		AttributeID() : attributeID(0) {};
		AttributeID(int32_t attributeID) : attributeID(attributeID) {};
	//private:
		int32_t attributeID;
		bool operator == (const AttributeID& other) const {
			return attributeID == other.attributeID;
		}
		
		bool operator > (const AttributeID& other) const {
			return attributeID > other.attributeID;
		}
		bool operator < (const AttributeID& other) const {
			return attributeID < other.attributeID;
		}
	};

	class Attribute {
	public:
		Attribute() {};
		Attribute(const Domain& domain, const AttributeID& attributeID) : domain(domain), attributeID(attributeID) {};
		
		bool set(float value);
		bool inc(float value);
		bool dec(float value);
		bool dec(const AttributeID& attributeID);
		bool inc(const AttributeID& attributeID);
		bool set(const AttributeID& attributeID);
		Association getAssociation(const std::string& name);
//	private:
		AttributeID attributeID;
		Domain domain;
		bool operator == (const Attribute& other) const {
			return attributeID == other.attributeID && domain == other.domain;
		}
		
		bool operator > (const Attribute& other) const {
			if (attributeID == other.attributeID)
				return domain > other.domain;
			else
				return attributeID > other.attributeID;
		}
		bool operator < (const Attribute& other) const {
			if (attributeID == other.attributeID)
				return domain < other.domain;
			else
				return attributeID < other.attributeID;
		}
	};
	
	typedef std::string AssociationName;

	class Association {
	public:
		Association() {};
		Association(const Attribute& attribute, const std::string& name) : attribute(attribute), name(name) {};
		
		bool addItemModifier(const AttributeID attributeID);
		bool addLocationGroupModifier(const AttributeID attributeID);
		bool addLocationModifier(const AttributeID attributeID);
		bool addLocationRequiredSkillModifier(const AttributeID attributeID);
		bool addOwnerRequiredSkillModifier(const AttributeID attributeID);
//	private:
		Attribute attribute;
		std::string name;
		
		bool operator == (const Association& other) const {
			return attribute == other.attribute && name == other.name;
		}
		bool operator > (const Association& other) const {
			if (attribute == other.attribute)
				return name > other.name;
			else
				return attribute > other.attribute;
		}
		bool operator < (const Association& other) const {
			if (attribute == other.attribute)
				return name < other.name;
			else
				return attribute < other.attribute;
		}

	};
	
	using Value = variant<int, double, bool, std::string>;
	using Argument = variant<AssociationName, AttributeID, Attribute, Value, Association, Domain, GroupID, TypeID>;
	
	
	class Expression;
	typedef std::function<Argument(const Expression&)> Operator;
	
	template<int N> Argument operand(const class Expression& expression) {
		return Value(true);
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
		
		template<typename T, int N>
		T get() const
		{
			if (N == 0)
				return expressions[arg1]->exec().get<T>();
			else if (N == 1)
				return expressions[arg2]->exec().get<T>();
			else
				throw std::bad_cast();
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
	
	class Modifier {
	public:
		Modifier(dgmpp::Modifier::Type type, const Association& association, const AttributeID& attributeID, int32_t modifierID): type(type), modifiedAssociation(association), modifyingAttributeID(attributeID), modifierID(modifierID) {}
		
		//friend std::ostream& operator<<(std::ostream& os, Modifier& modifier);
		
		Association modifiedAssociation;
		AttributeID modifyingAttributeID;
		int32_t modifierID;
		dgmpp::Modifier::Type type;
		
		
		bool operator == (const Modifier& other) const {
			return modifiedAssociation == other.modifiedAssociation && modifyingAttributeID == other.modifyingAttributeID;
		}
		bool operator > (const Modifier& other) const {
			if (modifyingAttributeID == other.modifyingAttributeID)
				return modifiedAssociation > other.modifiedAssociation;
			else
				return modifyingAttributeID > other.modifyingAttributeID;
		}
		bool operator < (const Modifier& other) const {
			if (modifyingAttributeID == other.modifyingAttributeID)
				return modifiedAssociation < other.modifiedAssociation;
			else
				return modifyingAttributeID < other.modifyingAttributeID;
		}
	private:
	};
	
	class Mutator {
	public:
		enum MutatorType{
			MutatorTypeInc,
			MutatorTypeDec,
			MutatorTypeSet
		};

		Mutator(const Attribute& attribute, float value, MutatorType type) : modifiedAttribute(attribute), modifyingValue(value), type(type) {};

		Mutator(const Attribute& attribute, const AttributeID& attributeID, MutatorType type) : modifiedAttribute(attribute), modifyingAttributeID(attributeID), type(type), modifyingValue(0) {};

		Attribute modifiedAttribute;
		AttributeID modifyingAttributeID;
		float modifyingValue;
		MutatorType type;
	};
	
	class Effect {
	public:
		int32_t effectID;
		std::list<Modifier> modifiers;
		std::list<Mutator> mutators;
	};
	
#include "Operands.hpp"

};