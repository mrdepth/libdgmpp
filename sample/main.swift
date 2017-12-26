//
//  main.swift
//  dgmppDemo
//
//  Created by Artem Shimanski on 12.12.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

import Foundation
import Dgmpp

do {
	let gang = try DGMGang()
	let pilot = try DGMCharacter()
	gang.add(pilot)
	pilot.setSkillLevels(5)
	let dominix = try DGMShip(typeID: 645)
	pilot.ship = dominix
	dominix.modules(slot: .hi)
	
	print("\(dominix.hitPoints.shield)")
	print(dominix.attributes.map {"\($0.attributeID): \($0.value)"}.joined(separator: "\n"))
	
	
}
catch _ {
	
}

