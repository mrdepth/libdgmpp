from utility import *

def patchMissilesDamage(env):
    addEffect(10000, 'characterDamageMissiles', EffectCategory.passive, False, False, env)
    addEffectGroup('Character', 'characterDamageMissiles', env)
    updateEffect('characterDamageMissiles', env, [OwnerRequiredSkillModifier(Domain.charID, 'Missile Launcher Operation', 'emDamage', Operation.postMul, 'missileDamageMultiplier'),
                                                  OwnerRequiredSkillModifier(Domain.charID, 'Missile Launcher Operation', 'explosiveDamage', Operation.postMul, 'missileDamageMultiplier'),
                                                  OwnerRequiredSkillModifier(Domain.charID, 'Missile Launcher Operation', 'kineticDamage', Operation.postMul, 'missileDamageMultiplier'),
                                                  OwnerRequiredSkillModifier(Domain.charID, 'Missile Launcher Operation', 'thermalDamage', Operation.postMul, 'missileDamageMultiplier')])

def patchTacticalDestroyer(name, env):
    addItemEffect('{} Defense Mode'.format(name), 'tacticalMode', env)
    addItemEffect('{} Sharpshooter Mode'.format(name), 'tacticalMode', env)
    addItemEffect('{} Propulsion Mode'.format(name), 'tacticalMode', env)
    addItemAttribute('{} Defense Mode'.format(name), 'canFitShipType1', getTypeID(name, env), env)
    addItemAttribute('{} Sharpshooter Mode'.format(name), 'canFitShipType1', getTypeID(name, env), env)
    addItemAttribute('{} Propulsion Mode'.format(name), 'canFitShipType1', getTypeID(name, env), env)
    addItemAttribute(name, 'tacticalModes', 1, env)

def patchTacticalModes(env):
    addEffect(10002, 'tacticalMode', EffectCategory.passive, False, False, env)
    addAttribute(10000, 'tacticalModes', 4, 122, True, True, 0, env)
    patchTacticalDestroyer('Confessor', env)
    patchTacticalDestroyer('Svipul', env)
    patchTacticalDestroyer('Jackdaw', env)
    patchTacticalDestroyer('Hecate', env)

def patchAncillaryArmorRepairer(env):
    addEffect(10001, 'naniteRepairPasteArmorDamageBonus', EffectCategory.passive, False, False, env)
    addEffect(10003, 'fueledArmorRepairBonus', EffectCategory.passive, False, False, env)
    addAttribute(10002, 'chargedArmorDamageMultiplierPostDiv', 5, 0, True, True, 0, env)

    for typeID, type in env['typeDogma'].items():
        for attribute in type['dogmaAttributes']:
            if attribute['attributeID'] == 1886:
                addItemAttribute(env['typeIDs'][typeID]['typeName'], 'chargedArmorDamageMultiplierPostDiv', attribute['value'], env)
                break
        for effect in type['dogmaEffects']:
            if effect['effectID'] == 5275:
                addItemEffect(env['typeIDs'][typeID]['typeName'], 'fueledArmorRepairBonus', env)

    addItemEffect('Nanite Repair Paste', 'naniteRepairPasteArmorDamageBonus', env)
    addItemAttribute('Nanite Repair Paste', 'chargedArmorDamageMultiplierPostDiv', 1, env)

def patchFitting(env):
    env['effectNames']['online']['effectCategory'] = EffectCategory.online.name
    env['effectNames']['onlineForStructures']['effectCategory'] = EffectCategory.online.name

    updateEffect('online', env, [ItemModifier(Domain.shipID, 'cpuLoad', Operation.modAdd, 'cpu'),
                                 ItemModifier(Domain.shipID, 'powerLoad', Operation.modAdd, 'power')])

    updateEffect('slotModifier', env, [ItemModifier(Domain.shipID, 'hiSlots', Operation.modAdd, 'hiSlotModifier'),
                                       ItemModifier(Domain.shipID, 'medSlots', Operation.modAdd, 'medSlotModifier'),
                                       ItemModifier(Domain.shipID, 'lowSlots', Operation.modAdd, 'lowSlotModifier')])

    updateEffect('hardPointModifierEffect', env, [ItemModifier(Domain.shipID, 'launcherSlotsLeft', Operation.modAdd, 'launcherHardPointModifier'),
                                                  ItemModifier(Domain.shipID, 'turretSlotsLeft', Operation.modAdd, 'turretHardPointModifier')])


