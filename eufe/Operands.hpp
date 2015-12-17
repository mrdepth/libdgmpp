
template<typename T, int N> T get(const class Expression& expression) {
	if (N == 0)
		return static_cast<T>(expressions[expression.arg1]->exec());
	else if (N == 1)
		return static_cast<T>(expressions[expression.arg2]->exec());
	else
		assert(0);
};

template<typename T> std::shared_ptr<T> get(const class Expression& expression) {
	return std::make_shared<T>(expression.value);
};


//"1, ADD, add two numbers, (%(arg1)s)+(%(arg2)s)"
template<> Argument operand<1>(const class Expression& expression) {
	auto arg0 = get<Value, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return arg0 + arg1;
}

//"2, AGGM, add gang groupl modifier, [%(arg1)s].AGGM(%(arg2)s)"
template<> Argument operand<2>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addLocationGroupModifier(arg1);
}

//"3, AGIM, add gang shipl modifier, [%(arg1)s].AGIM(%(arg2)s)"
template<> Argument operand<3>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addLocationModifier(arg1);
}

//"4, AGORSM, add gang owner required skill modifier, [%(arg1)s].AGORSM(%(arg2)s)"
template<> Argument operand<4>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addOwnerRequiredSkillModifier(arg1);
}

//"5, AGRSM, add gang required skill modifier, [%(arg1)s].AGRSM(%(arg2)s)"
template<> Argument operand<5>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addLocationRequiredSkillModifier(arg1);
}

//"6, AGRSM, add gang required skill modifier, [%(arg1)s].AGRSM(%(arg2)s)"
template<> Argument operand<6>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addItemModifier(arg1);
}

//"7, ALGM, add location group modifier, (%(arg1)s).AddLocationGroupModifier (%(arg2)s)"
template<> Argument operand<7>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addLocationGroupModifier(arg1);
}

//"8, ALM, add location modifier, (%(arg1)s).AddLocationModifier (%(arg2)s)"
template<> Argument operand<8>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addLocationModifier(arg1);
}

//"9, ALRSM, add location required skill modifier, (%(arg1)s).ALRSM(%(arg2)s)"
template<> Argument operand<9>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addLocationRequiredSkillModifier(arg1);
}

//"10, AND, logical and operation, (%(arg1)s) AND (%(arg2)s)"
template<> Argument operand<10>(const class Expression& expression) {
	auto arg0 = get<Value, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return static_cast<bool>(arg0) && static_cast<bool>(arg1);
}

//"11, AORSM, add owner required skill modifier, (%(arg1)s).AORSM(%(arg2)s)"
template<> Argument operand<11>(const class Expression& expression) {
	auto arg0 = get<Association, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.addOwnerRequiredSkillModifier(arg1);
}

//"12, ATT, attribute, %(arg1)s->%(arg2)s"
template<> Argument operand<12>(const class Expression& expression) {
	auto arg0 = get<Domain, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.getAttribute(arg1);
}

//"17, COMBINE, executes two statements, %(arg1)s);     (%(arg2)s"
template<> Argument operand<17>(const class Expression& expression) {
	get<Value, 0>(expression);
	get<Value, 1>(expression);
	return true;
}

//"18, DEC, decreases an item-attribute by the value of another attribute, %(arg1)s-=self.%(arg2)s"
template<> Argument operand<18>(const class Expression& expression) {
	auto arg0 = get<Attribute, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.dec(arg1);
}

//"20, DECN, decreases an item-attribute by number, %(arg1)s-=%(arg2)s"
template<> Argument operand<20>(const class Expression& expression) {
	auto arg0 = get<Attribute, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return arg0.dec(arg1);
}

//"21, DEFASSOCIATION, define attribute association type, %(value)s"
template<> Argument operand<21>(const class Expression& expression) {
	return AssociationName(expression.value);
}

//"22, DEFATTRIBUTE, define attribute, %(value)s"
template<> Argument operand<22>(const class Expression& expression) {
	int32_t attributeID = expression.attributeID;
	if (!attributeID)
		attributeID = getAttributeID(expression.value);
	if (!attributeID)
		attributeID = getAttributeID(expression.name);
	return AttributeID(attributeID);
}

//"23, DEFBOOL, define bool constant, Bool(%(value)s)"
template<> Argument operand<23>(const class Expression& expression) {
	return static_cast<bool>(std::atoi(expression.value.c_str()));
}

//"24, DEFENVIDX, define environment index, Current%(value)s"
template<> Argument operand<24>(const class Expression& expression) {
	return Domain(expression.value);
}

//"25, DEFFLOAT, defines a float constant, Float(%(value)s)"
template<> Argument operand<25>(const class Expression& expression) {
	return std::atof(expression.value.c_str());
}

//"26, DEFGROUP, define group, %(value)s"
template<> Argument operand<26>(const class Expression& expression) {
	int32_t groupID = expression.groupID;
	if (!groupID)
		groupID = getGroupID(expression.value);
	if (!groupID)
		groupID = getGroupID(expression.name);
	return GroupID(groupID);
}

//"27, DEFINT, defines an int constant, Int(%(value)s)"
template<> Argument operand<27>(const class Expression& expression) {
	return std::atoi(expression.value.c_str());
}

