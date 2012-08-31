#include "EffectByteCodeInterpreter.h"
#include "Engine.h"
#include "Compiler.h"
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

EffectByteCodeInterpreter::EffectByteCodeInterpreter(Engine* engine, const void* byteCode, size_t size, bool isAssistance, bool isOffensive) : engine_(engine), isAssistance_(isAssistance), isOffensive_(isOffensive)
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
	catch(eufe::EffectByteCodeInterpreter::Argument::TypeCastException& exc) {
		result = false;
	}
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
	catch(eufe::EffectByteCodeInterpreter::Argument::TypeCastException& exc) {
		result = false;
	}
	return result;
}

EffectInterpreter* EffectByteCodeInterpreter::clone() const
{
	return new EffectByteCodeInterpreter(*this);
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::execute(const Byte *expression)
{
	const Byte* ptr = expression;
	while (1) {
		Compiler::Opcode opcode = static_cast<Compiler::Opcode>(*ptr);
		ptr++;
		switch(opcode) {
			case Compiler::OPCODE_ARGUMENT :
			{
				Compiler::ArgumentType type = static_cast<Compiler::ArgumentType>(*ptr);
				ptr++;
				short length = *reinterpret_cast<const short*>(ptr);
				ptr += sizeof(short);
				
				if (type == Compiler::ARGUMENT_TYPE_INT)
					stack_.push_back(Argument(*reinterpret_cast<const int*>(ptr)));
				else if (type == Compiler::ARGUMENT_TYPE_STRING)
					stack_.push_back(Argument(reinterpret_cast<const char*>(ptr)));
				else if (type == Compiler::ARGUMENT_TYPE_EXPRESSION)
					stack_.push_back(Argument(*reinterpret_cast<const int*>(ptr), Argument::TYPE_EXPRESSION));
				
				ptr += length;
				break;
			}
			case Compiler::OPCODE_OPERAND:
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
	throw BadOperandException() << BadOperandExceptionInfo(0);
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addItemModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->addOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<ItemWrapper> item = arg1;
	TypeID attributeID = arg2;
	return boost::shared_ptr<AttributeWrapper>(new AttributeWrapper(item, attributeID));
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand13()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand14()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand15()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand16()
{
	return true;
}

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
	
	boost::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = environment_["Self"]->getAttribute(arg2)->getValue();
	attribute->dec(value);
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand19()
{
	return true;
}

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
	
	boost::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = arg2;
	attribute->dec(value);
	return true;
}

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

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand22()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand23()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand24()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	std::string key = arg1;
	if (environment_.find(key) != environment_.end())
		return boost::shared_ptr<ItemWrapper>(new ItemWrapper(environment_[key]));
	else
		return false;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand25()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand26()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand27()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand28()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand29()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	
	if (arg1.getType() == Argument::TYPE_STRING)
	{
		Engine::scoped_lock lock(*engine_);

		std::string typeName = arg1;
		sqlite3* db = engine_->getDb();
		std::stringstream sql;
		sql << "SELECT typeID FROM invTypes WHERE typeName = \"" << typeName << "\"";
		
		sqlite3_stmt* stmt = nullptr;
		sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr);
		int result = sqlite3_step(stmt);
		
		if (result == SQLITE_ROW)
		{
			TypeID typeID = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			return typeID;
		}
		else
		{
			sqlite3_finalize(stmt);
			throw UnknownTypeNameException() << UnknownTypeNameExceptionInfo(typeName);
		}
		
	}
	else
		return arg1;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand30()
{
	return true;
}

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
	boost::shared_ptr<AttributeWrapper> attribute = arg2;
	return boost::shared_ptr<AssociationWrapper>(new AssociationWrapper(attribute, associationName));
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand32()
{
	return true;
}

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
	
	if (environment_.find("Gang") == environment_.end())
		return false;
	
	Item* gang = environment_["Gang"];
	TypeID groupID = arg1;
	TypeID attributeID = arg2;
	boost::shared_ptr<ItemWrapper> item = boost::shared_ptr<ItemWrapper>(new ItemWrapper(gang));
	item->setGroupID(groupID);
	return boost::shared_ptr<AttributeWrapper> (new AttributeWrapper(item, attributeID));
}

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
	
	boost::shared_ptr<ItemWrapper> item = arg1;
	TypeID attributeID = arg2;
	return item->getItem()->getAttribute(attributeID)->getValue();
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand36()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	
	if (arg1.getType() != Argument::TYPE_ITEM)
		return false;
	
	boost::shared_ptr<ItemWrapper> item = arg1;
	return item->getItem()->getTypeID();
}

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
	
	boost::shared_ptr<ItemWrapper> item = arg1;
	TypeID groupID = static_cast<TypeID>(arg2);
	item->setGroupID(groupID);
	return item;
}

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

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand40()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	
	if (environment_.find("Gang") == environment_.end())
		return false;
	
	Item* gang = environment_["Gang"];
	TypeID attributeID = arg1;
	boost::shared_ptr<ItemWrapper> item = boost::shared_ptr<ItemWrapper>(new ItemWrapper(gang));
	return boost::shared_ptr<AttributeWrapper> (new AttributeWrapper(item, attributeID));
}

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
	
	boost::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = environment_["Self"]->getAttribute(arg2)->getValue();
	attribute->inc(value);
	return true;
}

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
	
	boost::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = arg2;
	attribute->inc(value);
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand44()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand45()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand46()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand47()
{
	return true;
}

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
	
	boost::shared_ptr<ItemWrapper> item = arg1;
	TypeID groupID = arg2;
	item->setGroupID(groupID);
	return item;
}

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
	
	boost::shared_ptr<ItemWrapper> item = arg1;
	TypeID skillID = arg2;
	item->setRequiredSkillID(skillID);
	return item;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand50()
{
	return true;
}

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

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand53()
{
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeItemModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationGroupModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeLocationRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<AssociationWrapper> association = arg1;
	TypeID attributeID = arg2;
	association->removeOwnerRequiredSkillModifier(environment_, attributeID, isAssistance_, isOffensive_);
	return true;
}

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
	
	boost::shared_ptr<ItemWrapper> item = arg1;
	TypeID skillID = arg2;
	return item->getItem()->requireSkill(skillID);
}

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
	
	if (environment_.find("Gang") == environment_.end())
		return false;
	
	Item* gang = environment_["Gang"];
	TypeID skillID = arg1;
	TypeID attributeID = arg2;
	boost::shared_ptr<ItemWrapper> item = boost::shared_ptr<ItemWrapper>(new ItemWrapper(gang));
	item->setRequiredSkillID(skillID);
	return boost::shared_ptr<AttributeWrapper> (new AttributeWrapper(item, attributeID));
	
}

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
	
	boost::shared_ptr<AttributeWrapper> attribute = arg1;
	float value = arg2;
	attribute->setValue(value);
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand66()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand67()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return true;
}

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

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand69()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand70()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand71()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand72()
{
	return true;
}