def patchHardeners(env):
    updateEffect('adaptiveArmorHardener', env, [ItemModifier(Domain.shipID, 'armorEmDamageResonance', Operation.postMul, 'armorEmDamageResonance'),
                                                ItemModifier(Domain.shipID, 'armorExplosiveDamageResonance', Operation.postMul, 'armorExplosiveDamageResonance'),
                                                ItemModifier(Domain.shipID, 'armorKineticDamageResonance', Operation.postMul, 'armorKineticDamageResonance'),
                                                ItemModifier(Domain.shipID, 'armorThermalDamageResonance', Operation.postMul, 'armorThermalDamageResonance')])

def patchRepairers(env):
    updateEffect('fueledArmorRepairBonus', env, [ItemModifier(Domain.itemID, 'chargedArmorDamageMultiplier', Operation.postDiv, 'chargedArmorDamageMultiplierPostDiv'),
                                                 ItemModifier(Domain.itemID, 'armorDamageAmount', Operation.postMul, 'chargedArmorDamageMultiplier')])
    
    updateEffect('naniteRepairPasteArmorDamageBonus', env, [ItemModifier(Domain.otherID, 'chargedArmorDamageMultiplierPostDiv', Operation.postAssignment, 'chargedArmorDamageMultiplierPostDiv')])

    updateEffect('armorRepair', env, [ItemModifier(Domain.shipID, 'armorDamage', Operation.subRate, 'armorDamageAmount')])
    updateEffect('targetArmorRepair', env, [ItemModifier(Domain.targetID, 'armorDamage', Operation.subRate, 'armorDamageAmount')])
    #updateEffect('remoteArmorRepairFalloff', env, [ItemModifier(Domain.targetID, 'armorDamage', Operation.subRate, 'armorDamageAmount')])
    updateEffect('fueledArmorRepair', env, [ItemModifier(Domain.shipID, 'armorDamage', Operation.subRate, 'armorDamageAmount')])
    updateEffect('shipModuleRemoteArmorRepairer', env, [ItemModifier(Domain.targetID, 'armorDamage', Operation.subRate, 'armorDamageAmount')])
    updateEffect('shipModuleAncillaryRemoteArmorRepairer', env, [ItemModifier(Domain.targetID, 'armorDamage', Operation.subRate, 'armorDamageAmount')])

    updateEffect('shieldBoosting', env, [ItemModifier(Domain.shipID, 'shieldCharge', Operation.addRate, 'shieldBonus')])
    updateEffect('shieldTransfer', env, [ItemModifier(Domain.targetID, 'shieldCharge', Operation.addRate, 'shieldBonus')])
    #updateEffect('remoteShieldTransferFalloff', env, [ItemModifier(Domain.targetID, 'shieldCharge', Operation.addRate, 'shieldBonus')])
    updateEffect('fueledShieldBoosting', env, [ItemModifier(Domain.shipID, 'shieldCharge', Operation.addRate, 'shieldBonus')])
    updateEffect('shipModuleRemoteShieldBooster', env, [ItemModifier(Domain.targetID, 'shieldCharge', Operation.addRate, 'shieldBonus')])
    updateEffect('shipModuleAncillaryRemoteShieldBooster', env, [ItemModifier(Domain.targetID, 'shieldCharge', Operation.addRate, 'shieldBonus')])

    updateEffect('structureRepair', env, [ItemModifier(Domain.shipID, 'damage', Operation.subRate, 'structureDamageAmount')])
    updateEffect('shipModuleRemoteHullRepairer', env, [ItemModifier(Domain.targetID, 'damage', Operation.subRate, 'structureDamageAmount')])

