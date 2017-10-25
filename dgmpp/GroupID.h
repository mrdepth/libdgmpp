#pragma once

//SELECT lower(substr(groupName, 1, 1)) || substr(replace(replace(groupName, '-', ''), ' ', ''), 2) || ' = ' || groupID || ','  FROM invGroups WHERE groupID IN (1, 899, 76, 365, 87, 916, 201, 208, 291, 379, 65, 52, 53, 74, 1029, 1030, 1063, 1027, 1028) order by groupID

namespace dgmpp {
	enum class GroupID: int {
		none = 0,
		
		character = 1,
		warpScrambler = 52,
		energyWeapon = 53,
		stasisWeb = 65,
		hybridWeapon = 74,
		capacitorBooster = 76,
		capacitorBoosterCharge = 87,
		eCM = 201,
		sensorDampener = 208,
		weaponDisruptor = 291,
		controlTower = 365,
		targetPainter = 379,
		warpDisruptFieldGenerator = 899,
		naniteRepairPaste = 916,
		commandCenters = 1027,
		processors = 1028,
		storageFacilities = 1029,
		spaceports = 1030,
		extractorControlUnits = 1063
	};
}
		

