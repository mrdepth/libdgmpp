//
//  DGMGang.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMGang: DGMType, Codable {
	
	public convenience init() throws {
		self.init(dgmpp_gang_create()!)
	}

	public convenience init(_ other: DGMGang) {
		self.init(dgmpp_gang_copy(other.handle))
	}

	public func add(_ pilot: DGMCharacter) {
        willChange()
		dgmpp_gang_add_pilot(handle, pilot.handle)
	}
	
	public func remove(_ pilot: DGMCharacter) {
        willChange()
		dgmpp_gang_remove_pilot(handle, pilot.handle)
	}
	
	public var pilots: [DGMCharacter] {
		return DGMArray<DGMCharacter>(dgmpp_gang_copy_pilots(handle)).array
	}
	
	public var factorReload: Bool {
		get {
			return dgmpp_gang_get_factor_reload(handle) != 0
		}
		set {
			willChange()
			dgmpp_gang_set_factor_reload(handle, newValue ? 1 : 0)
		}
	}
	
	public var area: DGMArea? {
		get {
			guard let area = dgmpp_gang_copy_area(handle) else {return nil}
            return DGMType.type(area) as? DGMArea
		}
		set {
            willChange()
			dgmpp_gang_set_area(handle, newValue?.handle)
		}
	}
    
    override func sendChange() {
        super.sendChange()
        pilots.forEach{$0.sendChange()}
    }

    public convenience required init(from decoder: Decoder) throws {
        try self.init()
        let container = try decoder.container(keyedBy: CodingKeys.self)
        let pilots = try container.decode([DGMCharacter].self, forKey: .pilots)
        for pilot in pilots {
            add(pilot)
        }
        area = try container.decodeIfPresent(DGMArea.self, forKey: .area)
        let links = try container.decode([Int: Int].self, forKey: .targets)
        
        let pilotsMap = Dictionary(pilots.map{($0.identifier, $0)}) {a, _ in a}
        
        for pilot in pilots {
            for module in pilot.ship?.modules ?? [] {
                guard let link = links[module.identifier] else {continue}
                module.target = pilotsMap[link]?.ship
            }
            for drone in pilot.ship?.drones ?? [] {
                guard let link = links[drone.identifier] else {continue}
                drone.target = pilotsMap[link]?.ship
            }
        }
    }
    
    public func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(pilots, forKey: .pilots)
        try container.encodeIfPresent(area, forKey: .area)
        
        var links = [Int: Int]()
        for pilot in pilots {
            for module in pilot.ship?.modules ?? [] {
                if let target = module.target?.parent {
                    links[module.identifier] = target.identifier
                }
            }
            for drone in pilot.ship?.drones ?? [] {
                if let target = drone.target?.parent {
                    links[drone.identifier] = target.identifier
                }
            }
        }

        try container.encode(links, forKey: .targets)
    }
    
    enum CodingKeys: String, CodingKey {
        case pilots
        case area
        case targets
    }

}
