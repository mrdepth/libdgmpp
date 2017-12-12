//
//  main.swift
//  dgmppDemo
//
//  Created by Artem Shimanski on 12.12.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

import Foundation
import Dgm


let gang = DGMGang()
let pilot = DGMCharacter()
let ship = try! DGMShip(typeID: 645)
pilot.setSkillLevels(5)
gang.addPilot(pilot)
pilot.ship = ship

print("\(ship.supportedDroneCategories)")
