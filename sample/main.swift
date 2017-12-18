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
	let gang = DGMGang()
	let pilot = DGMCharacter()
	gang.add(pilot)
	pilot.setSkillLevels(5)
	let dominix = try DGMShip(typeID: 645)
	pilot.ship = dominix
	
	print("\(dominix.hitPoints.shield)")
	print(dominix.attributes.map {"\($0.attributeID): \($0.value)"}.joined(separator: "\n"))
}
catch _ {
	
}
