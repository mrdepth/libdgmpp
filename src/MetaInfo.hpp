//
//  MetaInfo.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 10.11.2017.
//

#pragma once
#include "Utility.hpp"
#include <array>

namespace dgmpp {
	
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
			
			Modifier (const Modifier& other) = default;
			Modifier (Modifier&& other) = delete;
			Modifier& operator= (const Modifier& other) = delete;
			Modifier& operator= (Modifier&& other) = delete;
			~Modifier() = default;
		};
		
		struct Effect {
			enum class Category {
				passive,
				activation,
				target,
				online,
				overload,
				dungeon,
				system
			};
			
			EffectID	effectID;
			Category	category;
			bool		isOffensive;
			bool		isAssistance;
			virtual slice<const Modifier* const*> modifiers() const noexcept = 0;

			constexpr Effect(EffectID effectID, Category category, bool isOffensive, bool isAssistance)
			: effectID(effectID), category(category), isOffensive(isOffensive), isAssistance(isAssistance) {};

			Effect (const Effect& other) = delete;
			Effect& operator= (const Effect& other) = delete;
			Effect& operator= (Effect&& other) = delete;
			~Effect() = default;
		protected:
			Effect(Effect&& other) = default;
		};
		
		template<typename Modifiers>
		struct _Effect : public Effect {
			
			constexpr _Effect(EffectID effectID, Category category, bool isOffensive, bool isAssistance, const Modifiers& modifiers)
			: Effect(effectID, category, isOffensive, isAssistance), modifiers_(modifiers) {};
			
			
			virtual slice<const Modifier* const*> modifiers() const noexcept override {
				return { modifiers_.data(), modifiers_.data() + modifiers_.size() };
			}
		private:
			Modifiers modifiers_;
		};

		struct WarfareBuff {
			WarfareBuffID warfareBuffID;
			constexpr WarfareBuff(WarfareBuffID warfareBuffID) : warfareBuffID(warfareBuffID) {}
			virtual slice<const Modifier* const*> modifiers() const noexcept = 0;
			
			WarfareBuff (const WarfareBuff& other) = delete;
			WarfareBuff (WarfareBuff&& other) = delete;
			WarfareBuff& operator= (const WarfareBuff& other) = delete;
			WarfareBuff& operator= (WarfareBuff&& other) = delete;
			~WarfareBuff() = default;
		};
		
		template<typename Modifiers>
		struct _WarfareBuff : public WarfareBuff {
			constexpr _WarfareBuff(WarfareBuffID warfareBuffID, const Modifiers& modifiers)
			: WarfareBuff(warfareBuffID), modifiers_(modifiers) {}
			
			virtual slice<const Modifier* const*> modifiers() const noexcept override {
				return { modifiers_.data(), modifiers_.data() + modifiers_.size() };
			}

		private:
			Modifiers modifiers_;
		};
		
		struct Type {
			enum class MetaGroup {
				none,
				techI,
				techII,
				storyline,
				faction,
				officer,
				deadspace,
				frigates,
				eliteFrigates,
				commanderFrigates,
				destroyer,
				cruiser,
				eliteCruiser,
				commanderCruiser,
				techIII
			};
			
			TypeID		typeID;
			GroupID		groupID;
			CategoryID	categoryID;
			MetaGroup 	metaGroup;
			MetaLevel	metaLevel;
			
			virtual slice<const std::pair<const Attribute*, Float>*> attributes() const noexcept = 0;
			virtual slice<const Effect* const*> effects() const noexcept = 0;
			virtual slice<const TypeID*> requiredSkills() const noexcept = 0;

			constexpr Type(TypeID typeID, GroupID groupID, CategoryID categoryID, MetaGroup metaGroup, MetaLevel metaLevel)
			: typeID(typeID), groupID(groupID), categoryID(categoryID), metaGroup(metaGroup), metaLevel(metaLevel)  {}
			Type (const Type& other) = delete;
			Type& operator= (const Type& other) = delete;
			Type& operator= (Type&& other) = delete;
			~Type() = default;
			
			bool requireSkill (TypeID skillID) const noexcept {
				auto requiredSkills = this->requiredSkills();
				return std::find(requiredSkills.begin(), requiredSkills.end(), skillID) != requiredSkills.end();
			}
		protected:
			Type (Type&& other) = default;
		};
		
		
		template <typename Attributes, typename Effects, typename RequiredSkills>
		struct _Type : public Type {
			
			constexpr _Type(TypeID typeID, GroupID groupID, CategoryID categoryID, MetaGroup metaGroup, MetaLevel metaLevel, const Attributes& attributes, const Effects& effects, const RequiredSkills& requiredSkills)
			: Type(typeID, groupID, categoryID, metaGroup, metaLevel), attributes_(attributes), effects_(effects), requiredSkills_(requiredSkills) {}
			
			virtual slice<const std::pair<const Attribute*, Float>*> attributes() const noexcept override {
				return { attributes_.data(), attributes_.data() + attributes_.size() };
			}
			
			virtual slice<const Effect* const*> effects() const noexcept override {
				return { effects_.data(), effects_.data() + effects_.size() };
			}
			
			virtual slice<const TypeID*> requiredSkills() const noexcept override {
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
			std::pair<const Commodity*, std::size_t> output;
			virtual slice<const std::pair<const Commodity*, std::size_t>*> inputs() const noexcept = 0;
			
			constexpr Schematic(SchematicID schematicID, std::chrono::seconds cycleTime, std::pair<const Commodity*, std::size_t> output)
			: schematicID(schematicID), cycleTime(cycleTime), output(output) {}
			
			Schematic (const Schematic& other) = delete;
			Schematic (Schematic&& other) = delete;
			Schematic& operator= (const Schematic& other) = delete;
			Schematic& operator= (Schematic&& other) = delete;
			~Schematic() = default;
		};
		
		template <typename Inputs>
		struct _Schematic : public Schematic {
			
			constexpr _Schematic(SchematicID schematicID, std::chrono::seconds cycleTime, std::pair<const Commodity*, std::size_t> output, const Inputs& inputs)
			: Schematic(schematicID, cycleTime, output), inputs_(inputs) {}

			virtual slice<const std::pair<const Commodity*, std::size_t>*> inputs() const noexcept override {
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
		constexpr _Type<Attributes, Effects, RequiredSkills> MakeType(TypeID typeID, GroupID groupID, CategoryID categoryID, Type::MetaGroup metaGroup, MetaLevel metaLevel,
																	  const Attributes& attributes,
																	  const Effects& effects,
																	  const RequiredSkills& requiredSkills) {
			return { typeID, groupID, categoryID, metaGroup, metaLevel, attributes, effects, requiredSkills };
		}

		template <typename Modifiers>
		constexpr _WarfareBuff<Modifiers> MakeBuff(WarfareBuffID warfareBuffID, const Modifiers& modifiers) {
			return { warfareBuffID, modifiers };
		}

		template <typename Inputs>
		constexpr _Schematic<Inputs> MakeSchematic(SchematicID schematicID, std::chrono::seconds cycleTime, std::pair<const Commodity*, std::size_t> output, const Inputs& inputs) {
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
			return _array<std::pair<const Commodity*, std::size_t>, Args...>(args...);
		}

		constexpr std::pair<const Commodity*, std::size_t> _C (const Commodity* commodity, std::size_t quantity) {
			return {commodity, quantity};
		}

	}
}
