//
//  DGMPlanet.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation
import cwrapper

public class DGMPlanet: DGMObject, ObservableObject {
	
	public convenience init() {
		self.init(dgmpp_planet_create())
	}
	
	public func add(facility typeID: DGMTypeID, identifier: Int64 = 0) throws -> DGMFacility {
		guard let facility = dgmpp_planet_add_facility(handle, dgmpp_type_id(typeID), identifier) else {throw DGMError.invalidFacility(typeID)}
		return DGMFacility.facility(facility)
	}
	
	public func remove(facility: DGMFacility) {
		dgmpp_planet_remove_facility(handle, facility.handle)
	}
	
	public var facilities: [DGMFacility] {
		return DGMArray<DGMFacility>(dgmpp_planet_copy_facilities(handle)).array
	}
	
	public subscript(identifier: Int64) -> DGMFacility? {
		guard let facility = dgmpp_planet_get_facility(handle, identifier) else {return nil}
		return DGMFacility.facility(facility)
	}
	
	public func add(route: DGMRoute) {
        guard let from = route.from?.handle, let to = route.to?.handle else {return}
		dgmpp_planet_add_route(handle, from, to, dgmpp_commodity(route.commodity))
	}
	
	public func remove(route: DGMRoute) {
        guard let from = route.from?.handle, let to = route.to?.handle else {return}
		dgmpp_planet_remove_route(handle, from, to, dgmpp_commodity(route.commodity))
	}
	
	public var lastUpdate: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_planet_get_last_update(handle))
		}
		set {
			dgmpp_planet_set_last_update(handle, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	@discardableResult
	public func run() -> Date {
		return Date(timeIntervalSinceReferenceDate: dgmpp_planet_run(handle))
	}

}
