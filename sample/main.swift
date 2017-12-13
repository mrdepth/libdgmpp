//
//  main.swift
//  dgmppDemo
//
//  Created by Artem Shimanski on 12.12.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

import Foundation
import Dgm

do {
	let gang = DGMGang()
	let pilot = DGMCharacter()
	pilot.setSkillLevels(5)
	gang.addPilot(pilot)
	
	let dominix = try DGMShip(typeID: 645)
	pilot.ship = dominix
}
catch _ {
	
}
