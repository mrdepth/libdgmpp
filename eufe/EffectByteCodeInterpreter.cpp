#include <sstream>
#include "EffectByteCodeInterpreter.h"
#include "Engine.h"
//#include "Compiler.h"
#include "Item.h"
#include "Attribute.h"
#include "Character.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"

using namespace eufe;

EffectByteCodeInterpreter::OperandsVector EffectByteCodeInterpreter::operands = EffectByteCodeInterpreter::InitOperands();

EffectByteCodeInterpreter::OperandsVector EffectByteCodeInterpreter::InitOperands()
{
	OperandsVector operands;
	operands.push_back(&EffectByteCodeInterpreter::operand0);
	operands.push_back(&EffectByteCodeInterpreter::operand1);
	operands.push_back(&EffectByteCodeInterpreter::operand2);
	operands.push_back(&EffectByteCodeInterpreter::operand3);
	operands.push_back(&EffectByteCodeInterpreter::operand4);
	operands.push_back(&EffectByteCodeInterpreter::operand5);
	operands.push_back(&EffectByteCodeInterpreter::operand6);
	operands.push_back(&EffectByteCodeInterpreter::operand7);
	operands.push_back(&EffectByteCodeInterpreter::operand8);
	operands.push_back(&EffectByteCodeInterpreter::operand9);
	operands.push_back(&EffectByteCodeInterpreter::operand10);
	operands.push_back(&EffectByteCodeInterpreter::operand11);
	operands.push_back(&EffectByteCodeInterpreter::operand12);
	operands.push_back(&EffectByteCodeInterpreter::operand13);
	operands.push_back(&EffectByteCodeInterpreter::operand14);
	operands.push_back(&EffectByteCodeInterpreter::operand15);
	operands.push_back(&EffectByteCodeInterpreter::operand16);
	operands.push_back(&EffectByteCodeInterpreter::operand17);
	operands.push_back(&EffectByteCodeInterpreter::operand18);
	operands.push_back(&EffectByteCodeInterpreter::operand19);
	operands.push_back(&EffectByteCodeInterpreter::operand20);
	operands.push_back(&EffectByteCodeInterpreter::operand21);
	operands.push_back(&EffectByteCodeInterpreter::operand22);
	operands.push_back(&EffectByteCodeInterpreter::operand23);
	operands.push_back(&EffectByteCodeInterpreter::operand24);
	operands.push_back(&EffectByteCodeInterpreter::operand25);
	operands.push_back(&EffectByteCodeInterpreter::operand26);
	operands.push_back(&EffectByteCodeInterpreter::operand27);
	operands.push_back(&EffectByteCodeInterpreter::operand28);
	operands.push_back(&EffectByteCodeInterpreter::operand29);
	operands.push_back(&EffectByteCodeInterpreter::operand30);
	operands.push_back(&EffectByteCodeInterpreter::operand31);
	operands.push_back(&EffectByteCodeInterpreter::operand32);
	operands.push_back(&EffectByteCodeInterpreter::operand33);
	operands.push_back(&EffectByteCodeInterpreter::operand34);
	operands.push_back(&EffectByteCodeInterpreter::operand35);
	operands.push_back(&EffectByteCodeInterpreter::operand36);
	operands.push_back(&EffectByteCodeInterpreter::operand37);
	operands.push_back(&EffectByteCodeInterpreter::operand38);
	operands.push_back(&EffectByteCodeInterpreter::operand39);
	operands.push_back(&EffectByteCodeInterpreter::operand40);
	operands.push_back(&EffectByteCodeInterpreter::operand41);
	operands.push_back(&EffectByteCodeInterpreter::operand42);
	operands.push_back(&EffectByteCodeInterpreter::operand43);
	operands.push_back(&EffectByteCodeInterpreter::operand44);
	operands.push_back(&EffectByteCodeInterpreter::operand45);
	operands.push_back(&EffectByteCodeInterpreter::operand46);
	operands.push_back(&EffectByteCodeInterpreter::operand47);
	operands.push_back(&EffectByteCodeInterpreter::operand48);
	operands.push_back(&EffectByteCodeInterpreter::operand49);
	operands.push_back(&EffectByteCodeInterpreter::operand50);
	operands.push_back(&EffectByteCodeInterpreter::operand51);
	operands.push_back(&EffectByteCodeInterpreter::operand52);
	operands.push_back(&EffectByteCodeInterpreter::operand53);
	operands.push_back(&EffectByteCodeInterpreter::operand54);
	operands.push_back(&EffectByteCodeInterpreter::operand55);
	operands.push_back(&EffectByteCodeInterpreter::operand56);
	operands.push_back(&EffectByteCodeInterpreter::operand57);
	operands.push_back(&EffectByteCodeInterpreter::operand58);
	operands.push_back(&EffectByteCodeInterpreter::operand59);
	operands.push_back(&EffectByteCodeInterpreter::operand60);
	operands.push_back(&EffectByteCodeInterpreter::operand61);
	operands.push_back(&EffectByteCodeInterpreter::operand62);
	operands.push_back(&EffectByteCodeInterpreter::operand63);
	operands.push_back(&EffectByteCodeInterpreter::operand64);
	operands.push_back(&EffectByteCodeInterpreter::operand65);
	operands.push_back(&EffectByteCodeInterpreter::operand66);
	operands.push_back(&EffectByteCodeInterpreter::operand67);
	operands.push_back(&EffectByteCodeInterpreter::operand68);
	operands.push_back(&EffectByteCodeInterpreter::operand69);
	operands.push_back(&EffectByteCodeInterpreter::operand70);
	operands.push_back(&EffectByteCodeInterpreter::operand71);
	operands.push_back(&EffectByteCodeInterpreter::operand72);
	operands.push_back(&EffectByteCodeInterpreter::operand73);
	operands.push_back(&EffectByteCodeInterpreter::operand74);
	
	return operands;
}

