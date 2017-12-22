//
//  extractor_control_unit.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef extractor_control_unit_h
#define extractor_control_unit_h

#include "utility.h"
#include <stdio.h>

DGMPP_EXTERN dgmpp_seconds	dgmpp_ecu_get_launch_time	(dgmpp_facility_ptr facility);
DGMPP_EXTERN void			dgmpp_ecu_set_launch_time	(dgmpp_facility_ptr facility, dgmpp_seconds launch_time);
DGMPP_EXTERN dgmpp_seconds	dgmpp_ecu_get_install_time	(dgmpp_facility_ptr facility);
DGMPP_EXTERN void			dgmpp_ecu_set_install_time	(dgmpp_facility_ptr facility, dgmpp_seconds install_time);
DGMPP_EXTERN dgmpp_seconds	dgmpp_ecu_get_expiry_time	(dgmpp_facility_ptr facility);
DGMPP_EXTERN void			dgmpp_ecu_set_expiry_time	(dgmpp_facility_ptr facility, dgmpp_seconds expiry_time);
DGMPP_EXTERN dgmpp_seconds	dgmpp_ecu_get_cycle_time	(dgmpp_facility_ptr facility);
DGMPP_EXTERN void			dgmpp_ecu_set_cycle_time	(dgmpp_facility_ptr facility, dgmpp_seconds cycle_time);

DGMPP_EXTERN size_t	dgmpp_ecu_get_quantity_per_cycle (dgmpp_facility_ptr facility);
DGMPP_EXTERN void	dgmpp_ecu_set_quantity_per_cycle (dgmpp_facility_ptr facility, size_t quantity_per_cycle);

DGMPP_EXTERN BOOL	dgmpp_ecu_get_output (dgmpp_facility_ptr facility, dgmpp_commodity* commodity);

DGMPP_EXTERN dgmpp_array dgmpp_ecu_get_states (dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_array dgmpp_ecu_get_cycles (dgmpp_facility_ptr facility);

#endif /* extractor_control_unit_h */

