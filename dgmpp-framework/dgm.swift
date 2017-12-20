//
//  dgm.swift
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

import Foundation

extension DGMModule.State {
	init?(_ state: DGMPP_MODULE_STATE) {
		guard let value = DGMModule.State(rawValue: Int(state.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_MODULE_STATE {
	init(_ state: DGMModule.State) {
		self = DGMPP_MODULE_STATE(Int32(state.rawValue))
	}
}

extension DGMModule.Slot {
	init?(_ slot: DGMPP_MODULE_SLOT) {
		guard let value = DGMModule.Slot(rawValue: Int(slot.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_MODULE_SLOT {
	init(_ slot: DGMModule.Slot) {
		self = DGMPP_MODULE_SLOT(Int32(slot.rawValue))
	}
}

extension DGMModule.Hardpoint {
	init?(_ hardpoint: DGMPP_MODULE_HARDPOINT) {
		guard let value = DGMModule.Hardpoint(rawValue: Int(hardpoint.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_MODULE_HARDPOINT {
	init(_ hardpoint: DGMModule.Hardpoint) {
		self = DGMPP_MODULE_HARDPOINT(UInt32(hardpoint.rawValue))
	}
}

extension DGMDrone.Squadron {
	init?(_ squadron: DGMPP_DRONE_SQUADRON) {
		guard let value = DGMDrone.Squadron(rawValue: Int(squadron.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_DRONE_SQUADRON {
	init(_ squadron: DGMDrone.Squadron) {
		self = DGMPP_DRONE_SQUADRON(UInt32(squadron.rawValue))
	}
}

extension DGMCharge.Size {
	init?(_ size: DGMPP_CHARGE_SIZE) {
		guard let value = DGMCharge.Size(rawValue: Int(size.rawValue)) else {return nil}
		self = value
	}
}

extension DGMShip.ScanType {
	init?(_ scanType: DGMPP_SCAN_TYPE) {
		guard let value = DGMShip.ScanType(rawValue: Int(scanType.rawValue)) else {return nil}
		self = value
	}
}

extension DGMShip.RigSize {
	init?(_ rigSize: DGMPP_RIG_SIZE) {
		guard let value = DGMShip.RigSize(rawValue: Int(rigSize.rawValue)) else {return nil}
		self = value
	}
}

extension DGMRaceID {
	init?(_ raceID: DGMPP_RACE_ID) {
		guard let value = DGMRaceID(rawValue: Int(raceID.rawValue)) else {return nil}
		self = value
	}
}

extension DGMCommodity.Tier {
	init?(_ tier: DGMPP_COMMODITY_TIER) {
		guard let value = DGMCommodity.Tier(rawValue: Int(tier.rawValue)) else {return nil}
		self = value
	}
}

