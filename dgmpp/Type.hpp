//
//  Type.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 30.10.2017.
//

#pragma once
#include "types.h"
#include "Effect.h"
#include "Effect.h"
//#include <utility>
#include <mutex>

#include <sqlite3.h>

#include "Attribute.h"
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace dgmpp2 {
	
	class Type {
	public:
		struct MetaInfo;

		Type(const Type& other) = delete;
		Type(Type&& other) = delete;
		Type& operator=(const Type& other) = delete;
		Type& operator=(Type&& other) = delete;

		const MetaInfo& metaInfo() const {return metaInfo_;}
		Type* parent() const {return parent_;}
		
		bool hasAttribute(AttributeID attributeID);
		Attribute::Proxy operator[](AttributeID attributeID);
		
	protected:
		Type(TypeID typeID);
		
		void add(std::unique_ptr<Type> child);
		void remove(Type* child);
		
		friend class Modifier;
		virtual Type* operator[](Modifier::MetaInfo::Domain domain);
		
		std::list<const Modifier*> itemModifiers(const Attribute& attribute) const;
		std::list<const Modifier*> locationModifiers(const Attribute& attribute) const;
		std::list<const Modifier*> locationGroupModifiers(const Attribute& attribute, const Type& type) const;
		std::list<const Modifier*> locationRequiredSkillModifiers(const Attribute& attribute, const Type& type) const;
		
		virtual std::list<const Modifier*> modifiers(const Attribute& attribute) const;
		virtual std::list<const Modifier*> modifiersMatchingType(const Attribute& attribute, const Type& type) const;
		
		void addEffects(Effect::MetaInfo::Category category);
		void removeEffects(Effect::MetaInfo::Category category);
		
	private:
		friend class AttributeProxy;
		using AttributesMap = std::unordered_map<AttributeID, std::unique_ptr<Attribute>>;
		
		const MetaInfo& metaInfo_;
		Type* parent_ = nullptr;
		AttributesMap attributes_;
		std::vector<std::unique_ptr<Effect>> effects_;
		std::vector<std::unique_ptr<Type>> children_;

		std::vector<const Modifier*> itemModifiers_;
		std::vector<const Modifier*> locationModifiers_;
		std::vector<const Modifier*> locationGroupModifiers_;
		std::vector<std::pair<TypeID, const Modifier*>> locationRequiredSkillModifiers_;

		Type(const MetaInfo& metaInfo);
		void parent(Type* parent) {parent_ = parent;}
		
		void addModifier(const Modifier* modifier);
		void removeModifier(const Modifier* modifier);
	};
	
	struct Type::MetaInfo {
		TypeID typeID;
		GroupID groupID;
		CategoryID categoryID;
		std::initializer_list<std::pair<const Attribute::MetaInfo&, Float>> attributes;
		std::initializer_list<ref<const Effect::MetaInfo>> effects;
		std::initializer_list<const TypeID> requiredSkills;

		MetaInfo(const MetaInfo& other) = delete;
		MetaInfo(MetaInfo&& other) = delete;
		MetaInfo& operator=(const MetaInfo& other) = delete;
		MetaInfo& operator=(MetaInfo&& other) = delete;
		~MetaInfo() = default;
		
		bool requireSkill(TypeID skillID) const {
			return std::find(requiredSkills.begin(), requiredSkills.end(), skillID) != requiredSkills.end();
		}
	};
	
}
