//
//  Attribute.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include <utility>
#include <array>
#include <numeric>
#include "Type.hpp"
#include "SDE.hpp"
#include <functional>

#include <iostream>

namespace dgmpp {
	using namespace std::placeholders;

	namespace {
		constexpr std::size_t sfCount = 10;
		
		Float sf(int n) {
			return std::exp(-static_cast<Float>(std::pow(n, 2.0)) / 7.1289);
		}
		
		template<class Function, std::size_t... Indices>
		auto make_array_helper(Function f, std::index_sequence<Indices...>)
		-> std::array<typename std::result_of<Function(std::size_t)>::type, sizeof...(Indices)>
		{
			return {{ f(Indices)... }};
		}
		
		template<int N, class Function>
		auto make_array(Function f)
		-> std::array<typename std::result_of<Function(std::size_t)>::type, N>
		{
			return make_array_helper(f, std::make_index_sequence<N>{});
		}
		
		auto stackingFactor = make_array<sfCount>(sf);
		
		template <typename... Args>
		struct _AssociationComparer {
			bool operator()(const Modifier* modifier) {
				return std::find(associations.begin(), associations.end(), modifier->metaInfo().association) != associations.end();
			}
			
			constexpr _AssociationComparer(Args... arg): associations{arg...} {};
			std::array<MetaInfo::Modifier::Association, sizeof...(Args)> associations;
		};
		
		template <typename... Args>
		_AssociationComparer<Args...> AssociationComparer(Args&&... args) {
			return _AssociationComparer<Args...>(std::forward<Args>(args)...);
		}
	}
	
	Attribute::Attribute(const MetaInfo::Attribute& metaInfo, Float initialValue, Type& owner)
	: metaInfo_(metaInfo), initialValue_(initialValue), owner_(owner) {
		if (metaInfo.maxAttributeID != AttributeID::none) {
			maxAttribute_ = owner.attribute_(metaInfo.maxAttributeID);
		}
	}
	
	//	Attribute::Proxy::operator Float() const {
	//		return (**this).get();
	//		if (attribute_->second) {
	//			return *attribute_->second;
	//		}
	//		else {
	//			return metaInfo().defaultValue;
	//		}
	//	}
	
	Attribute& Attribute::Proxy::operator*() const {
		if (!attribute_->second) {
			const auto& metaInfo = this->metaInfo();
			attribute_->second = std::unique_ptr<Attribute>(new Attribute(metaInfo, metaInfo.defaultValue, *owner_));
		}
		return *attribute_->second;
	}
	
	const MetaInfo::Attribute& Attribute::Proxy::metaInfo() const {
		if (!metaInfo_) {
			if (attribute_->second)
				metaInfo_ = &attribute_->second->metaInfo();
			else
				metaInfo_ = &SDE::get(attribute_->first);
		}
		return *metaInfo_;
	}
	
	Attribute& Attribute::operator= (std::optional<Float>&& value) noexcept {
		forcedValue_ = std::move(value);
		owner().resetCache_();
		return *this;
	}
	
	Float Attribute::value() {
		LOCK(&owner_);
		return value_();
	}
	