EffectByteCodeInterpreter::EffectByteCodeInterpreter(std::shared_ptr<Engine> const& engine, const void* byteCode, size_t size, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
{
	byteCode_ = new Byte[size];
	memcpy(byteCode_, byteCode, size);
	endPtr_ = byteCode_ + size;
	preExpression_ = byteCode_ + *reinterpret_cast<int*>(byteCode_);
	postExpression_ = byteCode_ + *reinterpret_cast<int*>(byteCode_ + sizeof(int));
}

EffectByteCodeInterpreter::EffectByteCodeInterpreter(const EffectByteCodeInterpreter& from) : engine_(from.engine_), isAssistance_(from.isAssistance_), isOffensive_(from.isOffensive_)
{
	size_t size = from.endPtr_ - from.byteCode_;
	byteCode_ = new Byte[size];
	memcpy(byteCode_, from.byteCode_, size);
	endPtr_ = byteCode_ + size;
	preExpression_ = byteCode_ + *reinterpret_cast<int*>(byteCode_);
	postExpression_ = byteCode_ + *reinterpret_cast<int*>(byteCode_ + sizeof(int));
}

EffectByteCodeInterpreter::~EffectByteCodeInterpreter(void)
{
	delete[] byteCode_;
}

bool EffectByteCodeInterpreter::addEffect(const Environment& environment)
{
	environment_ = environment;
	Argument arg = execute(preExpression_);
	bool result;
	try {
		result = arg;
	}
	catch(eufe::EffectByteCodeInterpreter::Argument::TypeCastException&) {
		result = false;
	}
	environment_ = Environment();
	return result;
}

bool EffectByteCodeInterpreter::removeEffect(const Environment& environment)
{
	environment_ = environment;
	Argument arg = execute(postExpression_);
	bool result;
	try {
		result = arg;
	}
	catch(eufe::EffectByteCodeInterpreter::Argument::TypeCastException&) {
		result = false;
	}
	environment_ = Environment();
	return result;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::execute(const Byte *expression)
{
	const Byte* ptr = expression;
	while (1) {
		Opcode opcode = static_cast<Opcode>(*ptr);
		ptr++;
		switch(opcode) {
			case OPCODE_ARGUMENT :
			{
				ArgumentType type = static_cast<ArgumentType>(*ptr);
				ptr++;
				short length = *reinterpret_cast<const short*>(ptr);
				ptr += sizeof(short);
				
				if (type == ARGUMENT_TYPE_INT)
					stack_.push_back(Argument(*reinterpret_cast<const int*>(ptr)));
				else if (type == ARGUMENT_TYPE_STRING)
					stack_.push_back(Argument(reinterpret_cast<const char*>(ptr)));
				else if (type == ARGUMENT_TYPE_EXPRESSION)
					stack_.push_back(Argument(*reinterpret_cast<const int*>(ptr), Argument::TYPE_EXPRESSION));
				
				ptr += length;
				break;
			}
			case OPCODE_OPERAND:
			{
				TypeID operandID = *reinterpret_cast<const TypeID*>(ptr);
				OperandPtr operand = operands[operandID];
				return (this->*operand)();
			}
		};
	}
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand0()
{
	throw BadOperandException("0");
}

//"1, ADD, add two numbers, (%(arg1)s)+(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand1()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	return static_cast<float>(arg1) + static_cast<float>(arg2);
}

//"2, AGGM, add gang groupl modifier, [%(arg1)s].AGGM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand2()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"3, AGIM, add gang shipl modifier, [%(arg1)s].AGIM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand3()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"4, AGORSM, add gang owner required skill modifier, [%(arg1)s].AGORSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand4()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"5, AGRSM, add gang required skill modifier, [%(arg1)s].AGRSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand5()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"6, AIM, add item modifier, (%(arg1)s).AddItemModifier (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand6()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addItemModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"7, ALGM, add location group modifier, (%(arg1)s).AddLocationGroupModifier (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand7()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"8, ALM, add location modifier, (%(arg1)s).AddLocationModifier (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand8()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"9, ALRSM, add location required skill modifier, (%(arg1)s).ALRSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand9()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"10, AND, logical and operation, (%(arg1)s) AND (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand10()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (static_cast<bool>(arg1))
	{
		if (arg2.getType() == Argument::TYPE_EXPRESSION)
			arg2 = execute(byteCode_ + static_cast<int>(arg2));
		return arg2;
	}
	return false;
}

//"11, AORSM, add owner required skill modifier, (%(arg1)s).AORSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand11()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"12, ATT, attribute, %(arg1)s->%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand12()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	std::shared_ptr<ItemWrapper> item = arg1;
	TypeID attributeID = arg2;
	return std::shared_ptr<AttributeWrapper>(new AttributeWrapper(item, attributeID));
}

