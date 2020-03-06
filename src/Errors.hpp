//
//  Errors.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include <stdexcept>
#include "Utility.hpp"

namespace dgmpp {
	
	template <typename T>
	struct CannotFit: public std::logic_error {
		CannotFit(const std::shared_ptr<T>& type): type(type), std::logic_error("Cannot fit") {}
		std::shared_ptr<T> type;
	};

//    template <typename T>
//    struct TypeAlreadyHaveParent: public std::logic_error {
//        template <typename Ptr, typename = std::enable_if_t<std::is_constructible_v<std::shared_ptr<T>, Ptr>>>
//        TypeAlreadyHaveParent(Ptr&& type): type(std::forward<Ptr>(type)), std::logic_error("Type must not already have a parent") {}
//        std::shared_ptr<T> type;
//    };


	struct InvalidSkillLevel: std::invalid_argument {
		InvalidSkillLevel(): std::invalid_argument("Skill level should be in [0...5] range") {}
	};

	template<typename T>
	class NotFound: public std::out_of_range {
	public:
		NotFound (T identifier) : std::out_of_range("id = " + std::to_string(static_cast<int>(identifier))) {};
	};
	
	struct NotEnoughCommodities: public std::logic_error {
		NotEnoughCommodities(std::size_t quantity) : std::logic_error(std::to_string(quantity)) {}
	};

	struct InvalidRoute: public std::invalid_argument {
		InvalidRoute() : std::invalid_argument("Missing source or destination") {}
	};
	
	struct InvalidCategoryID: public std::logic_error {
		InvalidCategoryID(CategoryID categoryID): categoryID(categoryID), std::logic_error("Invalid categoryID") {};
		CategoryID categoryID;
	};

//	struct DifferentCommodities: public std::runtime_error {
//		DifferentCommodities(TypeID a, TypeID b) : std::runtime_error(std::to_string(static_cast<int>(a)) + " != " + std::to_string(static_cast<int>(b))) {}
//	}

}
