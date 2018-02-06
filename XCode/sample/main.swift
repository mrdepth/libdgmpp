//
//  main.swift
//  dgmppDemo
//
//  Created by Artem Shimanski on 12.12.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

import Foundation
import Dgmpp

struct Dump: Codable {
	struct Fit: Codable {
		var canonicalName: String
	}
	var data: [Fit]
}

do {
	
//	let dump = try JSONDecoder().decode(Dump.self, from: Data(contentsOf: URL(fileURLWithPath: "/Users/shimanski/Downloads/Fits.json")))
	
//	let hashes = try dump.data.enumerated().flatMap { (n, i) -> Int? in
//		guard let hash = try? DGMShip(string: i.canonicalName).hashValue else {return nil}
//		if n % 1000 == 0 {
//			print("\(n)")
//		}
//		return hash
//
//	}
//	var set = Set(hashes)
//	print("\(hashes.count == set.count)")
	
	
	let gang = try DGMGang()
	let pilot = try DGMCharacter()
	gang.add(pilot)
	pilot.setSkillLevels(5)
	
	let ship = try DGMShip(uniformString: "587|438::1;448::1;1183::1;1306::1;2048::1;2881:12625:3;4025::1;31668::1;31680::1|2488:10")
	pilot.ship = ship
	
	let form = ship.uniformString
	
	let d = try JSONEncoder().encode(pilot)
	let s = String(data: d, encoding: .utf8)
	print(s!)
	
	let ship2 = try JSONDecoder().decode(DGMCharacter.self, from: d)
	
	let d2 = try JSONEncoder().encode(ship2)
	let s2 = String(data: d, encoding: .utf8)

	print("\(s == s2)")
}
catch  {
	print("\(error)")
}

