#pragma once

namespace dgmpp {
	enum class CategoryID: int {
		none = 0,
		owner = 1,
		celestial = 2,
		material = 4,
		ship = 6,
		module = 7,
		charge = 8,
		skill = 16,
		drone = 18,
		implant = 20,
		starbase = 23,
		subsystem = 32,
		planetaryInteraction = 41,
		planetaryResources = 42,
		planetaryCommodities = 43,
		structure = 65,
		structureModule = 66,
		fighter = 87
	};
}