//"13, ATTACK, attack given ship, Attack"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand13()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return true;
}

//"14, CARGOSCAN, Scans the cargo of the targeted ship., CargoScan"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand14()
{
	return true;
}

//"15, CHEATTELEDOCK, Instantly enter a station., CheatTeleDock()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand15()
{
	return true;
}

//"16, CHEATTELEGATE, Automatically invoke a stargate destination from remote distances., CheatTeleGate()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand16()
{
	return true;
}

//"17, COMBINE, executes two statements, %(arg1)s);     (%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand17()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	return true;
}

//"18, DEC, decreases an item-attribute by the value of another attribute, %(arg1)s-=self.%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand18()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ATTRIBUTE)
		return false;
	
	std::shared_ptr<AttributeWrapper> attribute = arg1;
	//float value = environment_["Self"]->getAttribute(arg2)->getValue();
	float value = environment_.self->getAttribute(arg2)->getValue();
	attribute->dec(value);
	return true;
}

//"19, DECLOAKWAVE, broadcasts a decloaking wave, DecloakWave"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand19()
{
	return true;
}

//"20, DECN, decreases an item-attribute by number, %(arg1)s-=%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand20()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ATTRIBUTE)
		return false;
	
	std::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = arg2;
	attribute->dec(value);
	return true;
}