def patchEnergyTransfers(env):
    updateEffect('shipModuleRemoteCapacitorTransmitter', env, [ItemModifier(Domain.targetID, 'charge', Operation.addRate, 'powerTransferAmount')])
    updateEffect('energyNeutralizerFalloff', env, [ItemModifier(Domain.targetID, 'charge', Operation.subRate, 'powerTransferAmount')])
    updateEffect('energyNosferatuFalloff', env, [ItemModifier(Domain.targetID, 'charge', Operation.subRate, 'powerTransferAmount')])

def patchRemoteTrackingComputer(env):
    updateEffect('shipModuleRemoteTrackingComputer', env, [LocationRequiredSkillModifier(Domain.targetID, 'Gunnery', 'trackingSpeed', Operation.postPercent, 'trackingSpeedBonus'),
                                                           LocationRequiredSkillModifier(Domain.targetID, 'Gunnery', 'maxRange', Operation.postPercent, 'maxRangeBonus'),
                                                           LocationRequiredSkillModifier(Domain.targetID, 'Gunnery', 'falloff', Operation.postPercent, 'falloffBonus')])

def patchConfessor(env):
    updateEffect('modeVelocityPostDiv', env, [ItemModifier(Domain.shipID, 'maxVelocity', Operation.postDiv, 'modeVelocityPostDiv')])
    updateEffect('modeAgilityPostDiv', env, [ItemModifier(Domain.shipID, 'agility', Operation.postDiv, 'modeAgilityPostDiv')])
    updateEffect('modeArmorResonancePostDiv', env, [ItemModifier(Domain.shipID, 'armorEmDamageResonance', Operation.postDiv, 'modeEmResistancePostDiv'),
                                                    ItemModifier(Domain.shipID, 'armorExplosiveDamageResonance', Operation.postDiv, 'modeExplosiveResistancePostDiv'),
                                                    ItemModifier(Domain.shipID, 'armorKineticDamageResonance', Operation.postDiv, 'modeKineticResistancePostDiv'),
                                                    ItemModifier(Domain.shipID, 'armorThermalDamageResonance', Operation.postDiv, 'modeThermicResistancePostDiv')])
    updateEffect('modeSigRadiusPostDiv', env, [ItemModifier(Domain.shipID, 'signatureRadius', Operation.postDiv, 'modeSignatureRadiusPostDiv')])
    updateEffect('shipModeScanStrengthPostDiv', env, [ItemModifier(Domain.shipID, 'scanRadarStrength', Operation.postDiv, 'modeRadarStrengthPostDiv')])
    updateEffect('shipModeSETOptimalRangePostDiv', env, [LocationRequiredSkillModifier(Domain.shipID, 'Small Energy Turret', 'maxRange', Operation.postDiv, 'modeMaxRangePostDiv')])
    updateEffect('shipModeMaxTargetRangePostDiv', env, [ItemModifier(Domain.shipID, 'maxTargetRange', Operation.postDiv, 'modeMaxTargetRangePostDiv')])

def patchSvipul(env):
    updateEffect('modeShieldResonancePostDiv', env, [ItemModifier(Domain.shipID, 'shieldEmDamageResonance', Operation.postDiv, 'modeEmResistancePostDiv'),
                                                    ItemModifier(Domain.shipID, 'shieldExplosiveDamageResonance', Operation.postDiv, 'modeExplosiveResistancePostDiv'),
                                                    ItemModifier(Domain.shipID, 'shieldKineticDamageResonance', Operation.postDiv, 'modeKineticResistancePostDiv'),
                                                    ItemModifier(Domain.shipID, 'shieldThermalDamageResonance', Operation.postDiv, 'modeThermicResistancePostDiv')])
    updateEffect('shipModeSPTTrackingPostDiv', env, [LocationRequiredSkillModifier(Domain.shipID, 'Small Projectile Turret', 'trackingSpeed', Operation.postDiv, 'modeTrackingPostDiv')])
    updateEffect('modeMWDSigRadiusPostDiv', env, [LocationRequiredSkillModifier(Domain.shipID, 'High Speed Maneuvering', 'signatureRadiusBonus', Operation.postDiv, 'modeMWDSigPenaltyPostDiv')])