//"28, DEFSTRING, defines a string constant, ""%(value)s"""
template<> Argument operand<28>(const class Expression& expression) {
	return Value(expression.value);
}

//"29, DEFTYPEID, define a type ID, Type(%(value)s)"
template<> Argument operand<29>(const class Expression& expression) {
	int32_t typeID = expression.typeID;
	if (!typeID)
		typeID = getTypeID(expression.value);
	if (!typeID)
		typeID = getTypeID(expression.name);
	return TypeID(typeID);
}

//"31, EFF, define association type, (%(arg2)s).(%(arg1)s)"
template<> Argument operand<31>(const class Expression& expression) {
	auto arg0 = get<AssociationName, 0>(expression);
	auto arg1 = get<Attribute, 1>(expression);
	return arg1.getAssociation(arg0);
}

//"33, EQ, checks for equality, %(arg1)s == %(arg2)s"
template<> Argument operand<33>(const class Expression& expression) {
	auto arg0 = get<Value, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return static_cast<float>(arg0) == static_cast<float>(arg1);
}

//"34, GA, attribute on a module group, %(arg1)s.%(arg2)s"
template<> Argument operand<34>(const class Expression& expression) {
	auto arg0 = get<GroupID, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return Domain("Gang").getLocationGroup(arg0).getAttribute(arg1);
}

//"36, GETTYPE, gets type of item, %(arg1)s.GetTypeID()"
template<> Argument operand<36>(const class Expression& expression) {
	auto arg0 = get<Domain, 0>(expression);
	return arg0.getTypeID();
}

//"37, GM, get a module of a given groupID from a given location (ship or player), %(arg1)s.%(arg2)s"
template<> Argument operand<37>(const class Expression& expression) {
	auto arg0 = get<Domain, 0>(expression);
	auto arg1 = get<GroupID, 1>(expression);
	return arg0.getLocationGroup(arg1);
}

//"38, GT, checks whether expression 1  is greater than expression 2, %(arg1)s> %(arg2)s"
template<> Argument operand<38>(const class Expression& expression) {
	auto arg0 = get<Value, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return static_cast<float>(arg0) > static_cast<float>(arg1);
}

//"39, GTE, checks whether an expression is greater than or equal to another, %(arg1)s>=%(arg2)s"
template<> Argument operand<39>(const class Expression& expression) {
	auto arg0 = get<Value, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return static_cast<float>(arg0) >= static_cast<float>(arg1);
}

//"40, IA, generic attribute, %(arg1)s"
template<> Argument operand<40>(const class Expression& expression) {
	auto arg0 = get<AttributeID, 0>(expression);
	return Domain("Gang").getAttribute(arg0);
}

//"41, IF, if construct, If(%(arg1)s), Then (%(arg2)s)"
template<> Argument operand<41>(const class Expression& expression) {
	get<Value, 0>(expression);
	get<Value, 1>(expression);
	return true;
}

//"42, INC, increases an item-attribute by the value of another attribute, %(arg1)s+=self.%(arg2)s"
template<> Argument operand<42>(const class Expression& expression) {
	auto arg0 = get<Attribute, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return arg0.dec(arg1);
}

//"43, INCN, increases an item-attribute by a number, %(arg1)s+=%(arg2)s"
template<> Argument operand<43>(const class Expression& expression) {
	auto arg0 = get<Attribute, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return arg0.dec(arg1);
}

//"48, LG, specify a group in a location, %(arg1)s..%(arg2)s"
template<> Argument operand<48>(const class Expression& expression) {
	auto arg0 = get<Domain, 0>(expression);
	auto arg1 = get<GroupID, 1>(expression);
	return arg0.getLocationGroup(arg1);
}

//"49, LS, location - skill required item group, %(arg1)s[%(arg2)s]"
template<> Argument operand<49>(const class Expression& expression) {
	auto arg0 = get<Domain, 0>(expression);
	auto arg1 = get<TypeID, 1>(expression);
	return arg0.getRequiredSkill(arg1);
}

//"51, MUL, multiplies two numbers, (%(arg1)s)*(%(arg2)s)"
template<> Argument operand<51>(const class Expression& expression) {
	auto arg0 = get<Value, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return arg0 * arg1;
}

//"52, OR, logical or operation, %(arg1)s OR %(arg2)s"
template<> Argument operand<52>(const class Expression& expression) {
	get<Value, 0>(expression);
	return true;
}

//"64, RSA, attribute on modules that have required skill, %(arg1)s.%(arg2)s"
template<> Argument operand<64>(const class Expression& expression) {
	auto arg0 = get<TypeID, 0>(expression);
	auto arg1 = get<AttributeID, 1>(expression);
	return Domain("Gang").getRequiredSkill(arg0).getAttribute(arg1);
}

//"65, SET, sets an item attribute, %(arg1)s := %(arg2)s"
template<> Argument operand<65>(const class Expression& expression) {
	auto arg0 = get<Attribute, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return arg0.set(arg1);
}

//"68, SUB, subtracts a number from another one, %(arg1)s-%(arg2)s"
template<> Argument operand<68>(const class Expression& expression) {
	auto arg0 = get<Value, 0>(expression);
	auto arg1 = get<Value, 1>(expression);
	return arg0 - arg1;
}