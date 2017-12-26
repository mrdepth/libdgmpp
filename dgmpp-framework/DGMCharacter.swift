//
//  DGMCharacter.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMImplant: DGMType {
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_implant_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}

	public var slot: Int {
		return Int(dgmpp_implant_get_slot(handle))
	}
}

public class DGMBooster: DGMType {
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_booster_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}

	public var slot: Int {
		return Int(dgmpp_booster_get_slot(handle))
	}
}

public class DGMSkill: DGMType {
	
	public var level: Int {
		get {
			return Int(dgmpp_skill_get_level(handle))
		}
		set {
			dgmpp_skill_set_level(handle, Int32(newValue))
		}
	}
	
}

public class DGMCharacter: DGMType {
	
	public convenience init() throws {
		self.init(dgmpp_character_create()!, owned: true)
	}

	public var name: String {
		get {
			return String(cString: dgmpp_character_get_name(handle));
		}
		set {
			guard let string = newValue.cString(using: .utf8) else {return}
			dgmpp_character_set_name(handle, string)
		}
	}

	
	public var ship: DGMShip? {
		get {
			guard let ship = dgmpp_character_get_ship(handle) else {return nil}
			return DGMShip(ship)
		}
		set {
			dgmpp_character_set_ship(handle, newValue?.handle)
		}
	}
	
	public var structure: DGMStructure? {
		get {
			guard let structure = dgmpp_character_get_structure(handle) else {return nil}
			return DGMStructure(structure)
		}
		set {
			dgmpp_character_set_structure(handle, newValue?.handle)
		}
	}
	
	public func setSkillLevels(_ level: Int) {
		dgmpp_character_set_skill_levels(handle, Int32(level))
	}
	
	public func add(_ implant: DGMImplant, replace: Bool = false) throws {
		guard dgmpp_character_add_implant_v2(handle, implant.handle, replace) else { throw DGMError.cannotFit(implant)}
	}
	
	public func add(_ booster: DGMBooster, replace: Bool = false) throws {
		guard dgmpp_character_add_booster_v2(handle, booster.handle, replace) else { throw DGMError.cannotFit(booster)}
	}
	
	public func remove(_ implant: DGMImplant) {
		dgmpp_character_remove_implant(handle, implant.handle)
	}

	public func remove(_ booster: DGMBooster) {
		dgmpp_character_remove_booster(handle, booster.handle)
	}
	
	public var implants: [DGMImplant] {
		return DGMArray<DGMImplant>(dgmpp_character_copy_implants(handle)).array
	}

	public var boosters: [DGMBooster] {
		return DGMArray<DGMBooster>(dgmpp_character_copy_boosters(handle)).array
	}

	public var skills: [DGMSkill] {
		return DGMArray<DGMSkill>(dgmpp_character_copy_skills(handle)).array
	}
	
	public var droneControlDistance: DGMMeter {
		return dgmpp_character_get_drone_control_distance(handle)
	}

}