//"21, DEFASSOCIATION, define attribute association type, %(value)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand21()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	
	if (arg1.getType() == Argument::TYPE_STRING)
		return arg1;
	else
		return "SkillTime";
}

//"22, DEFATTRIBUTE, define attribute, %(value)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand22()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

//"23, DEFBOOL, define bool constant, Bool(%(value)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand23()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

//"24, DEFENVIDX, define environment index, Current%(value)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand24()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	std::string key = arg1;
	Item* item = environment_[key];
	if (item)
		return std::shared_ptr<ItemWrapper>(new ItemWrapper(item));
	else
		return false;
}

//"25, DEFFLOAT, defines a float constant, Float(%(value)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand25()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

//"26, DEFGROUP, define group, %(value)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand26()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

//"27, DEFINT, defines an int constant, Int(%(value)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand27()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

//"28, DEFSTRING, defines a string constant, ""%(value)s"""
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand28()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

//"29, DEFTYPEID, define a type ID, Type(%(value)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand29()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	
	if (arg1.getType() == Argument::TYPE_STRING)
	{
		std::string typeName = arg1;
		std::stringstream sql;
		sql << "SELECT typeID FROM invTypes WHERE typeName = \"" << typeName << "\"";
		
		std::shared_ptr<FetchResult> result = engine_.lock()->getSqlConnector()->exec(sql.str().c_str());
		if (result->next())
		{
			TypeID typeID = result->getInt(0);
			return typeID;
		}
		else
		{
			throw UnknownTypeNameException(typeName);
		}
		
	}
	else
		return arg1;
}

//"30, ECMBURST, Clears all targets on all ships(excluding self) wihin range. , ECMBurst()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand30()
{
	return true;
}

//"31, EFF, define association type, (%(arg2)s).(%(arg1)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand31()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	
	if (arg2.getType() != Argument::TYPE_ATTRIBUTE)
		return false;
	
	std::string associationName = arg1;
	std::shared_ptr<AttributeWrapper> attribute = arg2;
	return std::shared_ptr<AssociationWrapper>(new AssociationWrapper(attribute, associationName));
}

//"32, EMPWAVE, broadcasts an EMP wave, EMPWave"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand32()
{
	return true;
}

//"33, EQ, checks for equality, %(arg1)s == %(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand33()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	return static_cast<float>(arg1) == static_cast<float>(arg2);
}

//"34, GA, attribute on a module group, %(arg1)s.%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand34()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (!environment_.gang)
		return false;
	
	TypeID groupID = arg1;
	TypeID attributeID = arg2;
	std::shared_ptr<ItemWrapper> item = std::make_shared<ItemWrapper>(environment_.gang);
	item->setGroupID(groupID);
	return std::make_shared<AttributeWrapper>(item, attributeID);
}

//"35, GET, calculate attribute, %(arg1)s.%(arg2)s()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand35()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	std::shared_ptr<ItemWrapper> item = arg1;
	TypeID attributeID = arg2;
	return item->getItem()->getAttribute(attributeID)->getValue();
}

//"36, GETTYPE, gets type of item, %(arg1)s.GetTypeID()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand36()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	std::shared_ptr<ItemWrapper> item = arg1;
	return item->getItem()->getTypeID();
}

//"37, GM, get a module of a given groupID from a given location (ship or player), %(arg1)s.%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand37()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	std::shared_ptr<ItemWrapper> item = arg1;
	TypeID groupID = static_cast<TypeID>(arg2);
	item->setGroupID(groupID);
	return item;
}

//"38, GT, checks whether expression 1  is greater than expression 2, %(arg1)s> %(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand38()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	return static_cast<float>(arg1) > static_cast<float>(arg2);
}

//"39, GTE, checks whether an expression is greater than or equal to another, %(arg1)s>=%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand39()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	return static_cast<float>(arg1) >= static_cast<float>(arg2);
}

//"40, IA, generic attribute, %(arg1)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand40()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	
	if (!environment_.gang)
		return false;
	
	TypeID attributeID = arg1;
	std::shared_ptr<ItemWrapper> item = std::make_shared<ItemWrapper>(environment_.gang);
	return std::make_shared<AttributeWrapper>(item, attributeID);
}

