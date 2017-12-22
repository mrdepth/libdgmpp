//
//  facility.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef facility_h
#define facility_h

#include "utility.h"
#include <stdio.h>

DGMPP_EXTERN DGMPP_FACILITY_CATEGORY dgmpp_facility_get_category (dgmpp_facility_ptr facility);

DGMPP_EXTERN dgmpp_type_id		dgmpp_facility_get_type_id		(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_group_id		dgmpp_facility_get_group_id		(dgmpp_facility_ptr facility);
DGMPP_EXTERN int64_t			dgmpp_facility_get_identifier	(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_cubic_meter	dgmpp_facility_get_capacity		(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_cubic_meter	dgmpp_facility_get_free_volume	(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_cubic_meter	dgmpp_facility_get_used_volume	(dgmpp_facility_ptr facility);

DGMPP_EXTERN dgmpp_commodity	dgmpp_facility_get_free				(dgmpp_facility_ptr facility, dgmpp_type_id commodity_id);
DGMPP_EXTERN void				dgmpp_facility_add_commodity		(dgmpp_facility_ptr facility, dgmpp_commodity commodity);
DGMPP_EXTERN BOOL				dgmpp_facility_extract_commodity	(dgmpp_facility_ptr facility, dgmpp_commodity commodity);

DGMPP_EXTERN dgmpp_array_ptr	dgmpp_facility_get_commodities	(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_commodity	dgmpp_facility_get_commodity	(dgmpp_facility_ptr facility, dgmpp_type_id commodity_id);
DGMPP_EXTERN dgmpp_commodity	dgmpp_facility_get_income		(dgmpp_facility_ptr facility, dgmpp_type_id commodity_id);
DGMPP_EXTERN dgmpp_array_ptr	dgmpp_facility_get_inputs		(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_array_ptr	dgmpp_facility_get_outputs		(dgmpp_facility_ptr facility);

DGMPP_EXTERN BOOL dgmpp_facility_is_configured (dgmpp_facility_ptr facility);

DGMPP_EXTERN const char* dgmpp_facility_get_name (dgmpp_facility_ptr facility);

#endif /* facility_h */
