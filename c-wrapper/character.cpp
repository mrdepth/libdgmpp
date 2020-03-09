//
//  character.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "character.h"
#include "internal.h"

dgmpp_type dgmpp_character_create() {
	return new_handle(std::make_shared<Character>());
}

dgmpp_type dgmpp_character_copy (dgmpp_type character) {
	try {
		return new_handle(std::make_shared<Character>(*get<Character>(character)));
	}
	catch (...) {
		return nullptr;
	}
}

const char*	dgmpp_character_get_name (dgmpp_type character) {
	return get<Character>(character)->name().c_str();
}

void dgmpp_character_set_name (dgmpp_type character, const char* name) {
	return get<Character>(character)->name(name);
}


dgmpp_bool dgmpp_character_set_skill_levels (dgmpp_type character, int skill_levels) {
	try {
		get<Character>(character)->setSkillLevels(skill_levels);
		return true;
	}
	catch (...) {
		return false;
	}
}

dgmpp_array dgmpp_character_copy_skills (dgmpp_type character) {
	auto skills = get<Character>(character)->skills();
    std::vector<dgmpp_handle> result;
    std::transform(skills.begin(), skills.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    
	return dgmpp_make_array<dgmpp_handle>(std::move(result));
}

dgmpp_bool dgmpp_character_add_implant (dgmpp_type character, dgmpp_type implant, dgmpp_bool replace) {
	try {
        get<Character>(character)->add(get<Implant>(implant), replace);
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_bool dgmpp_character_add_booster (dgmpp_type character, dgmpp_type booster, dgmpp_bool replace) {
	try {
        get<Character>(character)->add(get<Booster>(booster), replace);
		return true;
	}
	catch(...) {
		return false;
	}
}

void dgmpp_character_remove_implant (dgmpp_type character, dgmpp_type implant) {
    get<Character>(character)->remove(get<Implant>(implant).get());
}

void dgmpp_character_remove_booster (dgmpp_type character, dgmpp_type booster) {
    get<Character>(character)->remove(get<Booster>(booster).get());
}

dgmpp_array dgmpp_character_copy_implants (dgmpp_type character) {
    auto implants = get<Character>(character)->implants();
    std::vector<dgmpp_handle> result;
    std::transform(implants.begin(), implants.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    return dgmpp_make_array<dgmpp_handle>(std::move(result));
}

dgmpp_array dgmpp_character_copy_boosters (dgmpp_type character) {
    auto boosters = get<Character>(character)->boosters();
    std::vector<dgmpp_handle> result;
    std::transform(boosters.begin(), boosters.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    return dgmpp_make_array<dgmpp_handle>(std::move(result));
}


dgmpp_type dgmpp_character_copy_ship (dgmpp_type character) {
    return new_handle(get<Character>(character)->ship());
}

//dgmpp_type dgmpp_character_get_structure (dgmpp_type character) {
//	return reinterpret_cast<Character*>(character)->structure();
//}

void dgmpp_character_set_ship (dgmpp_type character, dgmpp_type ship) {
    get<Character>(character)->ship(get<Ship>(ship));
}

//void dgmpp_character_set_structure (dgmpp_type character, dgmpp_type structure) {
//	if (structure)
//		reinterpret_cast<Character*>(character)->structure(get_unique_ptr<Structure>(structure));
//	else
//		reinterpret_cast<Character*>(character)->structure(nullptr);
//}

dgmpp_meter dgmpp_character_get_drone_control_distance (dgmpp_type character) {
	return get<Character>(character)->droneControlDistance();
}

int dgmpp_skill_get_level (dgmpp_type skill) {
	return get<Skill>(skill)->level();
}

dgmpp_bool dgmpp_skill_set_level (dgmpp_type skill, int level) {
	try {
		get<Skill>(skill)->level(level);
		return true;
	}
	catch(...) {
		return false;
	}
}


dgmpp_type dgmpp_implant_create (dgmpp_type_id type_id) {
	try {
        return new_handle(std::make_shared<Implant>(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_implant_copy (dgmpp_type implant) {
	try {
        return new_handle(std::make_shared<Implant>(*get<Implant>(implant)));
	}
	catch (...) {
		return nullptr;
	}
}

int dgmpp_implant_get_slot (dgmpp_type implant) {
	return get<Implant>(implant)->slot();
}


dgmpp_type dgmpp_booster_create (dgmpp_type_id type_id) {
	try {
        return new_handle(std::make_shared<Booster>(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_booster_copy (dgmpp_type booster) {
	try {
        return new_handle(std::make_shared<Booster>(*get<Booster>(booster)));
	}
	catch (...) {
		return nullptr;
	}
}

int dgmpp_booster_get_slot (dgmpp_type booster) {
	return get<Booster>(booster)->slot();
}

