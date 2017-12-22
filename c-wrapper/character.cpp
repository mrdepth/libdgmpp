//
//  character.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "character.h"
#include "internal.h"

BOOL dgmpp_character_create(dgmpp_type* character) {
	*character = dgmpp_handle_impl(Character::Create(), dgmpp_handle_tag::unique_ptr_character);
	return true;
}

const char*	dgmpp_character_get_name (dgmpp_type character) {
	return dgmpp_cast<Character>(character).name().c_str();
}

void dgmpp_character_set_name (dgmpp_type character, const char* name) {
	dgmpp_cast<Character>(character).name(name);
}


BOOL dgmpp_character_set_skill_levels (dgmpp_type character, int skill_levels) {
	try {
		dgmpp_cast<Character>(character).setSkillLevels(skill_levels);
		return true;
	}
	catch (...) {
		return false;
	}
}

BOOL dgmpp_character_get_skills (dgmpp_type character, dgmpp_array* skills) {
	*skills = dgmpp_make_array<dgmpp_handle_impl>(dgmpp_cast<Character>(character).skills());
	return true;
}

BOOL dgmpp_character_add_implant (dgmpp_type character, dgmpp_type* implant) {
	return dgmpp_character_add_implant_v2(character, implant, false);
}

BOOL dgmpp_character_add_implant_v2 (dgmpp_type character, dgmpp_type* implant, BOOL replace) {
	try {
		dgmpp_reset(*implant, dgmpp_cast<Character>(character).add(dgmpp_move<Implant>(*implant), replace));
		return true;
	}
	catch(...) {
		return false;
	}
}

BOOL dgmpp_character_add_booster (dgmpp_type character, dgmpp_type* booster) {
	return dgmpp_character_add_booster_v2(character, booster, false);
}

BOOL dgmpp_character_add_booster_v2 (dgmpp_type character, dgmpp_type* booster, BOOL replace) {
	try {
		dgmpp_reset(*booster, dgmpp_cast<Character>(character).add(dgmpp_move<Booster>(*booster), replace));
		return true;
	}
	catch(...) {
		return false;
	}
}

void dgmpp_character_remove_implant (dgmpp_type character, dgmpp_type* implant) {
	dgmpp_cast<Character>(character).remove(&dgmpp_cast<Implant>(*implant));
	dgmpp_reset(*implant, nullptr);
}

void dgmpp_character_remove_booster (dgmpp_type character, dgmpp_type* booster) {
	dgmpp_cast<Character>(character).remove(&dgmpp_cast<Booster>(*booster));
	dgmpp_reset(*booster, nullptr);
}

BOOL dgmpp_character_get_implants (dgmpp_type character, dgmpp_array* implants) {
	*implants = dgmpp_make_array<dgmpp_handle_impl>(dgmpp_cast<Character>(character).implants());
	return true;
}

BOOL dgmpp_character_get_boosters (dgmpp_type character, dgmpp_array* boosters) {
	*boosters = dgmpp_make_array<dgmpp_handle_impl>(dgmpp_cast<Character>(character).boosters());
	return true;
}


BOOL dgmpp_character_get_ship (dgmpp_type character, dgmpp_type* ship) {
	if (auto type = dgmpp_cast<Character>(character).ship()) {
		*ship = dgmpp_handle_impl(type);
		return true;
	}
	else
		return false;
}

BOOL dgmpp_character_get_structure (dgmpp_type character, dgmpp_type* structure) {
	if (auto type = dgmpp_cast<Character>(character).structure()) {
		*structure = dgmpp_handle_impl(type);
		return true;
	}
	else
		return false;
}

void dgmpp_character_set_ship (dgmpp_type character, dgmpp_type* ship) {
	if (ship)
		dgmpp_reset(*ship, dgmpp_cast<Character>(character).ship(dgmpp_move<Ship>(*ship)));
	else
		dgmpp_cast<Character>(character).ship(nullptr);
}

void dgmpp_character_set_structure (dgmpp_type character, dgmpp_type* structure) {
	if (structure)
		dgmpp_reset(*structure, dgmpp_cast<Character>(character).ship(dgmpp_move<Structure>(*structure)));
	else
		dgmpp_cast<Character>(character).structure(nullptr);
}

dgmpp_meter dgmpp_character_get_drone_control_distance (dgmpp_type character) {
	return dgmpp_cast<Character>(character).droneControlDistance();
}

int dgmpp_skill_get_level (dgmpp_type skill) {
	return dgmpp_cast<Skill>(skill).level();
}

BOOL dgmpp_skill_set_level (dgmpp_type skill, int level) {
	try {
		dgmpp_cast<Skill>(skill).level(level);
		return true;
	}
	catch(...) {
		return false;
	}
}


BOOL dgmpp_implant_create (dgmpp_type_id type_id, dgmpp_type* implant) {
	try {
		*implant = dgmpp_handle_impl(Implant::Create(static_cast<TypeID>(type_id)), dgmpp_handle_tag::unique_ptr_area);
		return true;
	}
	catch (...) {
		return false;
	}
}

int dgmpp_implant_get_slot (dgmpp_type implant) {
	return dgmpp_cast<Implant>(implant).slot();
}


BOOL dgmpp_booster_create (dgmpp_type_id type_id, dgmpp_type* booster) {
	try {
		*booster = dgmpp_handle_impl(Booster::Create(static_cast<TypeID>(type_id)), dgmpp_handle_tag::unique_ptr_area);
		return true;
	}
	catch (...) {
		return false;
	}
}

int dgmpp_booster_get_slot (dgmpp_type booster) {
	return dgmpp_cast<Booster>(booster).slot();
}

