//
//  character.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "character.h"
#include "internal.h"

dgmpp_type dgmpp_character_create() {
	return add_unique_ptr_wrapper(Character::Create());
}

dgmpp_type dgmpp_character_copy (dgmpp_type character) {
	try {
		return add_unique_ptr_wrapper(Character::Create(*reinterpret_cast<Character*>(character)));
	}
	catch (...) {
		return nullptr;
	}
}

const char*	dgmpp_character_get_name (dgmpp_type character) {
	return reinterpret_cast<Character*>(character)->name().c_str();
}

void dgmpp_character_set_name (dgmpp_type character, const char* name) {
	reinterpret_cast<Character*>(character)->name(name);
}


dgmpp_bool dgmpp_character_set_skill_levels (dgmpp_type character, int skill_levels) {
	try {
		reinterpret_cast<Character*>(character)->setSkillLevels(skill_levels);
		return true;
	}
	catch (...) {
		return false;
	}
}

dgmpp_array dgmpp_character_copy_skills (dgmpp_type character) {
	return dgmpp_make_array<Type*>(reinterpret_cast<Character*>(character)->skills());
}

dgmpp_bool dgmpp_character_add_implant (dgmpp_type character, dgmpp_type implant) {
	return dgmpp_character_add_implant_v2(character, implant, false);
}

dgmpp_bool dgmpp_character_add_implant_v2 (dgmpp_type character, dgmpp_type implant, dgmpp_bool replace) {
	try {
		reinterpret_cast<Character*>(character)->add(get_unique_ptr<Implant>(implant));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_bool dgmpp_character_add_booster (dgmpp_type character, dgmpp_type booster) {
	return dgmpp_character_add_booster_v2(character, booster, false);
}

dgmpp_bool dgmpp_character_add_booster_v2 (dgmpp_type character, dgmpp_type booster, dgmpp_bool replace) {
	try {
		reinterpret_cast<Character*>(character)->add(get_unique_ptr<Booster>(booster));
		return true;
	}
	catch(...) {
		return false;
	}
}

void dgmpp_character_remove_implant (dgmpp_type character, dgmpp_type implant) {
	reinterpret_cast<Character*>(character)->remove(reinterpret_cast<Implant*>(implant));
}

void dgmpp_character_remove_booster (dgmpp_type character, dgmpp_type booster) {
	reinterpret_cast<Character*>(character)->remove(reinterpret_cast<Booster*>(booster));
}

dgmpp_array dgmpp_character_copy_implants (dgmpp_type character) {
	return dgmpp_make_array<Implant*>(reinterpret_cast<Character*>(character)->implants());
}

dgmpp_array dgmpp_character_copy_boosters (dgmpp_type character) {
	return dgmpp_make_array<Booster*>(reinterpret_cast<Character*>(character)->boosters());
}


dgmpp_type dgmpp_character_get_ship (dgmpp_type character) {
	return reinterpret_cast<Character*>(character)->ship();
}

dgmpp_type dgmpp_character_get_structure (dgmpp_type character) {
	return reinterpret_cast<Character*>(character)->structure();
}

void dgmpp_character_set_ship (dgmpp_type character, dgmpp_type ship) {
	if (ship)
		reinterpret_cast<Character*>(character)->ship(get_unique_ptr<Ship>(ship));
	else
		reinterpret_cast<Character*>(character)->ship(nullptr);
}

void dgmpp_character_set_structure (dgmpp_type character, dgmpp_type structure) {
	if (structure)
		reinterpret_cast<Character*>(character)->structure(get_unique_ptr<Structure>(structure));
	else
		reinterpret_cast<Character*>(character)->structure(nullptr);
}

dgmpp_meter dgmpp_character_get_drone_control_distance (dgmpp_type character) {
	return reinterpret_cast<Character*>(character)->droneControlDistance();
}

int dgmpp_skill_get_level (dgmpp_type skill) {
	return reinterpret_cast<Skill*>(skill)->level();
}

dgmpp_bool dgmpp_skill_set_level (dgmpp_type skill, int level) {
	try {
		reinterpret_cast<Skill*>(skill)->level(level);
		return true;
	}
	catch(...) {
		return false;
	}
}


dgmpp_type dgmpp_implant_create (dgmpp_type_id type_id) {
	try {
		return add_unique_ptr_wrapper(Implant::Create(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_implant_copy (dgmpp_type implant) {
	try {
		return add_unique_ptr_wrapper(Implant::Create(*reinterpret_cast<Implant*>(implant)));
	}
	catch (...) {
		return nullptr;
	}
}

int dgmpp_implant_get_slot (dgmpp_type implant) {
	return reinterpret_cast<Implant*>(implant)->slot();
}


dgmpp_type dgmpp_booster_create (dgmpp_type_id type_id) {
	try {
		return add_unique_ptr_wrapper(Booster::Create(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_booster_copy (dgmpp_type booster) {
	try {
		return add_unique_ptr_wrapper(Booster::Create(*reinterpret_cast<Booster*>(booster)));
	}
	catch (...) {
		return nullptr;
	}
}

int dgmpp_booster_get_slot (dgmpp_type booster) {
	return reinterpret_cast<Booster*>(booster)->slot();
}