//"41, IF, if construct, If(%(arg1)s), Then (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand41()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (static_cast<bool>(arg1))
	{
		if (arg2.getType() == Argument::TYPE_EXPRESSION)
			arg2 = execute(byteCode_ + static_cast<int>(arg2));
		return true;
	}
	return false;
}

//"42, INC, increases an item-attribute by the value of another attribute, %(arg1)s+=self.%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand42()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ATTRIBUTE)
		return false;
	
	std::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = environment_.self->getAttribute(arg2)->getValue();
	attribute->inc(value);
	return true;
}

//"43, INCN, increases an item-attribute by a number, %(arg1)s+=%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand43()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ATTRIBUTE)
		return false;
	
	std::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = arg2;
	attribute->inc(value);
	return true;
}

//"44, LAUNCH, launches a missile, LaunchMissile()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand44()
{
	return true;
}

//"45, LAUNCHDEFENDERMISSILE, launches a defender missile, LaunchDefenderMissile()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand45()
{
	return true;
}

//"46, LAUNCHDRONE, launches a drone., LaunchDrone()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand46()
{
	return true;
}

//"47, LAUNCHFOFMISSILE, launches an FOF missile, LaunchFOFMissile()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand47()
{
	return true;
}

//"48, LG, specify a group in a location, %(arg1)s..%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand48()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	std::shared_ptr<ItemWrapper> item = arg1;
	TypeID groupID = arg2;
	item->setGroupID(groupID);
	return item;
}

//"49, LS, location - skill required item group, %(arg1)s[%(arg2)s]"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand49()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	std::shared_ptr<ItemWrapper> item = arg1;
	TypeID skillID = arg2;
	item->setRequiredSkillID(skillID);
	return item;
}

//"50, MINE, mines an asteroid, Mine"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand50()
{
	return true;
}

//"51, MUL, multiplies two numbers, (%(arg1)s)*(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand51()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	return static_cast<float>(arg1) * static_cast<float>(arg2);
}

//"52, OR, logical or operation, %(arg1)s OR %(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand52()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (!static_cast<bool>(arg1))
	{
		if (arg2.getType() == Argument::TYPE_EXPRESSION)
			arg2 = execute(byteCode_ + static_cast<int>(arg2));
		return arg2;
	}
	else
		return true;
}

//"53, POWERBOOST, , PowerBoost"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand53()
{
	return true;
}

//"54, RGGM, remove gang groupl modifier, [%(arg1)s].RGGM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand54()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"55, RGIM, remove gang shipl modifier, [%(arg1)s].RGIM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand55()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"56, RGORSM, remove a gang owner required skill modifier, [%(arg1)s].RGORSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand56()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"57, RGRSM, remove a gang required skill modifier, [%(arg1)s].RGRSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand57()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}


//"58, RIM, remove  item modifier, (%(arg1)s).RemoveItemModifier (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand58()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeItemModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"59, RLGM, remove location group modifier, (%(arg1)s).RemoveLocationGroupModifier (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand59()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"60, RLM, remove location modifier, (%(arg1)s).RemoveLocationModifier (%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand60()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"61, RLRSM, remove a  required skill modifier, (%(arg1)s).RLRSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand61()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"62, RORSM, remove an owner required skill modifier, (%(arg1)s).RORSM(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand62()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ASSOCIATION)
		return false;
	
	std::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

//"63, RS, true if arg1 requires arg2, %(arg1)s.Requires(%(arg2)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand63()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	std::shared_ptr<ItemWrapper> item = arg1;
	TypeID skillID = arg2;
	return item->getItem()->requireSkill(skillID);
}

//"64, RSA, attribute on modules that have required skill, %(arg1)s.%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand64()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (!environment_.gang)
		return false;
	
	TypeID skillID = arg1;
	TypeID attributeID = arg2;
	std::shared_ptr<ItemWrapper> item = std::make_shared<ItemWrapper>(environment_.gang);
	item->setRequiredSkillID(skillID);
	return std::make_shared<AttributeWrapper>(item, attributeID);
	
}

