//
//  DGMCharacter.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMImplant: DGMType {
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}
	
	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_implant_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
	
	public var slot: Int {
		return Int(dgmpp_implant_get_slot(opaque))
	}
}

public class DGMBooster: DGMType {
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}
	
	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_booster_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
	
	public var slot: Int {
		return Int(dgmpp_booster_get_slot(opaque))
	}
}

public class DGMSkill: DGMType {
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}
	
	public var level: Int {
		get {
			return Int(dgmpp_skill_get_level(opaque))
		}
		set {
			dgmpp_skill_set_level(opaque, Int32(newValue))
		}
	}
	
}

public class DGMCharacter: DGMType {
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}
	
	public init() {
		super.init(dgmpp_character_create()!)
	}
	
	public var name: String {
		get {
			return String(cString: dgmpp_character_get_name(opaque));
		}
		set {
			guard let string = newValue.cString(using: .utf8) else {return}
			dgmpp_character_set_name(opaque, string)
		}
	}

	
	public var ship: DGMShip? {
		get {
			guard let ship = dgmpp_character_get_ship(opaque) else {return nil}
			return DGMShip(ship)
		}
		set {
			dgmpp_character_set_ship(opaque, newValue?.opaque)
		}
	}
	
	public var structure: DGMStructure? {
		get {
			guard let structure = dgmpp_character_get_structure(opaque) else {return nil}
			return DGMStructure(structure)
		}
		set {
			dgmpp_character_set_structure(opaque, newValue?.opaque)
		}
	}
	
	public func setSkillLevels(_ level: Int) {
		dgmpp_character_set_skill_levels(opaque, Int32(level))
	}
	
	public func add(_ implant: DGMImplant, replace: Bool = false) throws {
		guard dgmpp_character_add_implant_v2(opaque, implant.opaque, replace) else { throw DGMError.cannotFit(implant)}
	}
	
	public func add(_ booster: DGMBooster, replace: Bool = false) throws {
		guard dgmpp_character_add_booster_v2(opaque, booster.opaque, replace) else { throw DGMError.cannotFit(booster)}
	}
	
	public func remove(_ implant: DGMImplant) {
		dgmpp_character_remove_implant(opaque, implant.opaque)
	}

	public func remove(_ booster: DGMBooster) {
		dgmpp_character_remove_booster(opaque, booster.opaque)
	}
	
	public var implants: [DGMImplant] {
		return DGMArray<DGMImplant>(dgmpp_character_get_implants(opaque)).array
	}

	public var boosters: [DGMBooster] {
		return DGMArray<DGMBooster>(dgmpp_character_get_boosters(opaque)).array
	}

	public var skills: [DGMSkill] {
		return DGMArray<DGMSkill>(dgmpp_character_get_skills(opaque)).array
	}
	
	public var droneControlDistance: DGMMeter {
		return dgmpp_character_get_drone_control_distance(opaque)
	}

}