def patchJackdaw(env):
    updateEffect('shipModeMissileVelocityPostDiv', env, [OwnerRequiredSkillModifier(Domain.charID, 'Missile Launcher Operation', 'maxVelocity', Operation.postDiv, 'modeMaxRangePostDiv')])

def patchHecate(env):
    updateEffect('modeHullResonancePostDiv', env, [ItemModifier(Domain.shipID, 'emDamageResonance', Operation.postDiv, 'modeEmResistancePostDiv'),
                                                   ItemModifier(Domain.shipID, 'explosiveDamageResonance', Operation.postDiv, 'modeExplosiveResistancePostDiv'),
                                                   ItemModifier(Domain.shipID, 'kineticDamageResonance', Operation.postDiv, 'modeKineticResistancePostDiv'),
                                                   ItemModifier(Domain.shipID, 'thermalDamageResonance', Operation.postDiv, 'modeThermicResistancePostDiv')])

    updateEffect('modeArmorRepDurationPostDiv', env, [LocationRequiredSkillModifier(Domain.shipID, 'Repair Systems', 'duration', Operation.postDiv, 'modeArmorRepDurationPostDiv')])
    updateEffect('modeMWDBoostPostDiv', env, [LocationRequiredSkillModifier(Domain.shipID, 'High Speed Maneuvering', 'speedFactor', Operation.postDiv, 'modeMWDVelocityPostDiv')])
    updateEffect('modeMWDCapPostDiv', env, [LocationRequiredSkillModifier(Domain.shipID, 'High Speed Maneuvering', 'capacitorNeed', Operation.postDiv, 'modeMWDCapPostDiv')])
    updateEffect('shipModeSHTOptimalRangePostDiv', env, [LocationRequiredSkillModifier(Domain.shipID, 'Small Hybrid Turret', 'maxRange', Operation.postDiv, 'modeMaxRangePostDiv')])

def patchSpeedBoost(env):
    addAttribute(576, 'speedBoostFactorCalc', 9, 0, True, True, 0.01, env)
    addAttribute(578, 'speedBoostFactorCalc2', 9, 0, True, True, 1.0, env)
    addEffect(710, 'speedBoostFactorCalculator', EffectCategory.passive, False, False, env)
    addEffect(712, 'speedBoostFactorCalculator2', EffectCategory.passive, False, False, env)
    addEffect(1171, 'massFactor', EffectCategory.passive, False, False, env)
    addEffectGroup('Propulsion Module', 'speedBoostFactorCalculator', env)
    addEffectGroup('Propulsion Module', 'speedBoostFactorCalculator2', env)

    updateEffect('speedBoostFactorCalculator', env, [ItemModifier(Domain.itemID, 'speedBoostFactorCalc', Operation.postMul, 'speedFactor'),
                                                     ItemModifier(Domain.itemID, 'speedBoostFactorCalc', Operation.postMul, 'speedBoostFactor')])

    updateEffect('speedBoostFactorCalculator2', env, [ItemModifier(Domain.itemID, 'speedBoostFactorCalc2', Operation.modAdd, 'speedBoostFactorCalc')])

    updateEffect('moduleBonusAfterburner', env, [ItemModifier(Domain.shipID, 'maxVelocity', Operation.postMul, 'speedBoostFactorCalc2'),
                                                 ItemModifier(Domain.shipID, 'mass', Operation.modAdd, 'massAddition')])

    updateEffect('moduleBonusMicrowarpdrive', env, [ItemModifier(Domain.shipID, 'maxVelocity', Operation.postMul, 'speedBoostFactorCalc2'),
                                                    ItemModifier(Domain.shipID, 'mass', Operation.modAdd, 'massAddition'),
                                                    ItemModifier(Domain.shipID, 'signatureRadius', Operation.postPercent, 'signatureRadiusBonus')])

    updateEffect('massFactor', env, [LocationGroupModifier(Domain.itemID, 'Propulsion Module', 'speedBoostFactorCalc', Operation.postDiv, 'mass')])
    addEffectCategory('Ship', 'massFactor', env)