//"65, SET, sets an item attribute, %(arg1)s := %(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand65()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	
	if (arg1.getType() != Argument::TYPE_ATTRIBUTE)
		return false;
	
	std::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = arg2;
	attribute->setValue(value);
	return true;
}

//"66, SHIPSCAN, scans a ship, ShipScan()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand66()
{
	return true;
}

//"67, SKILLCHECK, , SkillCheck(%(arg1)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand67()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return true;
}

//"68, SUB, subtracts a number from another one, %(arg1)s-%(arg2)s"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand68()
{
	Argument arg2 = *stack_.rbegin();
	stack_.pop_back();
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	if (arg2.getType() == Argument::TYPE_EXPRESSION)
		arg2 = execute(byteCode_ + static_cast<int>(arg2));
	return static_cast<float>(arg1) - static_cast<float>(arg2);
}

//"69, SURVEYSCAN, scans an asteroid for information, SurveyScan()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand69()
{
	return true;
}

//"70, TARGETHOSTILES, Targets any hostile ships within range (assuming electronics have capability)., TargetHostiles()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand70()
{
	return true;
}

//"71, TARGETSILENTLY, , TargetSilently()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand71()
{
	return true;
}

//"72, TOOLTARGETSKILLS,  , CheckToolTargetSkills"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand72()
{
	return true;
}

//"73, UE, raises an user error, UserError(%(arg1)s)"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand73()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

//"74, VERIFYTARGETGROUP, raises a user error if incorrect target group, VerifyTargetGroup()"
EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand74()
{
	return true;
}


float EffectByteCodeInterpreter::AttributeWrapper::getValue()
{
	return item_->getItem()->getAttribute(attributeID_)->getValue();
}

void EffectByteCodeInterpreter::AttributeWrapper::setValue(float value)
{
	item_->getItem()->getAttribute(attributeID_)->setValue(value);
}

void EffectByteCodeInterpreter::AttributeWrapper::inc(float value)
{
	item_->getItem()->getAttribute(attributeID_)->inc(value);
}

void EffectByteCodeInterpreter::AttributeWrapper::dec(float value)
{
	item_->getItem()->getAttribute(attributeID_)->dec(value);
}

