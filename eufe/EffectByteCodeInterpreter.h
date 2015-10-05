#pragma once
#include "EffectInterpreter.h"
#include "Modifier.h"
//#include <boost/exception/all.hpp>
#include <stdexcept>
#include <vector>

namespace eufe {
	
	class EffectByteCodeInterpreter : public EffectInterpreter
	{
	public:
		
		class ItemWrapper
		{
		public:
			ItemWrapper(std::shared_ptr<Item> item) : item_(item) {}
			std::shared_ptr<Item> getItem() const {return item_.lock();}
			TypeID getGroupID() const {return groupID_;}
			TypeID getRequiredSkillID() const {return requiredSkillID_;}
			void setGroupID(TypeID groupID) {groupID_ = groupID;}
			void setRequiredSkillID(TypeID requiredSkillID) {requiredSkillID_ = requiredSkillID;}
		private:
			std::weak_ptr<Item> item_;
			TypeID groupID_;
			TypeID requiredSkillID_;
		};
		
		class AttributeWrapper
		{
		public:
			AttributeWrapper(std::shared_ptr<ItemWrapper>& item, TypeID attributeID) : item_(item), attributeID_(attributeID) {}
			float getValue();
			void setValue(float value);
			void inc(float value);
			void dec(float value);
			std::shared_ptr<ItemWrapper> getItem() {return item_;}
			TypeID getAttributeID() const {return attributeID_;}
		private:
			std::shared_ptr<ItemWrapper> item_;
			TypeID attributeID_;
		};
		
		class AssociationWrapper
		{
		public:
			AssociationWrapper(std::shared_ptr<AttributeWrapper>& attribute, const std::string& name);
			std::shared_ptr<AttributeWrapper> getAttribute() {return attribute_;}
			Modifier::Association getAssociation() {return association_;}
			
			bool addItemModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool addLocationGroupModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool addLocationModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool addLocationRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool addOwnerRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool removeItemModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool removeLocationGroupModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool removeLocationModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool removeLocationRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			bool removeOwnerRequiredSkillModifier(const Environment& environment, TypeID attributeID, bool isAssistance, bool isOffensive);
			
		private:
			std::shared_ptr<AttributeWrapper> attribute_;
			Modifier::Association association_;
		};
		
		class Argument {
		public:
			enum Type{
				TYPE_UNKNOWN,
				TYPE_BOOL,			//argumentCategoryID = 4
				TYPE_INT,			//argumentCategoryID = 4
				TYPE_FLOAT,			//argumentCategoryID = 4
				TYPE_STRING,		//argumentCategoryID = 1, 4
				TYPE_EXPRESSION,	//argumentCategoryID = 4
				TYPE_ATTRIBUTE,		//argumentCategoryID = 3
				TYPE_ITEM,			//argumentCategoryID = 6
				TYPE_ASSOCIATION,	//argumentCategoryID = 5
				TYPE_ID = TYPE_INT	//argumentCategoryID = 2, 8, 9
			};
			
			//typedef boost::error_info<struct TypeCastExceptionFromTypeInfoTag, Type> TypeCastExceptionFromTypeInfo;
			//typedef boost::error_info<struct TypeCastExceptionToTypeInfoTag, Type> TypeCastExceptionToTypeInfo;
			//typedef boost::tuple<TypeCastExceptionFromTypeInfo, TypeCastExceptionToTypeInfo> TypeCastExceptionInfo;
			
			//struct TypeCastException : virtual boost::exception {};
            typedef std::runtime_error TypeCastException;
			
			Argument();
			Argument(int value, Type type = TYPE_INT);
			Argument(bool value);
			Argument(float value);
			Argument(const char* value);
			Argument(const std::string& value);
			Argument(std::shared_ptr<ItemWrapper> value);
			Argument(std::shared_ptr<AttributeWrapper> value);
			Argument(std::shared_ptr<AssociationWrapper> value);
			
			Type getType();
			
			operator bool ();
			operator int ();
			operator float ();
			operator std::string ();
			operator std::shared_ptr<ItemWrapper> ();
			operator std::shared_ptr<AttributeWrapper> ();
			operator std::shared_ptr<AssociationWrapper> ();
			
			
		private:
			union
			{
				int intValue_;
				float floatValue_;
			};
			std::string stringValue_;
			std::shared_ptr<ItemWrapper> itemValue_;
			std::shared_ptr<AttributeWrapper> attributeValue_;
			std::shared_ptr<AssociationWrapper> associationValue_;
			Type type_;
		};
		
		//typedef boost::error_info<struct BadOperandExceptionInfoTag, int> BadOperandExceptionInfo;
		//struct BadOperandException : virtual boost::exception {};
		
		//typedef boost::error_info<struct UnknownTypeNameExceptionInfoTag, std::string> UnknownTypeNameExceptionInfo;
		//struct UnknownTypeNameException : virtual boost::exception {};
        typedef std::invalid_argument BadOperandException;
        typedef std::invalid_argument UnknownTypeNameException;

		EffectByteCodeInterpreter(std::shared_ptr<Engine> engine, const void* byteCode, size_t size, bool isAssistance, bool isOffensive);
		EffectByteCodeInterpreter(const EffectByteCodeInterpreter& from);
		virtual ~EffectByteCodeInterpreter();
		
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);

	private:
		typedef Argument (EffectByteCodeInterpreter::*OperandPtr)();
		typedef std::vector<EffectByteCodeInterpreter::OperandPtr> OperandsVector;
		
		std::weak_ptr<Engine> engine_;
		
		bool isAssistance_;
		bool isOffensive_;
		Byte* preExpression_;
		Byte* postExpression_;
		
		Byte* byteCode_;
		Byte* endPtr_;
		
		std::list<Argument> stack_;
		Environment environment_;
		
		Argument execute(const Byte *expression);
		
		static OperandsVector operands;
		static OperandsVector InitOperands();
		
		Argument operand0();
		Argument operand1();
		Argument operand2();
		Argument operand3();
		Argument operand4();
		Argument operand5();
		Argument operand6();
		Argument operand7();
		Argument operand8();
		Argument operand9();
		Argument operand10();
		Argument operand11();
		Argument operand12();
		Argument operand13();
		Argument operand14();
		Argument operand15();
		Argument operand16();
		Argument operand17();
		Argument operand18();
		Argument operand19();
		Argument operand20();
		Argument operand21();
		Argument operand22();
		Argument operand23();
		Argument operand24();
		Argument operand25();
		Argument operand26();
		Argument operand27();
		Argument operand28();
		Argument operand29();
		Argument operand30();
		Argument operand31();
		Argument operand32();
		Argument operand33();
		Argument operand34();
		Argument operand35();
		Argument operand36();
		Argument operand37();
		Argument operand38();
		Argument operand39();
		Argument operand40();
		Argument operand41();
		Argument operand42();
		Argument operand43();
		Argument operand44();
		Argument operand45();
		Argument operand46();
		Argument operand47();
		Argument operand48();
		Argument operand49();
		Argument operand50();
		Argument operand51();
		Argument operand52();
		Argument operand53();
		Argument operand54();
		Argument operand55();
		Argument operand56();
		Argument operand57();
		Argument operand58();
		Argument operand59();
		Argument operand60();
		Argument operand61();
		Argument operand62();
		Argument operand63();
		Argument operand64();
		Argument operand65();
		Argument operand66();
		Argument operand67();
		Argument operand68();
		Argument operand69();
		Argument operand70();
		Argument operand71();
		Argument operand72();
		Argument operand73();
		Argument operand74();
	};
	
}