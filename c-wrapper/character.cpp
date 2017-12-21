//
//  character.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "character.h"
#include "internal.h"

dgmpp_type_ptr dgmpp_character_create() {
	return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_character_impl());
}

const char*	dgmpp_character_get_name (dgmpp_type_ptr character) {
	return type_cast<Character*>(character)->name().c_str();
}

void dgmpp_character_set_name (dgmpp_type_ptr character, const char* name) {
	type_cast<Character*>(character)->name(name);
}


BOOL dgmpp_character_set_skill_levels (dgmpp_type_ptr character, int skill_levels) {
	try {
		type_cast<Character*>(character)->setSkillLevels(skill_levels);
		return true;
	}
	catch (...) {
		return false;
	}
}

dgmpp_array_ptr dgmpp_character_get_skills (dgmpp_type_ptr character) {
	return dgmpp_make_array<dgmpp_type_impl*>(type_cast<Character*>(character)->skills());
}

BOOL dgmpp_character_add_implant (dgmpp_type_ptr character, dgmpp_type_ptr implant) {
	return dgmpp_character_add_implant_v2(character, implant, false);
}

BOOL dgmpp_character_add_implant_v2 (dgmpp_type_ptr character, dgmpp_type_ptr implant, BOOL replace) {
	try {
		type_cast<Character*>(character)->add(std::move(reinterpret_cast<dgmpp_implant_impl*>(implant)->implant), replace);
		return true;
	}
	catch(...) {
		return false;
	}
}

BOOL dgmpp_character_add_booster (dgmpp_type_ptr character, dgmpp_type_ptr booster) {
	return dgmpp_character_add_booster_v2(character, booster, false);
}

BOOL dgmpp_character_add_booster_v2 (dgmpp_type_ptr character, dgmpp_type_ptr booster, BOOL replace) {
	try {
		type_cast<Character*>(character)->add(std::move(reinterpret_cast<dgmpp_booster_impl*>(booster)->booster), replace);
		return true;
	}
	catch(...) {
		return false;
	}
}

void dgmpp_character_remove_implant (dgmpp_type_ptr character, dgmpp_type_ptr implant) {
	type_cast<Character*>(character)->remove(type_cast<Implant*>(implant));
}

void dgmpp_character_remove_booster (dgmpp_type_ptr character, dgmpp_type_ptr booster) {
	type_cast<Character*>(character)->remove(type_cast<Booster*>(booster));
}

dgmpp_array_ptr dgmpp_character_get_implants (dgmpp_type_ptr character) {
	return dgmpp_make_array<dgmpp_type_impl*>(type_cast<Character*>(character)->implants());
}

dgmpp_array_ptr dgmpp_character_get_boosters (dgmpp_type_ptr character) {
	return dgmpp_make_array<dgmpp_type_impl*>(type_cast<Character*>(character)->boosters());
}


dgmpp_type_ptr dgmpp_character_get_ship (dgmpp_type_ptr character) {
	return dgmpp_make_type(type_cast<Character*>(character)->ship());
}

dgmpp_type_ptr dgmpp_character_get_structure (dgmpp_type_ptr character) {
	return dgmpp_make_type(type_cast<Character*>(character)->structure());
}

void dgmpp_character_set_ship (dgmpp_type_ptr character, dgmpp_type_ptr ship) {
	type_cast<Character*>(character)->ship(std::move(reinterpret_cast<dgmpp_ship_impl*>(ship)->ship));
}

void dgmpp_character_set_structure (dgmpp_type_ptr character, dgmpp_type_ptr structure) {
	type_cast<Character*>(character)->ship(std::move(reinterpret_cast<dgmpp_structure_impl*>(structure)->structure));
}

dgmpp_meter dgmpp_character_get_drone_control_distance (dgmpp_type_ptr character) {
	return type_cast<Character*>(character)->droneControlDistance();
}

int dgmpp_skill_get_level (dgmpp_type_ptr skill) {
	return type_cast<Skill*>(skill)->level();
}

BOOL dgmpp_skill_set_level (dgmpp_type_ptr skill, int level) {
	try {
		type_cast<Skill*>(skill)->level(level);
		return true;
	}
	catch(...) {
		return false;
	}
}


dgmpp_type_ptr dgmpp_implant_create (dgmpp_type_id type_id) {
	try {
		return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_implant_impl(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

int dgmpp_implant_get_slot (dgmpp_type_ptr implant) {
	return type_cast<Implant*>(implant)->slot();
}


dgmpp_type_ptr dgmpp_booster_create (dgmpp_type_id type_id) {
	try {
		return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_booster_impl(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

int dgmpp_booster_get_slot (dgmpp_type_ptr booster) {
	return type_cast<Booster*>(booster)->slot();
}