EffectByteCodeInterpreter::Argument EffectByteCodeInterpreter::operand73()
{
	Argument arg1 = *stack_.rbegin();
	stack_.pop_back();
	
	if (arg1.getType() == Argument::TYPE_EXPRESSION)
		arg1 = execute(byteCode_ + static_cast<int>(arg1));
	return arg1;
}

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

EffectByteCodeInterpreter::AssociationWrapper::AssociationWrapper(boost::shared_ptr<AttributeWrapper>& attribute, const std::string& name) : attribute_(attribute)
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

	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);

	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);

	Modifier* modifier = new Modifier(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->addItemModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addLocationGroupModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID groupID = getAttribute()->getItem()->getGroupID();

	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);

	Modifier* modifier = new LocationGroupModifier(attribute_->getAttributeID(), association_, attribute, groupID, isAssistance, isOffensive, character);
	item->addLocationGroupModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addLocationModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new Modifier(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->addLocationModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addLocationRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new LocationRequiredSkillModifier(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->addLocationRequiredSkillModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::addOwnerRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	//	Attribute* attribute = item->getAttribute(attributeID).get();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new LocationRequiredSkillModifier(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->addLocationRequiredSkillModifier(modifier);
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeItemModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new Modifier(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->removeItemModifier(modifier);
	delete modifier;
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeLocationGroupModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID groupID = getAttribute()->getItem()->getGroupID();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new LocationGroupModifier(attribute_->getAttributeID(), association_, attribute, groupID, isAssistance, isOffensive, character);
	item->removeLocationGroupModifier(modifier);
	delete modifier;
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeLocationModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new Modifier(attribute_->getAttributeID(), association_, attribute, isAssistance, isOffensive, character);
	item->removeLocationModifier(modifier);
	delete modifier;
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeLocationRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new LocationRequiredSkillModifier(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->removeLocationRequiredSkillModifier(modifier);
	delete modifier;
	return true;
}

bool EffectByteCodeInterpreter::AssociationWrapper::removeOwnerRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive)
{
	Item* item = attribute_->getItem()->getItem();
	TypeID skillID = getAttribute()->getItem()->getRequiredSkillID();
	auto Self = environment.find("Self");
	auto Char = environment.find("Char");
	auto end = environment.end();
	Attribute* attribute = Self->second->getAttribute(attributeID);
	
	Character* character = nullptr;
	if (Char != end)
		character = dynamic_cast<Character*>(Char->second);
	
	Modifier* modifier = new LocationRequiredSkillModifier(attribute_->getAttributeID(), association_, attribute, skillID, isAssistance, isOffensive, character);
	item->removeLocationRequiredSkillModifier(modifier);
	delete modifier;
	return true;
}


EffectByteCodeInterpreter::Argument::Argument()						: type_(TYPE_UNKNOWN) {}
EffectByteCodeInterpreter::Argument::Argument(int value, Type type) : type_(type),			intValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(bool value)			: type_(TYPE_BOOL),		intValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(float value)			: type_(TYPE_FLOAT),	floatValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(const char* value)	: type_(TYPE_STRING),	stringValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(const std::string& value)						: type_(TYPE_STRING),		stringValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(boost::shared_ptr<ItemWrapper> value)			: type_(TYPE_ITEM),			itemValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(boost::shared_ptr<AttributeWrapper> value)	: type_(TYPE_ATTRIBUTE),	attributeValue_(value) {}
EffectByteCodeInterpreter::Argument::Argument(boost::shared_ptr<AssociationWrapper> value)	: type_(TYPE_ASSOCIATION),	associationValue_(value) {}

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
			throw TypeCastException() << TypeCastExceptionInfo(type_, TYPE_BOOL);
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
			throw TypeCastException() << TypeCastExceptionInfo(type_, TYPE_INT);
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
			throw TypeCastException() << TypeCastExceptionInfo(type_, TYPE_FLOAT);
	}
};

EffectByteCodeInterpreter::Argument::operator std::string ()
{
	if (type_ == TYPE_STRING)
		return stringValue_;
	else
		throw TypeCastException() << TypeCastExceptionInfo(type_, TYPE_STRING);
};

EffectByteCodeInterpreter::Argument::operator boost::shared_ptr<EffectByteCodeInterpreter::ItemWrapper> ()
{
	if (type_ == TYPE_ITEM)
		return itemValue_;
	else
		throw TypeCastException() << TypeCastExceptionInfo(type_, TYPE_ITEM);
};

EffectByteCodeInterpreter::Argument::operator boost::shared_ptr<EffectByteCodeInterpreter::AttributeWrapper> ()
{
	if (type_ == TYPE_ATTRIBUTE)
		return attributeValue_;
	else
		throw TypeCastException() << TypeCastExceptionInfo(type_, TYPE_ATTRIBUTE);
};

EffectByteCodeInterpreter::Argument::operator boost::shared_ptr<EffectByteCodeInterpreter::AssociationWrapper> ()
{
	if (type_ == TYPE_ASSOCIATION)
		return associationValue_;
	else
		throw TypeCastException() << TypeCastExceptionInfo(type_, TYPE_ASSOCIATION);
};