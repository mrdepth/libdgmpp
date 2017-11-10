//
//  MetaInfo.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 10.11.2017.
//

#pragma once
#include "types.h"

namespace dgmpp2 {
	namespace MetaInfo {
		
		struct Attribute {
			AttributeID	attributeID;
			AttributeID	maxAttributeID;
			Float		defaultValue;
			bool		isStackable;
			bool		highIsGood;
			
			Attribute (const Attribute& other) = delete;
			Attribute (Attribute&& other) = delete;
			Attribute& operator= (const Attribute& other) = delete;
			Attribute& operator= (Attribute&& other) = delete;
			~Attribute() = default;
			
		};
		
		struct Modifier {
			enum class ModifierType {
				item,
				location,
				locationGroup,
				locationRequiredSkill,
				ownerRequiredSkill,
				locationRequiredDomainSkill,
			};
			
			enum class Association {
				preAssignment,
				modAdd,
				modSub,
				preDiv,
				preMul,
				postPercent,
				postDiv,
				postMul,
				postAssignment,
				skillTime,
				addRate,
				subRate
			};
			
			enum class Domain {
				self,
				character,
				ship,
				gang,
				area,
				target,
				other,
				structure
			};
			
			union Requirement {
				TypeID	typeID;
				GroupID	groupID;
				Domain	domain;
				constexpr Requirement (TypeID typeID)	: typeID (typeID) {}
				constexpr Requirement (GroupID groupID)	: groupID (groupID) {}
				constexpr Requirement (Domain domain)	: domain (domain) {}
			};

			ModifierType	type;
			Association		association;
			Domain			domain;
			
			AttributeID		modifiedAttributeID;
			AttributeID		modifyingAttributeID;
			
			Requirement		require;
			
			constexpr Modifier (ModifierType type,
								Association association,
								Domain domain,
								AttributeID modifiedAttributeID,
								AttributeID modifyingAttributeID)
			: type(type), association(association), domain(domain), modifiedAttributeID(modifiedAttributeID), modifyingAttributeID(modifyingAttributeID), require(TypeID::none) {}
			
			constexpr Modifier (ModifierType type,
								Association association,
								Domain domain,
								AttributeID modifiedAttributeID,
								AttributeID modifyingAttributeID,
								TypeID require)
			: type(type), association(association), domain(domain), modifiedAttributeID(modifiedAttributeID), modifyingAttributeID(modifyingAttributeID), require(require) {}
			
			constexpr Modifier (ModifierType type,
								Association association,
								Domain domain,
								AttributeID modifiedAttributeID,
								AttributeID modifyingAttributeID,
								GroupID require)
			: type(type), association(association), domain(domain), modifiedAttributeID(modifiedAttributeID), modifyingAttributeID(modifyingAttributeID), require(require) {}
			
			constexpr Modifier (ModifierType type,
								Association association,
								Domain domain,
								AttributeID modifiedAttributeID,
								AttributeID modifyingAttributeID,
								Domain require)
			: type(type), association(association), domain(domain), modifiedAttributeID(modifiedAttributeID), modifyingAttributeID(modifyingAttributeID), require(require) {}
			
			Modifier (const Modifier& other) = delete;
			Modifier (Modifier&& other) = delete;
			Modifier& operator= (const Modifier& other) = delete;
			Modifier& operator= (Modifier&& other) = delete;
			~Modifier() = default;
		};
		
		struct Effect {
			enum class Category {
				generic,
				active,
				target,
				passive,
				overloaded,
				dungeon,
				system
			};
			
			EffectID	effectID;
			Category	category;
			bool		isAssistance;
			bool		isOffensive;
			std::initializer_list<ref<const Modifier>> modifiers;
			
			Effect (const Effect& other) = delete;
			Effect (Effect&& other) = delete;
			Effect& operator= (const Effect& other) = delete;
			Effect& operator= (Effect&& other) = delete;
			~Effect() = default;
			
		};
		
		struct Type {
			TypeID		typeID;
			GroupID		groupID;
			CategoryID	categoryID;
			
			std::initializer_list<std::pair<const Attribute&, Float>>	attributes;
			std::initializer_list<ref<const Effect>>					effects;
			std::initializer_list<const TypeID>							requiredSkills;
			
			Type (const Type& other) = delete;
			Type (Type&& other) = delete;
			Type& operator= (const Type& other) = delete;
			Type& operator= (Type&& other) = delete;
			~Type() = default;
			
			bool requireSkill (TypeID skillID) const {
				return std::find(requiredSkills.begin(), requiredSkills.end(), skillID) != requiredSkills.end();
			}
		};
	}
}