EffectByteCodeInterpreter::AssociationWrapper::AssociationWrapper(std::shared_ptr<AttributeWrapper> const& attribute, const std::string& name) : attribute_(attribute)
{
	if (name == "PreAssignment")
		association_ = Modifier::ASSOCIATION_POST_ASSIGNMENT;
	else if (name == "PreDiv")
		association_ = Modifier::ASSOCIATION_PRE_DIV;
	else if (name == "PreMul")
		association_ = Modifier::ASSOCIATION_PRE_MUL;
	else if (name == "ModAdd")
		association_ = Modifier::ASSOCIATION_MOD_ADD;
	else if (name == "ModSub")
		association_ = Modifier::ASSOCIATION_MOD_SUB;
	else if (name == "PostPercent")
		association_ = Modifier::ASSOCIATION_POST_PERCENT;
	else if (name == "PostMul")
		association_ = Modifier::ASSOCIATION_POST_MUL;
	else if (name == "PostDiv")
		association_ = Modifier::ASSOCIATION_POST_DIV;
	else if (name == "PostAssignment")
		association_ = Modifier::ASSOCIATION_POST_ASSIGNMENT;
	else
		association_ = Modifier::ASSOCIATION_PRE_DIV;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addItemModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);

	auto modifier = std::make_shared<Modifier>(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->addItemModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addLocationGroupModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID groupID = getAttribute()->getItem()->getGroupID();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);

	auto modifier = std::make_shared<LocationGroupModifier>(attribute_->getAttributeID(), association_, attribute, groupID, isAssistance, isOffensive, character);
	item->addLocationGroupModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addLocationModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<Modifier>(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->addLocationModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addLocationRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<LocationRequiredSkillModifier>(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->addLocationRequiredSkillModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addOwnerRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<LocationRequiredSkillModifier>(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->addLocationRequiredSkillModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeItemModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<Modifier>(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->removeItemModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeLocationGroupModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID groupID = getAttribute()->getItem()->getGroupID();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<LocationGroupModifier>(attribute_->getAttributeID(), association_, attribute, groupID, isAssistance, isOffensive, character);
	item->removeLocationGroupModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeLocationModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<Modifier>(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->removeLocationModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeLocationRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<LocationRequiredSkillModifier>(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->removeLocationRequiredSkillModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeOwnerRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	std::shared_ptr<Attribute> attribute = environment.self->getAttribute(attributeID);
	Character* character = dynamic_cast<Character*>(environment.character);
	
	auto modifier = std::make_shared<LocationRequiredSkillModifier>(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->removeLocationRequiredSkillModifier(modifier);
	return true;
}


EffectByteCodeInterpreter::Argument::Argument()						: type_(TYPE_UNKNOWN) {}
EffectByteCodeInterpreter::Argument::Argument(int value, Type type) : type_(type),			intValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(bool value)			: type_(TYPE_BOOL),		intValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(float value)			: type_(TYPE_FLOAT),	floatValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(const char* value)	: type_(TYPE_STRING),	stringValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(const std::string& value)						: type_(TYPE_STRING),		stringValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(std::shared_ptr<ItemWrapper> const& value)			: type_(TYPE_ITEM),			itemValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(std::shared_ptr<AttributeWrapper> const& value)	: type_(TYPE_ATTRIBUTE),	attributeValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(std::shared_ptr<AssociationWrapper> const& value)	: type_(TYPE_ASSOCIATION),	associationValue_(value) {}

EffectByteCodeInterpreter::Argument::Type EffectByteCodeInterpreter::Argument::getType()
{
	return type_;
}

EffectByteCodeInterpreter::Argument::operator bool ()
{
	switch(type_)
	{
		case TYPE_BOOL:
		case TYPE_INT:
			return intValue_ != 0;
		case TYPE_FLOAT:
			return floatValue_ != 0;
		default:
			throw TypeCastException(std::to_string(type_));
	}
};

EffectByteCodeInterpreter::Argument::operator int ()
{
	switch(type_) {
		case TYPE_BOOL:
		case TYPE_INT:
		case TYPE_EXPRESSION:
			return intValue_;
		case TYPE_FLOAT:
			return static_cast<int>(floatValue_);
		default:
			throw TypeCastException(std::to_string(type_));
	}
};

EffectByteCodeInterpreter::Argument::operator float ()
{
	switch(type_)
	{
		case TYPE_BOOL:
		case TYPE_INT:
			return static_cast<float>(intValue_);
		case TYPE_FLOAT:
			return floatValue_;
		default:
			throw TypeCastException(std::to_string(type_));
	}
};

EffectByteCodeInterpreter::Argument::operator std::string ()
{
	if (type_ == TYPE_STRING)
		return stringValue_;
	else
		throw TypeCastException(std::to_string(type_));
};

EffectByteCodeInterpreter::Argument::operator std::shared_ptr<EffectByteCodeInterpreter::ItemWrapper> ()
{
	if (type_ == TYPE_ITEM)
		return itemValue_;
	else
		throw TypeCastException(std::to_string(type_));
};

EffectByteCodeInterpreter::Argument::operator std::shared_ptr<EffectByteCodeInterpreter::AttributeWrapper> ()
{
	if (type_ == TYPE_ATTRIBUTE)
		return attributeValue_;
	else
		throw TypeCastException(std::to_string(type_));
};

EffectByteCodeInterpreter::Argument::operator std::shared_ptr<EffectByteCodeInterpreter::AssociationWrapper> ()
{
	if (type_ == TYPE_ASSOCIATION)
		return associationValue_;
	else
		throw TypeCastException(std::to_string(type_));
};