	Float Attribute::value_() {
		if (forcedValue_)
			return *forcedValue_;
		
		if (!calculatedValue_) {
#if DEBUG
			assert(recursionFlag_ == false);
			recursionFlag_ = true;
#endif
			
			auto value = initialValue_;
			auto modifiers = owner().modifiers_(metaInfo());
			bool isDisallowedAssistance;
			bool isDisallowedOffense;
			if (metaInfo().attributeID != AttributeID::disallowAssistance && metaInfo().attributeID != AttributeID::disallowOffensiveModifiers) {
				isDisallowedAssistance = owner().isDisallowedAssistance_();
				isDisallowedOffense = owner().isDisallowedOffense_();
			}
			else {
				isDisallowedAssistance = false;
				isDisallowedOffense = false;
			}
			const bool isStackable = metaInfo().isStackable;
			const bool highIsGood = metaInfo().highIsGood;
			
			auto character = owner().domain_(MetaInfo::Modifier::Domain::character);
			
			auto begin = modifiers.begin();
			auto end = modifiers.end();
			if (character) {
				end = std::partition(begin, end, [=](const auto modifier) {
					const auto& affector = modifier->owner();
					const auto isProjected = !affector.isDescendant_(*character);
					return !(isProjected &&
							 ((isDisallowedOffense && modifier->effect().metaInfo().isOffensive) ||
							  (isDisallowedAssistance && modifier->effect().metaInfo().isAssistance)));
				});
			}
			
			auto partition = [&](const auto& pred) {
				auto partialEnd = std::partition(begin, end, pred);
				auto result = std::make_pair(begin, partialEnd);
				begin = partialEnd;
				return result;
			};
			
			auto add = [](auto a, auto b) {
				return a + b->value();
			};
			auto sub = [](auto a, auto b) {
				return a - b->value();
			};
			
			auto mul = [](auto a, auto b) {
				return a * b->value();
			};
			
			
			std::vector<Float> values;
			values.reserve(std::distance(end, begin));
			auto extract = [](auto a) {
				return a->value();
			};
			
			std::function<Float(const std::pair<decltype(begin), decltype(end)>&, Float)> multiply;
			
			if (isStackable) {
				multiply = [&values, isStackable, &mul](const auto& range, auto v) -> Float {
					v = std::accumulate(range.first, range.second, v, mul);
					return v;
				};
			}
			else {
				multiply = [&values, isStackable, highIsGood, &mul, &extract](const auto& range, auto v) -> Float {
					auto i = std::partition(range.first, range.second, [=](auto modifier) {
						return modifier->needsStackingCheck();
					});
					
					v = std::accumulate(i, range.second, v, mul);
					values.clear();
					std::transform(range.first, i, std::back_inserter(values), extract);
					
					auto j = std::partition(values.begin(), values.end(), std::bind(std::less<>(), _1, 1.0));

					std::sort(values.begin(), j, std::less<>());
					std::sort(j, values.end(), std::greater<>());
					
					v = std::inner_product(values.begin(), std::min(j, values.begin() + sfCount), stackingFactor.begin(), v, std::multiplies<>(), [](auto a, auto b) {
						return 1.0 + (a - 1.0) * b;
					});
					
					v = std::inner_product(j, std::min(values.end(), j + sfCount), stackingFactor.begin(), v, std::multiplies<>(), [](auto a, auto b) {
						return 1.0 + (a - 1.0) * b;
					});
					
					return v;
				};
			}
			
			auto postAssignments = partition(AssociationComparer(MetaInfo::Modifier::Association::postAssignment));
			
			if (postAssignments.first != postAssignments.second) {
				value = extract(*postAssignments.first);
			}
			else {
				auto range = partition(AssociationComparer(MetaInfo::Modifier::Association::modAdd, MetaInfo::Modifier::Association::addRate));
				value = std::accumulate(range.first, range.second, value, add);
				
				range = partition(AssociationComparer(MetaInfo::Modifier::Association::modSub, MetaInfo::Modifier::Association::subRate));
				value = std::accumulate(range.first, range.second, value, sub);
				
				range = partition(AssociationComparer(MetaInfo::Modifier::Association::preMul));
				value = multiply(range, value);
				
				range = partition(AssociationComparer(MetaInfo::Modifier::Association::preDiv));
				value = multiply(range, value);
			}
			
			auto range = partition(AssociationComparer(MetaInfo::Modifier::Association::postMul));
			value = multiply(range, value);
			

			range = partition(AssociationComparer(MetaInfo::Modifier::Association::postDiv));
			value = multiply(range, value);

			range = partition(AssociationComparer(MetaInfo::Modifier::Association::postPercent));
			value = multiply(range, value);
			
			
			
			if (maxAttribute_) {
				value = std::min(value, (*maxAttribute_)->value_());
			}

			calculatedValue_ = value;
			owner_.cache_().add(this);
#if DEBUG
			recursionFlag_ = false;
#endif
		}
		
		return *calculatedValue_;
	}
	
#if DEBUG
	void Attribute::dumpAffectors() {
		auto value = initialValue_;
		auto modifiers = owner().modifiers_(metaInfo());
		bool isDisallowedAssistance;
		bool isDisallowedOffense;
		if (metaInfo().attributeID != AttributeID::disallowAssistance && metaInfo().attributeID != AttributeID::disallowOffensiveModifiers) {
			isDisallowedAssistance = owner().isDisallowedAssistance_();
			isDisallowedOffense = owner().isDisallowedOffense_();
		}
		else {
			isDisallowedAssistance = false;
			isDisallowedOffense = false;
		}
		const bool isStackable = metaInfo().isStackable;
		const bool highIsGood = metaInfo().highIsGood;
		
		auto character = owner().domain_(MetaInfo::Modifier::Domain::character);
		
		auto begin = modifiers.begin();
		auto end = modifiers.end();
		if (character) {
			end = std::partition(begin, end, [=](const auto modifier) {
				const auto& affector = modifier->owner();
				const auto isProjected = !affector.isDescendant_(*character);
				return !(isProjected &&
						 ((isDisallowedOffense && modifier->effect().metaInfo().isOffensive) ||
						  (isDisallowedAssistance && modifier->effect().metaInfo().isAssistance)));
			});
		}
		
		auto partition = [&](const auto& pred) {
			auto partialEnd = std::partition(begin, end, pred);
			auto result = std::make_pair(begin, partialEnd);
			begin = partialEnd;
			return result;
		};
		
		auto add = [](auto a, auto b) {
			return a + b->value();
		};
		auto sub = [](auto a, auto b) {
			return a - b->value();
		};
		
		auto mul = [](auto a, auto b) {
			return a * b->value();
		};
		
		
		std::vector<Float> values;
		values.reserve(std::distance(end, begin));
		auto extract = [](auto a) {
			return a->value();
		};
		
		std::function<Float(const std::pair<decltype(begin), decltype(end)>&, Float)> multiply;
		
		if (isStackable) {
			multiply = [&values, isStackable, &mul](const auto& range, auto v) -> Float {
				v = std::accumulate(range.first, range.second, v, mul);
				return v;
			};
		}
		else {
			multiply = [&values, isStackable, highIsGood, &mul, &extract](const auto& range, auto v) -> Float {
				auto i = std::partition(range.first, range.second, [=](auto modifier) {
					return modifier->needsStackingCheck();
				});
				
				v = std::accumulate(i, range.second, v, mul);
				values.clear();
				std::transform(range.first, i, std::back_inserter(values), extract);
				
				decltype(values.begin()) j;
				if (!highIsGood)
					j = std::partition(values.begin(), values.end(),
									   std::bind(std::less<>(), _1, 1.0));
				else
					j = std::partition(values.begin(), values.end(),
									   std::bind(std::greater<>(), _1, 1.0));
				
				std::sort(values.begin(), j, std::greater<>());
				std::sort(j, values.end(), std::less<>());
				
				
				std::copy(values.begin(), values.end(), std::ostream_iterator<Float>(std::cout, ", "));
				
				return v;
			};
		}
		
		auto postAssignments = partition(AssociationComparer(MetaInfo::Modifier::Association::postAssignment));
		
		if (postAssignments.first != postAssignments.second) {
			value = extract(*postAssignments.first);
		}
		else {
			auto range = partition(AssociationComparer(MetaInfo::Modifier::Association::modAdd, MetaInfo::Modifier::Association::addRate));
			value = std::accumulate(range.first, range.second, value, add);
			
			range = partition(AssociationComparer(MetaInfo::Modifier::Association::modSub, MetaInfo::Modifier::Association::subRate));
			value = std::accumulate(range.first, range.second, value, sub);
			
			std::cout << "preMul: ";
			range = partition(AssociationComparer(MetaInfo::Modifier::Association::preMul));
			value = multiply(range, value);
			std::cout << std::endl;
			
			std::cout << "preDiv: ";
			range = partition(AssociationComparer(MetaInfo::Modifier::Association::preDiv));
			value = multiply(range, value);
			std::cout << std::endl;
		}
		
		std::cout << "postMul: ";
		auto range = partition(AssociationComparer(MetaInfo::Modifier::Association::postMul));
		value = multiply(range, value);
		std::cout << std::endl;
		
		std::cout << "postDiv: ";
		range = partition(AssociationComparer(MetaInfo::Modifier::Association::postDiv));
		value = multiply(range, value);
		std::cout << std::endl;

		std::cout << "postPercent: ";
		range = partition(AssociationComparer(MetaInfo::Modifier::Association::postPercent));
		value = multiply(range, value);
		std::cout << std::endl;
	}
#endif
}