def patchMissing(env):
    updateEffect('droneDmgBonus', env, [LocationRequiredDomainSkillModifier(Domain.charID, 'damageMultiplier', Operation.postPercent, 'damageMultiplierBonus', Domain.itemID)])
    updateEffect('selfRof', env, [LocationRequiredDomainSkillModifier(Domain.shipID, 'speed', Operation.postPercent, 'rofBonus', Domain.itemID)])
    updateEffect('launcherFitted', env, [ItemModifier(Domain.shipID, 'launcherSlotsLeft', Operation.modSub, 'slots')])
    updateEffect('turretFitted', env, [ItemModifier(Domain.shipID, 'turretSlotsLeft', Operation.modSub, 'slots')])
    
    updateEffect('missileEMDmgBonus', env, [LocationRequiredDomainSkillModifier(Domain.charID, 'emDamage', Operation.postPercent, 'damageMultiplierBonus', Domain.itemID)])
    updateEffect('missileExplosiveDmgBonus', env, [LocationRequiredDomainSkillModifier(Domain.charID, 'explosiveDamage', Operation.postPercent, 'damageMultiplierBonus', Domain.itemID)])
    updateEffect('missileThermalDmgBonus', env, [LocationRequiredDomainSkillModifier(Domain.charID, 'thermalDamage', Operation.postPercent, 'damageMultiplierBonus', Domain.itemID)])
    updateEffect('missileKineticDmgBonus2', env, [LocationRequiredDomainSkillModifier(Domain.charID, 'kineticDamage', Operation.postPercent, 'damageMultiplierBonus', Domain.itemID)])
    
    updateEffect('cloakingTargetingDelayBonusPostPercentCloakingTargetingDelayBonusForShipModulesRequiringCloaking', env, [LocationRequiredDomainSkillModifier(Domain.shipID, 'cloakingTargetingDelay', Operation.postPercent, 'cloakingTargetingDelayBonus', Domain.itemID)])

    
