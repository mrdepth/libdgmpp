//
//  MetaInfo.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 10.11.2017.
//

#pragma once
#include "Utility.hpp"
#include <array>

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
			virtual dgmpp2::slice<const Modifier* const*> modifiers() const = 0;

			constexpr Effect(EffectID effectID, Category category, bool isAssistance, bool isOffensive)
			: effectID(effectID), category(category), isAssistance(isAssistance), isOffensive(isOffensive) {};

			Effect (const Effect& other) = delete;
			Effect& operator= (const Effect& other) = delete;
			Effect& operator= (Effect&& other) = delete;
			~Effect() = default;
		protected:
			Effect(Effect&& other) = default;
		};
		
		template<typename Modifiers>
		struct _Effect : public Effect {
			
			constexpr _Effect(EffectID effectID, Category category, bool isAssistance, bool isOffensive, const Modifiers& modifiers)
			: Effect(effectID, category, isAssistance, isOffensive), modifiers_(modifiers) {};
			
			
			virtual dgmpp2::slice<const Modifier* const*> modifiers() const override {
				return { modifiers_.data(), modifiers_.data() + modifiers_.size() };
			}
		private:
			Modifiers modifiers_;
		};

		struct WarfareBuff {
			WarfareBuffID warfareBuffID;
			AttributeID modifyingAttributeID;
			constexpr WarfareBuff(WarfareBuffID warfareBuffID, AttributeID modifyingAttributeID)
			: warfareBuffID(warfareBuffID), modifyingAttributeID(modifyingAttributeID) {}
			virtual dgmpp2::slice<const Modifier* const*> modifiers() const = 0;
			
			WarfareBuff (const WarfareBuff& other) = delete;
			WarfareBuff (WarfareBuff&& other) = delete;
			WarfareBuff& operator= (const WarfareBuff& other) = delete;
			WarfareBuff& operator= (WarfareBuff&& other) = delete;
			~WarfareBuff() = default;
		};
		
		template<typename Modifiers>
		struct _WarfareBuff : public WarfareBuff {
			constexpr _WarfareBuff(WarfareBuffID warfareBuffID, AttributeID modifyingAttributeID, const Modifiers& modifiers)
			: WarfareBuff(warfareBuffID, modifyingAttributeID), modifiers_(modifiers) {}
			
			virtual dgmpp2::slice<const Modifier* const*> modifiers() const override {
				return { modifiers_.data(), modifiers_.data() + modifiers_.size() };
			}

		private:
			Modifiers modifiers_;
		};
		
		struct Type {
			TypeID		typeID;
			GroupID		groupID;
			CategoryID	categoryID;
			
			virtual dgmpp2::slice<const std::pair<const Attribute*, Float>*> attributes() const = 0;
			virtual dgmpp2::slice<const Effect* const*> effects() const = 0;
			virtual dgmpp2::slice<const TypeID*> requiredSkills() const = 0;

			constexpr Type(TypeID typeID, GroupID groupID, CategoryID categoryID)
			: typeID(typeID), groupID(groupID), categoryID(categoryID) {}
			Type (const Type& other) = delete;
			Type& operator= (const Type& other) = delete;
			Type& operator= (Type&& other) = delete;
			~Type() = default;
			
			bool requireSkill (TypeID skillID) const {
				auto requiredSkills = this->requiredSkills();
				return std::find(requiredSkills.begin(), requiredSkills.end(), skillID) != requiredSkills.end();
			}
		protected:
			Type (Type&& other) = default;
		};
		
		
		template <typename Attributes, typename Effects, typename RequiredSkills>
		struct _Type : public Type {
			
			constexpr _Type(TypeID typeID, GroupID groupID, CategoryID categoryID, const Attributes& attributes, const Effects& effects, const RequiredSkills& requiredSkills)
			: Type(typeID, groupID, categoryID), attributes_(attributes), effects_(effects), requiredSkills_(requiredSkills) {}
			
			virtual dgmpp2::slice<const std::pair<const Attribute*, Float>*> attributes() const override {
				return { attributes_.data(), attributes_.data() + attributes_.size() };
			}
			
			virtual dgmpp2::slice<const Effect* const*> effects() const override {
				return { effects_.data(), effects_.data() + effects_.size() };
			}
			
			virtual dgmpp2::slice<const TypeID*> requiredSkills() const override {
				return { requiredSkills_.data(), requiredSkills_.data() + requiredSkills_.size() };
			}
			
			
		private:
			Attributes attributes_;
			Effects effects_;
			RequiredSkills requiredSkills_;
		};
		

		struct Commodity {
			enum class Tier {
				unknown = -1,
				raw,
				tier1,
				tier2,
				tier3,
				tier4
			};
			
			TypeID typeID;
			Tier tier;
			CubicMeter volume;
			
			Commodity (const Commodity& other) = delete;
			Commodity (Commodity&& other) = delete;
			Commodity& operator= (const Commodity& other) = delete;
			Commodity& operator= (Commodity&& other) = delete;
			~Commodity() = default;
		};
		
		struct Facility {
			TypeID typeID;
			GroupID groupID;
			CubicMeter capacity;
		};
		
		struct Schematic {
			SchematicID schematicID;
			std::chrono::seconds cycleTime;
			std::pair<const Commodity*, size_t> output;
			virtual dgmpp2::slice<const std::pair<const Commodity*, size_t>*> inputs() const = 0;
			
			constexpr Schematic(SchematicID schematicID, std::chrono::seconds cycleTime, std::pair<const Commodity*, size_t> output)
			: schematicID(schematicID), cycleTime(cycleTime), output(output) {}
			
			Schematic (const Schematic& other) = delete;
			Schematic (Schematic&& other) = delete;
			Schematic& operator= (const Schematic& other) = delete;
			Schematic& operator= (Schematic&& other) = delete;
			~Schematic() = default;
		};
		
		template <typename Inputs>
		struct _Schematic : public Schematic {
			
			constexpr _Schematic(SchematicID schematicID, std::chrono::seconds cycleTime, std::pair<const Commodity*, size_t> output, const Inputs& inputs)
			: Schematic(schematicID, cycleTime, output), inputs_(inputs) {}

			virtual dgmpp2::slice<const std::pair<const Commodity*, size_t>*> inputs() const override {
				return { inputs_.data(), inputs_.data() + inputs_.size() };
			}
			
		private:
			Inputs inputs_;
		};
		
		template<typename Modifiers>
		constexpr _Effect<Modifiers> MakeEffect(EffectID effectID, Effect::Category category, bool isAssistance, bool isOffensive, const Modifiers& modifiers) {
			return { effectID, category, isAssistance, isOffensive, modifiers };
		}
		
		template <typename Attributes, typename Effects, typename RequiredSkills>
		constexpr _Type<Attributes, Effects, RequiredSkills> MakeType(TypeID typeID, GroupID groupID, CategoryID categoryID,
																	  const Attributes& attributes,
																	  const Effects& effects,
																	  const RequiredSkills& requiredSkills) {
			return { typeID, groupID, categoryID, attributes, effects, requiredSkills };
		}

		template <typename Modifiers>
		constexpr _WarfareBuff<Modifiers> MakeBuff(WarfareBuffID warfareBuffID, AttributeID modifyingAttributeID, const Modifiers& modifiers) {
			return { warfareBuffID, modifyingAttributeID, modifiers };
		}

		template <typename Inputs>
		constexpr _Schematic<Inputs> MakeSchematic(SchematicID schematicID, std::chrono::seconds cycleTime, std::pair<const Commodity*, size_t> output, const Inputs& inputs) {
			return { schematicID, cycleTime, output, inputs };
		}

		template<typename T, typename... Args>
		struct arr {
			constexpr arr (T (&a)[sizeof...(Args)]) : array(a) {}
			T array[sizeof...(Args)];
		};

		template <typename T, typename... Args>
		constexpr std::array<T, sizeof...(Args)> _array(Args... args) {
			return { args... };
		}

		template <typename... Args>
		constexpr auto _attributes(Args... args) {
			return _array<std::pair<const MetaInfo::Attribute*, Float>, Args...>(args...);
		}

		template <typename... Args>
		constexpr auto _effects(Args... args) {
			return _array<const MetaInfo::Effect*>(args...);
		}

		template <typename... Args>
		constexpr auto _modifiers(Args... args) {
			return _array<const MetaInfo::Modifier*>(args...);
		}

		template <typename... Args>
		constexpr auto _buffModifiers(Args... args) {
			return _array<MetaInfo::Modifier>(args...);
		}

		template <typename... Args>
		constexpr auto _typeIDs(Args... args) {
			return _array<TypeID>(args...);
		}

		constexpr std::pair<const Attribute*, Float> _A (const Attribute* attribute, Float value) {
			return {attribute, value};
		}
		
		template <typename... Args>
		constexpr auto _inputs(Args... args) {
			return _array<std::pair<const Commodity*, size_t>, Args...>(args...);
		}

		constexpr std::pair<const Commodity*, size_t> _C (const Commodity* commodity, size_t quantity) {
			return {commodity, quantity};
		}

	}
}
