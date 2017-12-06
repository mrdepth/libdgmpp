//
//  Errors.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include <stdexcept>
#include "Utility.hpp"

namespace dgmpp2 {
	
	template <typename T>
	struct CannotFit: public std::runtime_error {
		CannotFit(std::unique_ptr<T> type): type(std::move(type)), std::runtime_error("Cannot fit") {}
		std::unique_ptr<T> type;
	};

	struct InvalidSkillLevel: std::runtime_error {
		InvalidSkillLevel(): std::runtime_error("Skill level should be in [0...5] range") {}
	};

	template<typename T>
	class NotFound: public std::runtime_error {
	public:
		NotFound (T identifier) : std::runtime_error("id = " + std::to_string(static_cast<int>(identifier))) {};
	};
	
	struct NotEnoughCommodities: public std::runtime_error {
		NotEnoughCommodities(size_t quantity) : std::runtime_error(std::to_string(quantity)) {}
	};

	struct InvalidRoute: public std::runtime_error {
		InvalidRoute() : std::runtime_error("Missing source or destination") {}
	};

//	struct DifferentCommodities: public std::runtime_error {
//		DifferentCommodities(TypeID a, TypeID b) : std::runtime_error(std::to_string(static_cast<int>(a)) + " != " + std::to_string(static_cast<int>(b))) {}
//	}

}
