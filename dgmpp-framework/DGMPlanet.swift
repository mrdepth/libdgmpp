//
//  DGMPlanet.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMPlanet {
	var opaque: dgmpp_planet_ptr
	
	public required init(_ opaque: dgmpp_planet_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_release(opaque)
	}
	
	public convenience init() {
		self.init(dgmpp_planet_create())
	}
	
	public func add(facility typeID: DGMTypeID, identifier: Int64 = 0) throws -> DGMFacility {
		guard let facility = dgmpp_planet_add_facility(opaque, dgmpp_type_id(typeID), identifier) else {throw DGMError.invalidFacility(typeID)}
		return DGMFacility.facility(facility)
	}
	
	public func remove(facility: DGMFacility) {
		dgmpp_planet_remove_facility(opaque, facility.opaque)
	}
	
	public var facilities: [DGMFacility] {
		return DGMArray<DGMFacility>(dgmpp_planet_get_facilities(opaque)).array
	}
	
	public subscript(identifier: Int64) -> DGMFacility? {
		guard let facility = dgmpp_planet_get_facility(opaque, identifier) else {return nil}
		return DGMFacility.facility(facility)
	}
	
	public func add(route: DGMRoute) {
		dgmpp_planet_add_route(opaque, route.from.opaque, route.to.opaque, dgmpp_commodity(route.commodity))
	}
	
	public func remove(route: DGMRoute) {
		dgmpp_planet_remove_route(opaque, route.from.opaque, route.to.opaque, dgmpp_commodity(route.commodity))
	}
	
	public var lastUpdate: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_planet_get_last_update(opaque))
		}
		set {
			dgmpp_planet_set_last_update(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	@discardableResult
	public func run() -> Date {
		return Date(timeIntervalSinceReferenceDate: dgmpp_planet_run(opaque))
	}

}

extension DGMPlanet: Hashable {
	
	public var hashValue: Int {
		return dgmpp_get_hash(opaque)
	}
	
	public static func ==(lhs: DGMPlanet, rhs: DGMPlanet) -> Bool {
		return lhs.hashValue == rhs.hashValue
	}
}