def patchGangBoost(env):
    addEffect(1004, 'gangBoost', EffectCategory.activation, False, False, env)
    addEffectGroup('Command Burst', 'gangBoost', env)
    addEffectGroup('Titan Phenomena Generator', 'gangBoost', env)
    warfareBuffs = dict()

    for typeID, type in env['typeDogma'].items():
        for attribute in type['dogmaAttributes']:
            name = env['dogmaAttributes'][attribute['attributeID']]['name']
            if name.startswith('warfareBuff'):
                bufID = int(attribute['value'])
                if bufID in warfareBuffs:
                    continue
                modifyingAttribute = 'none'

                if bufID == 10:
                    id = 'shieldHarmonizingChargeBuff'
                    attributes = ["shieldEmDamageResonance", "shieldKineticDamageResonance", "shieldThermalDamageResonance", "shieldExplosiveDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 11:
                    id = 'activeShieldingChargeBuf'
                    modifiers = list()
                    for modifiedAttribute in ["capacitorNeed", "duration"]:
                        for skill in ["Shield Operation", "Shield Emission Systems"]:
                            modifiers.append(LocationRequiredSkillModifier(Domain.shipID, skill, modifiedAttribute, Operation.postPercent, modifyingAttribute))
                elif bufID == 12:
                    id = 'shieldExtensionChargeBuff'
                    modifiers = [ItemModifier(Domain.shipID, 'shieldCapacity', Operation.postPercent, modifyingAttribute)]
                elif bufID == 13:
                    id = 'armorEnergizingChargeBuff'
                    attributes = ["armorEmDamageResonance", "armorKineticDamageResonance", "armorThermalDamageResonance", "armorExplosiveDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 14:
                    id = 'rapidRepairChargeBuff'
                    modifiers = list()
                    for modifiedAttribute in ["capacitorNeed", "duration"]:
                        for skill in ["Repair Systems", "Remote Armor Repair Systems"]:
                            modifiers.append(LocationRequiredSkillModifier(Domain.shipID, skill, modifiedAttribute, Operation.postPercent, modifyingAttribute))
                elif bufID == 15:
                    id = 'armorReinforcementChargeBuff'
                    modifiers = [ItemModifier(Domain.shipID, 'armorHP', Operation.postPercent, modifyingAttribute)]
                elif bufID == 16:
                    id = 'sensorOptimizationChargeBuff1'
                    modifiers = [ItemModifier(Domain.shipID, 'scanResolution', Operation.postPercent, modifyingAttribute)]
                elif bufID == 17:
                    id = 'electronicSuperiorityChargeBuff'
                    modifiers = list()
                    for modifiedAttribute in ["maxRange", "falloffEffectiveness"]:
                        for group in ["ECM", "Sensor Dampener", "Weapon Disruptor", "Target Painter"]:
                            modifiers.append(LocationGroupModifier(Domain.shipID, group, modifiedAttribute, Operation.postPercent, modifyingAttribute))

                    for modifiedAttribute in ["scanGravimetricStrengthBonus", "scanLadarStrengthBonus", "scanMagnetometricStrengthBonus", "scanRadarStrengthBonus"]:
                        modifiers.append(LocationGroupModifier(Domain.shipID, 'ECM', modifiedAttribute, Operation.postPercent, modifyingAttribute))

                    for modifiedAttribute in ["missileVelocityBonus", "explosionDelayBonus", "aoeVelocityBonus", "falloffBonus", "maxRangeBonus", "aoeCloudSizeBonus", "trackingSpeedBonus"]:
                        modifiers.append(LocationGroupModifier(Domain.shipID, 'Weapon Disruptor', modifiedAttribute, Operation.postPercent, modifyingAttribute))

                    for modifiedAttribute in ["maxTargetRangeBonus", "scanResolutionBonus"]:
                        modifiers.append(LocationGroupModifier(Domain.shipID, 'Sensor Dampener', modifiedAttribute, Operation.postPercent, modifyingAttribute))
                    modifiers.append(LocationGroupModifier(Domain.shipID, 'Target Painter', 'signatureRadiusBonus', Operation.postPercent, modifyingAttribute))
                elif bufID == 18:
                    id = 'electronicHardeningChargeBuff1'
                    attributes = ["scanGravimetricStrength", "scanRadarStrength", "scanLadarStrength", "scanMagnetometricStrength"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 19:
                    id = 'electronicHardeningChargeBuff2'
                    attributes = ["sensorDampenerResistance", "weaponDisruptionResistance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 20:
                    id = 'evasiveManeuversChargeBuff1'
                    modifiers = [ItemModifier(Domain.shipID, 'signatureRadius', Operation.postPercent, modifyingAttribute)]
                elif bufID == 21:
                    id = 'interdictionManeuversChargeBuff'
                    groups = ["Stasis Web", "Warp Scrambler"]
                    modifiers = [LocationGroupModifier(Domain.shipID, x, 'maxRange', Operation.postPercent, modifyingAttribute) for x in groups]
                elif bufID == 22:
                    id = 'rapidDeploymentChargeBuff'
                    skills = ["Afterburner", "High Speed Maneuvering"]
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, x, 'speedFactor', Operation.postPercent, modifyingAttribute) for x in skills]
                elif bufID == 23:
                    id = 'miningLaserFieldEnhancementChargeBuff'
                    skills = ["Mining", "Ice Harvesting", "Gas Cloud Harvesting"]
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, x, 'maxRange', Operation.postPercent, modifyingAttribute) for x in skills]
                    modifiers.append(LocationRequiredSkillModifier(Domain.shipID, 'CPU Management', 'surveyScanRange', Operation.postPercent, modifyingAttribute))
                elif bufID == 24:
                    id = 'miningLaserOptimizationChargeBuff'
                    modifiers = list()
                    for modifiedAttribute in ["capacitorNeed", "duration"]:
                        for skill in ["Mining", "Ice Harvesting", "Gas Cloud Harvesting"]:
                            modifiers.append(LocationRequiredSkillModifier(Domain.shipID, skill, modifiedAttribute, Operation.postPercent, modifyingAttribute))
                elif bufID == 25:
                    id = 'miningEquipmentPreservationChargeBuff1'
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Mining', 'crystalVolatilityChance', Operation.postPercent, modifyingAttribute)]
                elif bufID == 26:
                    id = 'sensorOptimizationChargeBuff2'
                    modifiers = [ItemModifier(Domain.shipID, 'maxTargetRange', Operation.postPercent, modifyingAttribute)]
                elif bufID == 39:
                    id = 'amarrPhenomenaGeneratorBuff1'
                    modifiers = [ItemModifier(Domain.shipID, 'rechargeRate', Operation.postPercent, modifyingAttribute)]
                elif bufID == 40:
                    id = 'amarrPhenomenaGeneratorBuff2'
                    attributes = ["armorKineticDamageResonance", "shieldKineticDamageResonance", "kineticDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 41:
                    id = 'amarrPhenomenaGeneratorBuff3'
                    attributes = ["armorEmDamageResonance", "shieldEmDamageResonance", "emDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 42:
                    id = 'gallentePhenomenaGeneratorBuff1'
                    modifiers = [ItemModifier(Domain.shipID, 'armorHP', Operation.postPercent, modifyingAttribute)]
                elif bufID == 43:
                    id = 'gallentePhenomenaGeneratorBuff2'
                    attributes = ["armorExplosiveDamageResonance", "shieldExplosiveDamageResonance", "explosiveDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 44:
                    id = 'gallentePhenomenaGeneratorBuff3'
                    attributes = ["armorThermalDamageResonance", "shieldThermalDamageResonance", "thermalDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 45:
                    id = 'minmatarPhenomenaGeneratorBuff1'
                    modifiers = [ItemModifier(Domain.shipID, 'signatureRadius', Operation.postPercent, modifyingAttribute)]
                elif bufID == 46:
                    id = 'minmatarPhenomenaGeneratorBuff2'
                    attributes = ["armorThermalDamageResonance", "shieldThermalDamageResonance", "thermalDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 47:
                    id = 'minmatarPhenomenaGeneratorBuff3'
                    attributes = ["armorExplosiveDamageResonance", "shieldExplosiveDamageResonance", "explosiveDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 48:
                    id = 'caldariPhenomenaGeneratorBuff1'
                    modifiers = [ItemModifier(Domain.shipID, 'shieldCapacity', Operation.postPercent, modifyingAttribute)]
                elif bufID == 49:
                    id = 'caldariPhenomenaGeneratorBuff2'
                    attributes = ["armorEmDamageResonance", "shieldEmDamageResonance", "emDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 50:
                    id = 'caldariPhenomenaGeneratorBuff3'
                    attributes = ["armorKineticDamageResonance", "shieldKineticDamageResonance", "kineticDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 51:
                    id = 'amarrPhenomenaGeneratorBuff4'
                    modifiers = [ItemModifier(Domain.shipID, 'maxVelocity', Operation.postPercent, modifyingAttribute)]
                elif bufID == 52:
                    id = 'gallentePhenomenaGeneratorBuff4'
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Shield Emission Systems', 'shieldBonus', Operation.postPercent, modifyingAttribute)]
                elif bufID == 53:
                    id = 'caldariPhenomenaGeneratorBuff4'
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Remote Armor Repair Systems', 'armorDamageAmount', Operation.postPercent, modifyingAttribute)]
                elif bufID == 54:
                    id = 'minmatarPhenomenaGeneratorBuff4'
                    groups = ["Energy Weapon", "Hybrid Weapon"]
                    modifiers = [LocationGroupModifier(Domain.shipID, x, 'maxRange', Operation.postPercent, modifyingAttribute) for x in groups]
                elif bufID == 60:
                    id = 'evasiveManeuversChargeBuff2'
                    modifiers = [ItemModifier(Domain.shipID, 'agility', Operation.postPercent, modifyingAttribute)]
                elif bufID == 79:
                    id = 'aoeBeaconBioluminescenceCloud'
                    modifiers = [ItemModifier(Domain.shipID, 'signatureRadius', Operation.postPercent, modifyingAttribute)]
                elif bufID == 80:
                    id = 'aoeBeaconCausticCloudLocalRepair'
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Repair Systems', 'armorDamageAmount', Operation.postPercent, modifyingAttribute)]
                elif bufID == 81:
                    id = 'aoeBeaconCausticCloudRemoteRepair'
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Remote Armor Repair Systems', 'armorDamageAmount', Operation.postPercent, modifyingAttribute)]
                elif bufID == 88:
                    id = 'aoeBeaconFilamentCloudShieldBoosterShieldBonus'
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Shield Operation', 'shieldBonus', Operation.postPercent, modifyingAttribute)]
                elif bufID == 89:
                    id = 'aoeBeaconFilamentCloudShieldBoosterDuration'
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Shield Operation', 'duration', Operation.postPercent, modifyingAttribute)]
                elif bufID == 90:
                    id = 'weatherElectricStormEMResistancePenalty'
                    attributes = ["shieldEmDamageResonance", "armorEmDamageResonance", "emDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 92:
                    id = 'weatherElectricStormCapacitorRechargeBonus'
                    modifiers = [ItemModifier(Domain.shipID, 'rechargeRate', Operation.postPercent, modifyingAttribute)]
                elif bufID == 93:
                    id = 'weatherXenonGasExplosiveResistancePenalty'
                    attributes = ["shieldExplosiveDamageResonance", "armorExplosiveDamageResonance", "explosiveDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 94:
                    id = 'weatherXenonGasShieldHPBonus'
                    modifiers = [ItemModifier(Domain.shipID, 'shieldCapacity', Operation.postPercent, modifyingAttribute)]
                elif bufID == 95:
                    id = 'weatherInfernalThermalResistancePenalty'
                    attributes = ["shieldThermalDamageResonance", "armorThermalDamageResonance", "thermalDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 96:
                    id = 'weatherInfernalArmorHPBonus'
                    modifiers = [ItemModifier(Domain.shipID, 'armorHP', Operation.postPercent, modifyingAttribute)]
                elif bufID == 97:
                    id = 'weatherDarknessTurretRangePenalty'
                    attributes = ["maxRange", "falloff"]
                    modifiers = [LocationRequiredSkillModifier(Domain.shipID, 'Gunnery', x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 98:
                    id = 'weatherDarknessVelocityBonus'
                    modifiers = [ItemModifier(Domain.shipID, 'maxVelocity', Operation.postPercent, modifyingAttribute)]
                elif bufID == 99:
                    id = 'weatherCausticToxinKineticResistancePenalty'
                    attributes = ["shieldKineticDamageResonance", "armorKineticDamageResonance", "kineticDamageResonance"]
                    modifiers = [ItemModifier(Domain.shipID, x, Operation.postPercent, modifyingAttribute) for x in attributes]
                elif bufID == 100:
                    id = 'weatherCausticToxinScanResolutionBonus'
                    modifiers = [ItemModifier(Domain.shipID, 'scanResolution', Operation.postPercent, modifyingAttribute)]
                else:
                    continue
                warfareBuffs[bufID] = {'id': id, 'modifiers': modifiers}
    env['warfareBuffs'] = warfareBuffs

def patchSubsystems(env):
    for type in env['typeDogma'].values():
        for attribute in type['dogmaAttributes']:
            if attribute['attributeID'] == 1367: #maxSubSystems
                attribute['value'] = 4
                break

    #maxSubSystems

def patch(env):
    patchMissilesDamage(env)
    patchTacticalModes(env)
    patchAncillaryArmorRepairer(env)
    patchFitting(env)
    patchHardeners(env)
    patchRepairers(env)
    patchEnergyTransfers(env)
    patchRemoteTrackingComputer(env)
    patchSpeedBoost(env)
    patchMissing(env)
    patchGangBoost(env)
    patchSubsystems(env)
    #patchConfessor(env)
    #patchSvipul(env)
    #patchJackdaw(env)
    #patchHecate(env)