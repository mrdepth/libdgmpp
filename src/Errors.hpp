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
		CannotFit(std::unique_ptr<T> type): type(std::move(type)), std::logic_error("Cannot fit") {}
		std::unique_ptr<T> type;
	};

	struct InvalidSkillLevel: std::invalid_argument {
		InvalidSkillLevel(): std::invalid_argument("Skill level should be in [0...5] range") {}
	};

	template<typename T>
	class NotFound: public std::out_of_range {
	public:
		NotFound (T identifier) : std::out_of_range("id = " + std::to_string(static_cast<int>(identifier))) {};
	};
	
	struct NotEnoughCommodities: public std::logic_error {
		NotEnoughCommodities(size_t quantity) : std::logic_error(std::to_string(quantity)) {}
	};

	struct InvalidRoute: public std::invalid_argument {
		InvalidRoute() : std::invalid_argument("Missing source or destination") {}
	};

//	struct DifferentCommodities: public std::runtime_error {
//		DifferentCommodities(TypeID a, TypeID b) : std::runtime_error(std::to_string(static_cast<int>(a)) + " != " + std::to_string(static_cast<int>(b))) {}
//	}

}
