//
//  character.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef character_h
#define character_h

#include "type.h"

dgmpp_type_ptr dgmpp_character_create();

BOOL dgmpp_character_set_skill_levels				(dgmpp_type_ptr character, int skill_levels);
dgmpp_types_array_ptr dgmpp_character_get_skills	(dgmpp_type_ptr character);

BOOL dgmpp_character_add_implant					(dgmpp_type_ptr character, dgmpp_type_ptr implant);
BOOL dgmpp_character_add_implant_v2					(dgmpp_type_ptr character, dgmpp_type_ptr implant, BOOL replace);
BOOL dgmpp_character_add_booster					(dgmpp_type_ptr character, dgmpp_type_ptr booster);
BOOL dgmpp_character_add_booster_v2					(dgmpp_type_ptr character, dgmpp_type_ptr booster, BOOL replace);
void dgmpp_character_remove_implant					(dgmpp_type_ptr character, dgmpp_type_ptr implant);
void dgmpp_character_remove_booster					(dgmpp_type_ptr character, dgmpp_type_ptr booster);
dgmpp_types_array_ptr dgmpp_character_get_implants	(dgmpp_type_ptr character);
dgmpp_types_array_ptr dgmpp_character_get_boosters	(dgmpp_type_ptr character);

dgmpp_type_ptr	dgmpp_character_get_ship		(dgmpp_type_ptr character);
dgmpp_type_ptr	dgmpp_character_get_structure	(dgmpp_type_ptr character);
void 			dgmpp_character_set_ship		(dgmpp_type_ptr character, dgmpp_type_ptr ship);
void 			dgmpp_character_set_structure	(dgmpp_type_ptr character, dgmpp_type_ptr structure);

int		dgmpp_skill_get_level (dgmpp_type_ptr skill);
BOOL	dgmpp_skill_set_level (dgmpp_type_ptr skill, int level);

dgmpp_type_ptr	dgmpp_implant_create	(dgmpp_type_id type_id);
int				dgmpp_implant_get_slot	(dgmpp_type_ptr implant);

dgmpp_type_ptr	dgmpp_booster_create	(dgmpp_type_id type_id);
int				dgmpp_booster_get_slot	(dgmpp_type_ptr booster);

#endif /* character_h */
