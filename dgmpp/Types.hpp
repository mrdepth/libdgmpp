#pragma once
#include "Type.hpp"
#include "Attributes.hpp"
#include "Effects.hpp"

namespace dgmpp2 {
	namespace SDE {
		constexpr const Type::MetaInfo types[] {
			{TypeID::corporation, GroupID::corporation, CategoryID::owner, {
			},{
			},
			{
			}},
			{TypeID::region, GroupID::region, CategoryID::celestial, {
				{attributes[119], 1}, //volume
			},{
			},
			{
			}},
			{TypeID::constellation, GroupID::constellation, CategoryID::celestial, {
				{attributes[119], 1}, //volume
			},{
			},
			{
			}},
			{TypeID::solarSystem, GroupID::solarSystem, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[120], 5e+12}, //radius
			},{
			},
			{
			}},
			{TypeID::sunG5Yellow, GroupID::sun, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+18}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::sunK7Orange, GroupID::sun, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+18}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::sunK5RedGiant, GroupID::sun, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+18}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::sunB0Blue, GroupID::sun, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+18}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::sunF0White, GroupID::sun, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+18}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::planetTemperate, GroupID::planet, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+35}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::planetIce, GroupID::planet, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+35}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::planetGas, GroupID::planet, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+35}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::moon, GroupID::moon, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+35}, //mass
				{attributes[120], 10000}, //radius
			},{
			},
			{
			}},
			{TypeID::asteroidBelt, GroupID::asteroidBelt, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+35}, //mass
			},{
			},
			{
			}},
			{TypeID::stargateCaldariSystem, GroupID::stargate, CategoryID::celestial, {
				{attributes[153], 1}, //raceID
				{attributes[119], 1e+07}, //volume
				{attributes[2], 1e+11}, //mass
				{attributes[120], 3532}, //radius
			},{
			},
			{
			}},
			{TypeID::stargateAmarrConstellation, GroupID::stargate, CategoryID::celestial, {
				{attributes[153], 4}, //raceID
				{attributes[119], 1e+08}, //volume
				{attributes[2], 1e+11}, //mass
				{attributes[120], 2323}, //radius
			},{
			},
			{
			}},
			{TypeID::cargoContainer, GroupID::cargoContainer, CategoryID::celestial, {
				{attributes[20], 27500}, //capacity
				{attributes[119], 27500}, //volume
				{attributes[2], 10000}, //mass
				{attributes[120], 14}, //radius
				{attributes[5], 500}, //hp
				{attributes[451], 1}, //structureUniformity
				{attributes[474], 5000}, //signatureRadius
			},{
			},
			{
			}},
			{TypeID::ring, GroupID::ring, CategoryID::celestial, {
				{attributes[119], 1}, //volume
				{attributes[2], 1e+35}, //mass
				{attributes[120], 4.5e+06}, //radius
			},{
			},
			{
			}},
			{TypeID::corpseMale, GroupID::biomass, CategoryID::celestial, {
				{attributes[119], 2}, //volume
				{attributes[2], 80}, //mass
				{attributes[120], 1}, //radius
				{attributes[5], 10}, //hp
				{attributes[474], 50}, //signatureRadius
			},{
			},
			{
			}},
			{TypeID::credits, GroupID::money, CategoryID::material, {
			},{
			},
			{
			}},
			{TypeID::faction, GroupID::faction, CategoryID::owner, {
			},{
			},
			{
			}},
			{TypeID::tritanium, GroupID::mineral, CategoryID::material, {
				{attributes[119], 0.01}, //volume
			},{
			},
			{
			}},
			{TypeID::pyerite, GroupID::mineral, CategoryID::material, {
				{attributes[119], 0.01}, //volume
			},{
			},
			{
			}},
			{TypeID::mexallon, GroupID::mineral, CategoryID::material, {
				{attributes[119], 0.01}, //volume
			},{
			},
			{
			}},
			{TypeID::isogen, GroupID::mineral, CategoryID::material, {
				{attributes[119], 0.01}, //volume
			},{
			},
			{
			}},
			{TypeID::nocxium, GroupID::mineral, CategoryID::material, {
				{attributes[119], 0.01}, //volume
			},{
			},
			{
			}},
			{TypeID::zydrine, GroupID::mineral, CategoryID::material, {
				{attributes[119], 0.01}, //volume
			},{
			},
			{
			}},
			{TypeID::megacyte, GroupID::mineral, CategoryID::material, {
				{attributes[119], 0.01}, //volume
			},{
			},
			{
			}},
			{TypeID::garbage, GroupID::general, CategoryID::commodity, {
				{attributes[119], 0.25}, //volume
				{attributes[2], 2500}, //mass
			},{
			},
			{
			}},
			{TypeID::spicedWine, GroupID::general, CategoryID::commodity, {
				{attributes[119], 0.5}, //volume
				{attributes[2], 500}, //mass
			},{
			},
			{
			}},
			{TypeID::antibiotics, GroupID::general, CategoryID::commodity, {
				{attributes[119], 0.2}, //volume
				{attributes[2], 5}, //mass
			},{
			},
			{
			}},
			{TypeID::enrichedUranium, GroupID::refinedCommodities, CategoryID::planetaryCommodities, {
				{attributes[119], 1.5}, //volume
				{attributes[1415], 7200}, //importTaxMultiplier
				{attributes[1416], 7200}, //exportTaxMultiplier
			},{
			},
			{
			}},
			{TypeID::frozenPlantSeeds, GroupID::frozen, CategoryID::commodity, {
				{attributes[119], 0.5}, //volume
				{attributes[2], 400}, //mass
			},{
			},
			{
			}},
			{TypeID::carbonizedLeadS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 1}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 4.08228e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.6}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::nuclearS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 4}, //explosiveDamage
				{attributes[78], 1}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 4.08407e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.4}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::protonS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 3}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 2}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 2.7723e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.2}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::depletedUraniumS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 3}, //explosiveDamage
				{attributes[78], 2}, //kineticDamage
				{attributes[79], 3}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 3.95785e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.2}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::titaniumSabotS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 2}, //explosiveDamage
				{attributes[78], 6}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 6.38035e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.2}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.875}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::fusionS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 10}, //explosiveDamage
				{attributes[78], 2}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.20211e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.75}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::phasedPlasmaS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 2}, //kineticDamage
				{attributes[79], 10}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 3.30402e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.625}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::EMPS, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 9}, //emDamage
				{attributes[77], 2}, //explosiveDamage
				{attributes[78], 1}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.67635e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.5}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::carbonizedLeadM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 2}, //explosiveDamage
				{attributes[78], 8}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 4.08228e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.6}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::nuclearM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 8}, //explosiveDamage
				{attributes[78], 2}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 4.08407e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.4}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::protonM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 1}, //mass
				{attributes[76], 6}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 2.7723e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.2}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::depletedUraniumM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 1}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 6}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 6}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 4.61244e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.2}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::titaniumSabotM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 1}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 4}, //explosiveDamage
				{attributes[78], 12}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 6.38035e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.2}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.875}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::fusionM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 1}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 20}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.20211e+07}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.75}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::phasedPlasmaM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 1}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 20}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 3.30402e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.625}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::EMPM, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 1}, //mass
				{attributes[76], 18}, //emDamage
				{attributes[77], 4}, //explosiveDamage
				{attributes[78], 2}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.67635e+07}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.5}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::carbonizedLeadL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 4}, //explosiveDamage
				{attributes[78], 16}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 4.08228e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.6}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::nuclearL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 16}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 4.08407e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.4}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::protonL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 12}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 8}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 4.08663e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.05}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.2}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::depletedUraniumL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 12}, //explosiveDamage
				{attributes[78], 8}, //kineticDamage
				{attributes[79], 12}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 4.61244e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.2}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::titaniumSabotL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 8}, //explosiveDamage
				{attributes[78], 24}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 6.38035e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1.2}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.875}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::fusionL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 40}, //explosiveDamage
				{attributes[78], 8}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.20211e+07}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.75}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::phasedPlasmaL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 8}, //kineticDamage
				{attributes[79], 40}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 3.30402e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.625}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::EMPL, GroupID::projectileAmmo, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 36}, //emDamage
				{attributes[77], 8}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.67635e+07}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 55}, //launcherGroup
				{attributes[193], 1}, //trackingSpeedMultiplier
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.5}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[226]}, //ammoTrackingMultiplier
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::mjolnirCruiseMissile, GroupID::cruiseMissile, CategoryID::charge, {
				{attributes[119], 0.05}, //volume
				{attributes[2], 1250}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 240}, //hp
				{attributes[19], 4700}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 0.8}, //emDamageResonance
				{attributes[76], 375}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 506}, //launcherGroup
				{attributes[140], 3326}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 14000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 69}, //aoeVelocity
				{attributes[565], 330}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.882}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::cruiseMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::scourgeCruiseMissile, GroupID::cruiseMissile, CategoryID::charge, {
				{attributes[119], 0.05}, //volume
				{attributes[2], 1250}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 240}, //hp
				{attributes[19], 4700}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 0.8}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 375}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 506}, //launcherGroup
				{attributes[140], 3326}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 14000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 69}, //aoeVelocity
				{attributes[565], 330}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.882}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::cruiseMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::infernoCruiseMissile, GroupID::cruiseMissile, CategoryID::charge, {
				{attributes[119], 0.05}, //volume
				{attributes[2], 1250}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 240}, //hp
				{attributes[19], 4700}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 0.8}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 375}, //thermalDamage
				{attributes[97], 506}, //launcherGroup
				{attributes[140], 3326}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 14000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 69}, //aoeVelocity
				{attributes[565], 330}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.882}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::cruiseMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::novaCruiseMissile, GroupID::cruiseMissile, CategoryID::charge, {
				{attributes[119], 0.05}, //volume
				{attributes[2], 1250}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 240}, //hp
				{attributes[19], 4700}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 0.8}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 375}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 506}, //launcherGroup
				{attributes[140], 3326}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 14000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 69}, //aoeVelocity
				{attributes[565], 330}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.882}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::cruiseMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::novaHeavyMissile, GroupID::heavyMissile, CategoryID::charge, {
				{attributes[119], 0.03}, //volume
				{attributes[2], 1000}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 120}, //hp
				{attributes[19], 4300}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 0.8}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 142}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 510}, //launcherGroup
				{attributes[140], 3324}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 6500}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 81}, //aoeVelocity
				{attributes[565], 140}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.682}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::heavyMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::mjolnirHeavyMissile, GroupID::heavyMissile, CategoryID::charge, {
				{attributes[119], 0.03}, //volume
				{attributes[2], 1000}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 120}, //hp
				{attributes[19], 4300}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 0.8}, //emDamageResonance
				{attributes[76], 142}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 510}, //launcherGroup
				{attributes[140], 3324}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 6500}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 81}, //aoeVelocity
				{attributes[565], 140}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.682}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::heavyMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::infernoHeavyMissile, GroupID::heavyMissile, CategoryID::charge, {
				{attributes[119], 0.03}, //volume
				{attributes[2], 1000}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 120}, //hp
				{attributes[19], 4300}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 0.8}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 142}, //thermalDamage
				{attributes[97], 510}, //launcherGroup
				{attributes[140], 3324}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 6500}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 81}, //aoeVelocity
				{attributes[565], 140}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.682}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::heavyMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::scourgeHeavyMissile, GroupID::heavyMissile, CategoryID::charge, {
				{attributes[119], 0.03}, //volume
				{attributes[2], 1000}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 120}, //hp
				{attributes[19], 4300}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 0.8}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 142}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 510}, //launcherGroup
				{attributes[140], 3324}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 6500}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 81}, //aoeVelocity
				{attributes[565], 140}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.682}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::heavyMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::scourgeLightMissile, GroupID::lightMissile, CategoryID::charge, {
				{attributes[119], 0.015}, //volume
				{attributes[2], 700}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 60}, //hp
				{attributes[19], 3750}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 0.8}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 83}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 509}, //launcherGroup
				{attributes[140], 3321}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 5000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 170}, //aoeVelocity
				{attributes[565], 40}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.604}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::lightMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::infernoLightMissile, GroupID::lightMissile, CategoryID::charge, {
				{attributes[119], 0.015}, //volume
				{attributes[2], 700}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 60}, //hp
				{attributes[19], 3750}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 0.8}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 83}, //thermalDamage
				{attributes[97], 509}, //launcherGroup
				{attributes[140], 3321}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 5000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 170}, //aoeVelocity
				{attributes[565], 40}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.604}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::lightMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::mjolnirLightMissile, GroupID::lightMissile, CategoryID::charge, {
				{attributes[119], 0.015}, //volume
				{attributes[2], 700}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 60}, //hp
				{attributes[19], 3750}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 1}, //explosiveDamageResonance
				{attributes[75], 0.8}, //emDamageResonance
				{attributes[76], 83}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 509}, //launcherGroup
				{attributes[140], 3321}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 5000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 170}, //aoeVelocity
				{attributes[565], 40}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.604}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::lightMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::novaLightMissile, GroupID::lightMissile, CategoryID::charge, {
				{attributes[119], 0.015}, //volume
				{attributes[2], 700}, //mass
				{attributes[120], 300}, //radius
				{attributes[5], 60}, //hp
				{attributes[19], 3750}, //maxVelocity
				{attributes[39], 0.000144498}, //agility
				{attributes[70], 35}, //detonationRange
				{attributes[71], 1}, //kineticDamageResonance
				{attributes[72], 1}, //thermalDamageResonance
				{attributes[73], 0.8}, //explosiveDamageResonance
				{attributes[75], 1}, //emDamageResonance
				{attributes[76], 0}, //emDamage
				{attributes[77], 83}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[97], 509}, //launcherGroup
				{attributes[140], 3321}, //requiredSkill1
				{attributes[141], 3319}, //requiredSkill2
				{attributes[225], 1}, //requiredSkill1Level
				{attributes[226], 1}, //requiredSkill2Level
				{attributes[229], 5000}, //explosionDelay
				{attributes[354], 1}, //techLevel
				{attributes[451], 1}, //structureUniformity
				{attributes[546], 0}, //metaLevel
				{attributes[555], 1}, //aimedLaunch
				{attributes[564], 170}, //aoeVelocity
				{attributes[565], 40}, //aoeCloudSize
				{attributes[566], 1500}, //aoeFalloff
				{attributes[1161], 0.604}, //aoeDamageReductionFactor
			},{
				{effects[1]}, //missileLaunching
			},
			{TypeID::lightMissiles, TypeID::missileLauncherOperation, 
			}},
			{TypeID::ironChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 3}, //kineticDamage
				{attributes[79], 2}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 5.20284e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -30}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.6}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::tungstenChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 2}, //thermalDamage
				{attributes[80], 1.4}, //weaponRangeMultiplier
				{attributes[84], 5.80188e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -27}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.4}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::iridiumChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 4}, //kineticDamage
				{attributes[79], 3}, //thermalDamage
				{attributes[80], 1.2}, //weaponRangeMultiplier
				{attributes[84], 6.20149e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -24}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.2}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::leadChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 5}, //kineticDamage
				{attributes[79], 3}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 8.30116e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -50}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::thoriumChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 5}, //kineticDamage
				{attributes[79], 4}, //thermalDamage
				{attributes[80], 0.875}, //weaponRangeMultiplier
				{attributes[84], 1.07273e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -40}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.875}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::uraniumChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 6}, //kineticDamage
				{attributes[79], 4}, //thermalDamage
				{attributes[80], 0.75}, //weaponRangeMultiplier
				{attributes[84], 1.18358e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -8}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.75}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::plutoniumChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 6}, //kineticDamage
				{attributes[79], 5}, //thermalDamage
				{attributes[80], 0.625}, //weaponRangeMultiplier
				{attributes[84], 1.24871e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -5}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.625}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::antimatterChargeS, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0025}, //volume
				{attributes[2], 0.01}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 7}, //kineticDamage
				{attributes[79], 5}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.67641e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], 0}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.5}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::ironChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 6}, //kineticDamage
				{attributes[79], 4}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 5.20284e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -30}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.6}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::tungstenChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 8}, //kineticDamage
				{attributes[79], 4}, //thermalDamage
				{attributes[80], 1.4}, //weaponRangeMultiplier
				{attributes[84], 5.80188e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -27}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.4}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::iridiumChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 8}, //kineticDamage
				{attributes[79], 6}, //thermalDamage
				{attributes[80], 1.2}, //weaponRangeMultiplier
				{attributes[84], 6.20149e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -24}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.2}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::leadChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 10}, //kineticDamage
				{attributes[79], 6}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 8.30116e+06}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -50}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::thoriumChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 10}, //kineticDamage
				{attributes[79], 8}, //thermalDamage
				{attributes[80], 0.875}, //weaponRangeMultiplier
				{attributes[84], 1.07273e+07}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -40}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.875}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::uraniumChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 12}, //kineticDamage
				{attributes[79], 8}, //thermalDamage
				{attributes[80], 0.75}, //weaponRangeMultiplier
				{attributes[84], 1.18358e+07}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -8}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.75}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::plutoniumChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 12}, //kineticDamage
				{attributes[79], 10}, //thermalDamage
				{attributes[80], 0.625}, //weaponRangeMultiplier
				{attributes[84], 1.24871e+07}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -5}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.625}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::antimatterChargeM, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.0125}, //volume
				{attributes[2], 0.05}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 14}, //kineticDamage
				{attributes[79], 10}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.67641e+07}, //mainColor
				{attributes[88], 2}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], 0}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.5}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::ironChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 12}, //kineticDamage
				{attributes[79], 8}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 5.20284e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -30}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.6}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::tungstenChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 16}, //kineticDamage
				{attributes[79], 8}, //thermalDamage
				{attributes[80], 1.4}, //weaponRangeMultiplier
				{attributes[84], 5.80188e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -27}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.4}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::iridiumChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 16}, //kineticDamage
				{attributes[79], 12}, //thermalDamage
				{attributes[80], 1.2}, //weaponRangeMultiplier
				{attributes[84], 6.20149e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -24}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.2}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::leadChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 20}, //kineticDamage
				{attributes[79], 12}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 8.30116e+06}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -50}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::thoriumChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 20}, //kineticDamage
				{attributes[79], 16}, //thermalDamage
				{attributes[80], 0.875}, //weaponRangeMultiplier
				{attributes[84], 1.07273e+07}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -40}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.875}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::uraniumChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 24}, //kineticDamage
				{attributes[79], 16}, //thermalDamage
				{attributes[80], 0.75}, //weaponRangeMultiplier
				{attributes[84], 1.18358e+07}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -8}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.75}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::plutoniumChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 24}, //kineticDamage
				{attributes[79], 20}, //thermalDamage
				{attributes[80], 0.625}, //weaponRangeMultiplier
				{attributes[84], 1.24871e+07}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], -5}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.625}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::antimatterChargeL, GroupID::hybridCharge, CategoryID::charge, {
				{attributes[119], 0.025}, //volume
				{attributes[2], 0.1}, //mass
				{attributes[120], 10}, //radius
				{attributes[76], 0}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 28}, //kineticDamage
				{attributes[79], 20}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.67641e+07}, //mainColor
				{attributes[88], 3}, //chargeSize
				{attributes[97], 74}, //launcherGroup
				{attributes[265], 0}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.5}, //entityFlyRangeMultiplier
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
			},
			{
			}},
			{TypeID::radioS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 5}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 0}, //thermalDamage
				{attributes[80], 1.6}, //weaponRangeMultiplier
				{attributes[84], 2.83386e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], -15}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.6}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::microwaveS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 4}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 2}, //thermalDamage
				{attributes[80], 1.4}, //weaponRangeMultiplier
				{attributes[84], 3.10595e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], -25}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.4}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::infraredS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 5}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 2}, //thermalDamage
				{attributes[80], 1.2}, //weaponRangeMultiplier
				{attributes[84], 5.20924e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], -35}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1.2}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::standardS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 5}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 3}, //thermalDamage
				{attributes[80], 1}, //weaponRangeMultiplier
				{attributes[84], 5.21586e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], -45}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 1}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::ultravioletS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 6}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 3}, //thermalDamage
				{attributes[80], 0.875}, //weaponRangeMultiplier
				{attributes[84], 8.03901e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], -35}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.875}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::xrayS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 6}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 4}, //thermalDamage
				{attributes[80], 0.75}, //weaponRangeMultiplier
				{attributes[84], 9.20228e+06}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], -25}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.75}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::gammaS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 7}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 4}, //thermalDamage
				{attributes[80], 0.625}, //weaponRangeMultiplier
				{attributes[84], 1.67464e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], -15}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.625}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
			{TypeID::multifrequencyS, GroupID::frequencyCrystal, CategoryID::charge, {
				{attributes[119], 1}, //volume
				{attributes[2], 1}, //mass
				{attributes[1], 0}, //damage
				{attributes[5], 1}, //hp
				{attributes[76], 7}, //emDamage
				{attributes[77], 0}, //explosiveDamage
				{attributes[78], 0}, //kineticDamage
				{attributes[79], 5}, //thermalDamage
				{attributes[80], 0.5}, //weaponRangeMultiplier
				{attributes[84], 1.16467e+07}, //mainColor
				{attributes[88], 1}, //chargeSize
				{attributes[97], 53}, //launcherGroup
				{attributes[265], 0}, //capNeedBonus
				{attributes[354], 1}, //techLevel
				{attributes[528], 0}, //baseShieldDamage
				{attributes[529], 0}, //baseArmorDamage
				{attributes[680], 0.5}, //entityFlyRangeMultiplier
				{attributes[684], 1}, //crystalVolatilityChance
				{attributes[685], 0.00025}, //crystalVolatilityDamage
				{attributes[687], 0}, //crystalsGetDamaged
			},{
				{effects[223]}, //ammoInfluenceRange
				{effects[281]}, //ammoInfluenceCapNeed
				{effects[399]}, //ammoInfluenceEntityFlyRange
			},
			{
			}},
		};
	}
}
