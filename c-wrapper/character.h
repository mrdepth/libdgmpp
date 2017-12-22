//
//  character.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef character_h
#define character_h

#include "type.h"

DGMPP_EXTERN BOOL dgmpp_character_create(dgmpp_type* character);

DGMPP_EXTERN const char*	dgmpp_character_get_name (dgmpp_type character);
DGMPP_EXTERN void			dgmpp_character_set_name (dgmpp_type character, const char* name);

DGMPP_EXTERN BOOL 	dgmpp_character_set_skill_levels	(dgmpp_type character, int skill_levels);
DGMPP_EXTERN BOOL	dgmpp_character_get_skills			(dgmpp_type character, dgmpp_array* skills);

DGMPP_EXTERN BOOL dgmpp_character_add_implant				(dgmpp_type character, dgmpp_type* implant);
DGMPP_EXTERN BOOL dgmpp_character_add_implant_v2			(dgmpp_type character, dgmpp_type* implant, BOOL replace);
DGMPP_EXTERN BOOL dgmpp_character_add_booster				(dgmpp_type character, dgmpp_type* booster);
DGMPP_EXTERN BOOL dgmpp_character_add_booster_v2			(dgmpp_type character, dgmpp_type* booster, BOOL replace);
DGMPP_EXTERN void dgmpp_character_remove_implant			(dgmpp_type character, dgmpp_type* implant);
DGMPP_EXTERN void dgmpp_character_remove_booster			(dgmpp_type character, dgmpp_type* booster);
DGMPP_EXTERN BOOL dgmpp_character_get_implants	(dgmpp_type character, dgmpp_array* implants);
DGMPP_EXTERN BOOL dgmpp_character_get_boosters	(dgmpp_type character, dgmpp_array* boosters);

DGMPP_EXTERN BOOL	dgmpp_character_get_ship		(dgmpp_type character, dgmpp_type* ship);
DGMPP_EXTERN BOOL	dgmpp_character_get_structure	(dgmpp_type character, dgmpp_type* structure);
DGMPP_EXTERN void 	dgmpp_character_set_ship		(dgmpp_type character, dgmpp_type* ship);
DGMPP_EXTERN void 	dgmpp_character_set_structure	(dgmpp_type character, dgmpp_type* structure);

DGMPP_EXTERN dgmpp_meter dgmpp_character_get_drone_control_distance (dgmpp_type character);


DGMPP_EXTERN int	dgmpp_skill_get_level (dgmpp_type skill);
DGMPP_EXTERN BOOL	dgmpp_skill_set_level (dgmpp_type skill, int level);

DGMPP_EXTERN BOOL	dgmpp_implant_create	(dgmpp_type_id type_id, dgmpp_type* implant);
DGMPP_EXTERN int	dgmpp_implant_get_slot	(dgmpp_type implant);

DGMPP_EXTERN BOOL	dgmpp_booster_create	(dgmpp_type_id type_id, dgmpp_type* booster);
DGMPP_EXTERN int	dgmpp_booster_get_slot	(dgmpp_type booster);

#endif /* character_h */
