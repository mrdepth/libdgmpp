#pragma once
#include "MetaInfo.hpp"

namespace dgmpp {
	namespace SDE {
		namespace Commodities {
			constexpr MetaInfo::Commodity enrichedUranium = {TypeID::enrichedUranium, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity microorganisms = {TypeID::microorganisms, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity baseMetals = {TypeID::baseMetals, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity aqueousLiquids = {TypeID::aqueousLiquids, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity nobleMetals = {TypeID::nobleMetals, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity heavyMetals = {TypeID::heavyMetals, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity plankticColonies = {TypeID::plankticColonies, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity complexOrganisms = {TypeID::complexOrganisms, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity carbonCompounds = {TypeID::carbonCompounds, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity autotrophs = {TypeID::autotrophs, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity nonCSCrystals = {TypeID::nonCSCrystals, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity felsicMagma = {TypeID::felsicMagma, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity suspendedPlasma = {TypeID::suspendedPlasma, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity ionicSolutions = {TypeID::ionicSolutions, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity nobleGas = {TypeID::nobleGas, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity reactiveGas = {TypeID::reactiveGas, MetaInfo::Commodity::Tier::raw, 0.01};
			constexpr MetaInfo::Commodity supertensilePlastics = {TypeID::supertensilePlastics, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity oxides = {TypeID::oxides, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity testCultures = {TypeID::testCultures, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity polyaramids = {TypeID::polyaramids, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity microfiberShielding = {TypeID::microfiberShielding, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity waterCooledCPU = {TypeID::waterCooledCPU, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity biocells = {TypeID::biocells, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity condensates = {TypeID::condensates, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity cameraDrones = {TypeID::cameraDrones, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity syntheticSynapses = {TypeID::syntheticSynapses, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity gelMatrixBiopaste = {TypeID::gelMatrixBiopaste, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity supercomputers = {TypeID::supercomputers, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity smartfabUnits = {TypeID::smartfabUnits, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity nuclearReactors = {TypeID::nuclearReactors, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity neocoms = {TypeID::neocoms, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity biotechResearchReports = {TypeID::biotechResearchReports, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity industrialExplosives = {TypeID::industrialExplosives, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity hermeticMembranes = {TypeID::hermeticMembranes, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity hazmatDetectionSystems = {TypeID::hazmatDetectionSystems, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity cryoprotectantSolution = {TypeID::cryoprotectantSolution, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity plasmoids = {TypeID::plasmoids, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity electrolytes = {TypeID::electrolytes, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity oxidizingCompound = {TypeID::oxidizingCompound, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity bacteria = {TypeID::bacteria, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity proteins = {TypeID::proteins, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity biofuels = {TypeID::biofuels, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity industrialFibers = {TypeID::industrialFibers, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity reactiveMetals = {TypeID::reactiveMetals, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity preciousMetals = {TypeID::preciousMetals, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity toxicMetals = {TypeID::toxicMetals, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity chiralStructures = {TypeID::chiralStructures, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity nanites = {TypeID::nanites, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity broadcastNode = {TypeID::broadcastNode, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity integrityResponseDrones = {TypeID::integrityResponseDrones, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity nanoFactory = {TypeID::nanoFactory, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity organicMortarApplicators = {TypeID::organicMortarApplicators, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity recursiveComputingModule = {TypeID::recursiveComputingModule, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity selfHarmonizingPowerCore = {TypeID::selfHarmonizingPowerCore, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity sterileConduits = {TypeID::sterileConduits, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity wetwareMainframe = {TypeID::wetwareMainframe, MetaInfo::Commodity::Tier::tier4, 100};
			constexpr MetaInfo::Commodity water = {TypeID::water, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity oxygen = {TypeID::oxygen, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity mechanicalParts = {TypeID::mechanicalParts, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity syntheticOil = {TypeID::syntheticOil, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity fertilizer = {TypeID::fertilizer, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity polytextiles = {TypeID::polytextiles, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity silicateGlass = {TypeID::silicateGlass, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity livestock = {TypeID::livestock, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity viralAgent = {TypeID::viralAgent, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity biomass = {TypeID::biomass, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity constructionBlocks = {TypeID::constructionBlocks, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity silicon = {TypeID::silicon, MetaInfo::Commodity::Tier::tier1, 0.38};
			constexpr MetaInfo::Commodity rocketFuel = {TypeID::rocketFuel, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity coolant = {TypeID::coolant, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity guidanceSystems = {TypeID::guidanceSystems, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity consumerElectronics = {TypeID::consumerElectronics, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity superconductors = {TypeID::superconductors, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity transmitter = {TypeID::transmitter, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity miniatureElectronics = {TypeID::miniatureElectronics, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity planetaryVehicles = {TypeID::planetaryVehicles, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity robotics = {TypeID::robotics, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity transcranialMicrocontrollers = {TypeID::transcranialMicrocontrollers, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity geneticallyEnhancedLivestock = {TypeID::geneticallyEnhancedLivestock, MetaInfo::Commodity::Tier::tier2, 1.5};
			constexpr MetaInfo::Commodity ukomiSuperconductors = {TypeID::ukomiSuperconductors, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity dataChips = {TypeID::dataChips, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity highTechTransmitters = {TypeID::highTechTransmitters, MetaInfo::Commodity::Tier::tier3, 6};
			constexpr MetaInfo::Commodity vaccines = {TypeID::vaccines, MetaInfo::Commodity::Tier::tier3, 6};
		}

		constexpr const MetaInfo::Commodity* commodities[] {
&Commodities::enrichedUranium, &Commodities::microorganisms, &Commodities::baseMetals, &Commodities::aqueousLiquids, &Commodities::nobleMetals, &Commodities::heavyMetals, &Commodities::plankticColonies, &Commodities::complexOrganisms, &Commodities::carbonCompounds, &Commodities::autotrophs, &Commodities::nonCSCrystals, &Commodities::felsicMagma, &Commodities::suspendedPlasma, &Commodities::ionicSolutions, &Commodities::nobleGas, &Commodities::reactiveGas, &Commodities::supertensilePlastics, &Commodities::oxides, &Commodities::testCultures, &Commodities::polyaramids, &Commodities::microfiberShielding, &Commodities::waterCooledCPU, &Commodities::biocells, &Commodities::condensates, &Commodities::cameraDrones, &Commodities::syntheticSynapses, &Commodities::gelMatrixBiopaste, &Commodities::supercomputers, &Commodities::smartfabUnits, &Commodities::nuclearReactors, &Commodities::neocoms, &Commodities::biotechResearchReports, &Commodities::industrialExplosives, &Commodities::hermeticMembranes, &Commodities::hazmatDetectionSystems, &Commodities::cryoprotectantSolution, &Commodities::plasmoids, &Commodities::electrolytes, &Commodities::oxidizingCompound, &Commodities::bacteria, &Commodities::proteins, &Commodities::biofuels, &Commodities::industrialFibers, &Commodities::reactiveMetals, &Commodities::preciousMetals, &Commodities::toxicMetals, &Commodities::chiralStructures, &Commodities::nanites, &Commodities::broadcastNode, &Commodities::integrityResponseDrones, &Commodities::nanoFactory, &Commodities::organicMortarApplicators, &Commodities::recursiveComputingModule, &Commodities::selfHarmonizingPowerCore, &Commodities::sterileConduits, &Commodities::wetwareMainframe, &Commodities::water, &Commodities::oxygen, &Commodities::mechanicalParts, &Commodities::syntheticOil, &Commodities::fertilizer, &Commodities::polytextiles, &Commodities::silicateGlass, &Commodities::livestock, &Commodities::viralAgent, &Commodities::biomass, &Commodities::constructionBlocks, &Commodities::silicon, &Commodities::rocketFuel, &Commodities::coolant, &Commodities::guidanceSystems, &Commodities::consumerElectronics, &Commodities::superconductors, &Commodities::transmitter, &Commodities::miniatureElectronics, &Commodities::planetaryVehicles, &Commodities::robotics, &Commodities::transcranialMicrocontrollers, &Commodities::geneticallyEnhancedLivestock, &Commodities::ukomiSuperconductors, &Commodities::dataChips, &Commodities::highTechTransmitters, &Commodities::vaccines, 		};
	}
}
