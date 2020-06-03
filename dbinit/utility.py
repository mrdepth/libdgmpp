from enum import Enum
import re
import io

class EffectCategory(Enum):
    activation = 'activation'
    target = 'target'
    area = 'area'
    dungeon = 'dungeon'
    online = 'online'
    overload = 'overload'
    passive = 'passive'
    system = 'system'

    @classmethod
    def fromString(cls, s):
        return cls.__dict__['_value2member_map_'][s]

    def esiName(self):
        return {EffectCategory.activation: "activation",
                EffectCategory.target: "target",
                EffectCategory.area: "area",
                EffectCategory.dungeon: "dungeon",
                EffectCategory.online: "online",
                EffectCategory.overload: "overload",
                EffectCategory.passive: "passive",
                EffectCategory.system: "system"}[self]

    def order(self):
        return {EffectCategory.activation: 1,
                EffectCategory.target: 2,
                EffectCategory.area: 7,
                EffectCategory.dungeon: 5,
                EffectCategory.online: 3,
                EffectCategory.overload: 4,
                EffectCategory.passive: 0,
                EffectCategory.system: 6}[self]


class Func(Enum):
    LocationModifier = 'LocationModifier'
    ItemModifier = 'ItemModifier'
    LocationGroupModifier = 'LocationGroupModifier'
    OwnerRequiredSkillModifier = 'OwnerRequiredSkillModifier'
    LocationRequiredSkillModifier = 'LocationRequiredSkillModifier'
    LocationRequiredDomainSkillModifier = 'LocationRequiredDomainSkillModifier'
    EffectStopper = 'EffectStopper'

    @classmethod
    def fromString(cls, s):
        return cls.__dict__['_value2member_map_'][s]

    def esiName(self):
        return {Func.LocationModifier: "location",
                Func.ItemModifier: "item",
                Func.LocationGroupModifier: "locationGroup",
                Func.OwnerRequiredSkillModifier: "ownerRequiredSkill",
                Func.LocationRequiredSkillModifier: "locationRequiredSkill",
                Func.LocationRequiredDomainSkillModifier: "locationRequiredDomainSkill",
                Func.EffectStopper: None}[self]


class Domain(Enum):
    itemID = 'itemID'
    target = 'target'
    otherID = 'otherID'
    targetID = 'targetID'
    charID = 'charID'
    structureID = 'structureID'
    shipID = 'shipID'

    @classmethod
    def fromString(cls, s):
        return cls.__dict__['_value2member_map_'][s]

    def esiName(self):
        return {Domain.itemID: "self",
                Domain.target: "target",
                Domain.targetID: "target",
                Domain.charID: "character",
                Domain.otherID: "other",
                Domain.structureID: "structure",
                Domain.shipID: "ship"}[self]

class Operation(Enum):
    modSub = 'modSub'
    postDiv = 'postDiv'
    preAssignment = 'preAssignment'
    preMul = 'preMul'
    specialSkillOp = 'specialSkillOp'
    postPercent = 'postPercent'
    postAssignment = 'postAssignment'
    postMul = 'postMul'
    modAdd = 'modAdd'
    subRate = 'subRate'
    addRate = 'addRate'

    @classmethod
    def fromString(cls, s):
        return cls.__dict__['_value2member_map_'][s]

    def esiName(self):
        if self == Operation.specialSkillOp:
            return "skillTime"
        else:
            return self.name

class Modifier:
    def __init__(self, domain: Domain, func: Func, modifiedAttribute, operation: Operation, modifyingAttribute, skillType, group, domainID):
        self.domain = domain
        self.func = func
        self.operation = operation
        self.modifiedAttribute = modifiedAttribute
        self.modifyingAttribute = modifyingAttribute
        self.skillType = skillType
        self.group = group
        self.domainID = domainID

    @classmethod
    def fromDict(cls, modifier, env):
        func = Func.fromString(modifier['func'])
        if func == Func.EffectStopper:
            return None
        domain = Domain.fromString(modifier['domain'])
        operation = Operation.fromString(modifier['operation'])
        modifiedAttributeID = modifier['modifiedAttributeID']
        modifyingAttributeID = modifier['modifyingAttributeID']
        modifiedAttribute = env['dogmaAttributes'][modifiedAttributeID]['name']
        modifyingAttribute = env['dogmaAttributes'][modifyingAttributeID]['name']

        try:
            groupID = modifier['groupID']
            group = getName(env['groupIDs'][groupID])
        except:
            group = None
            pass

        try:
            skillTypeID = modifier['skillTypeID']
            skillType = getName(env['typeIDs'][skillTypeID])
        except:
            skillType = None

        try:
            domainID = Domain.fromString(modifier['domainID'])
        except:
            domainID = None

        return cls(domain, func, modifiedAttribute, operation, modifyingAttribute, skillType, group, domainID)


    def patch(self, env):
        skillTypeID = env['typeNames'][self.skillType]['typeID'] if self.skillType else None
        groupID = env['groupNames'][self.group]['groupID'] if self.group else None
        domainID = self.domainID.name if self.domainID else None

        modifier = {'domain': self.domain.name,
                'func': self.func.name,
                'operation': self.operation.name,
                'modifiedAttributeID': env['attributeNames'][self.modifiedAttribute]['attributeID'],
                'modifyingAttributeID': env['attributeNames'][self.modifyingAttribute]['attributeID'],
                'skillTypeID': skillTypeID,
                'groupID': groupID,
                'domainID': domainID}
        modifier = {k:v for k,v in modifier.items() if v is not None}
        return modifier
        #effect['modifierInfo'].add(modifier)

    def dic(self):
        return {'domain': self.domain.name,
                'func': self.func.name,
                'operation': self.operation.name,
                'modifiedAttribute': self.modifiedAttribute,
                'modifyingAttribute': self.modifyingAttribute,
                'skillType': self.skillType,
                'group': self.group,
                'domainID': self.domainID}

    def __eq__(self, other):
        return self.dic() == other.dic()
    
    def __hash__(self):
        return hash(self.dic().__repr__())


class ItemModifier(Modifier):
    def __init__(self, domain: Domain, modifiedAttribute, operation: Operation, modifyingAttribute):
        super(ItemModifier, self).__init__(domain, Func.ItemModifier, modifiedAttribute, operation, modifyingAttribute, None, None, None)

class LocationGroupModifier(Modifier):
    def __init__(self, domain: Domain, group, modifiedAttribute, operation: Operation, modifyingAttribute):
        super(LocationGroupModifier, self).__init__(domain, Func.LocationGroupModifier, modifiedAttribute, operation, modifyingAttribute, None, group, None)

class LocationRequiredSkillModifier(Modifier):
    def __init__(self, domain: Domain, skill, modifiedAttribute, operation: Operation, modifyingAttribute):
        super(LocationRequiredSkillModifier, self).__init__(domain, Func.LocationRequiredSkillModifier, modifiedAttribute, operation, modifyingAttribute, skill, None, None)

class OwnerRequiredSkillModifier(Modifier):
    def __init__(self, domain: Domain, skill, modifiedAttribute, operation: Operation, modifyingAttribute):
        super(OwnerRequiredSkillModifier, self).__init__(domain, Func.OwnerRequiredSkillModifier, modifiedAttribute, operation, modifyingAttribute, skill, None, None)

class LocationRequiredDomainSkillModifier(Modifier):
    def __init__(self, domain: Domain, modifiedAttribute, operation: Operation, modifyingAttribute, domainID: Domain):
        super(LocationRequiredDomainSkillModifier, self).__init__(domain, Func.LocationRequiredDomainSkillModifier, modifiedAttribute, operation, modifyingAttribute, None, None, domainID)

def getName(obj):
    try:
        return obj['name']['en']
    except:
        return None

def getTypeID(typeName, env):
    return env['typeNames'][typeName]['typeID']

def addEffect(id, name, category: EffectCategory, isOffensive, isAssistance, env):
    env['dogmaEffects'][id] = {'effectID': id, 'effectName': name, 'effectCategory': category.name, 'isOffensive': isOffensive, 'isAssistance': isAssistance}
    env['effectNames'][name] = env['dogmaEffects'][id]

def addAttribute(id, name, categoryID, unitID, stackable, highIsGood, defaultValue, env):
    env['dogmaAttributes'][id] = {'attributeID': id, 'name': name, 'categoryID': categoryID, 'unitID': unitID, 'stackable': stackable, 'highIsGood': highIsGood, 'defaultValue': defaultValue}
    env['attributeNames'][name] = env['dogmaAttributes'][id]

def addItemEffect(typeName, effectName, env):
    effectID = env['effectNames'][effectName]['effectID']
    env['typeNames'][typeName]['dogmaEffects'].append({'effectID': effectID})

def addItemAttribute(typeName, attributeName, value, env):
    attributeID = env['attributeNames'][attributeName]['attributeID']
    env['typeNames'][typeName]['dogmaAttributes'].append({'attributeID': attributeID, 'value': value})

def addAttributeGroup(groupName, attributeName, value, env):
    groupID = env['groupNames'][groupName]['groupID']
    attributeID = env['attributeNames'][attributeName]['attributeID']
    for k, v in env['typeDogma'].items():
        if v['groupID'] == groupID:
            v['dogmaAttributes'].append({'attributeID': attributeID, 'value': value})

def addEffectGroup(groupName, effectName, env):
    groupID = env['groupNames'][groupName]['groupID']
    effectID = env['effectNames'][effectName]['effectID']
    for k, v in env['typeDogma'].items():
        if env['typeIDs'][k]['groupID'] == groupID:
            v['dogmaEffects'].append({'effectID': effectID, 'isDefault': False})

def addEffectCategory(categoryName, effectName, env):
    categoryID = env['categoryNames'][categoryName]['categoryID']
    effectID = env['effectNames'][effectName]['effectID']

    for k, v in env['typeDogma'].items():
        groupID = env['typeIDs'][k]['groupID']
        if env['groupIDs'][groupID]['categoryID'] == categoryID:
            v['dogmaEffects'].append({'effectID': effectID, 'isDefault': False})

def updateEffect(effectName, env, modifiers):
    effect = env['effectNames'][effectName]
    effect['modifierInfo'] = [x.patch(env) for x in modifiers]

r1 = re.compile(r'(\\u.{4})')
r2 = re.compile(r'[^a-zA-Z0-9]')
r3 = re.compile(r'^[A-Z][^A-Z]+.*')
r4 = re.compile(r'^\d.*')
def safeName(s):
    s = r1.sub("", s)
    s = r2.sub("", s)
    if r3.match(s):
        ss = list(s)
        ss[0] = ss[0].lower()
        s = "".join(ss)
    if r4.match(s):
        s = '_' + s
    if len(s) == 0:
        s = "unknown"

    return s

def uniqueName(name, uniqueNames):
    base = name
    i = 1
    while name in uniqueNames:
        name = "{}_{}".format(base, i)
        i += 1
    uniqueNames.add(name)
    return name

def dumpIDs(ids, typeName, f: io.IOBase):
    unique = set()
    idsMap = dict()

    rows=['\t\tnone = 0']
    for id, base in sorted(ids.items()):
        if base is None:
            continue
        base = safeName(base)
        name = uniqueName(base, unique)
        idsMap[id] = name
        rows.append('\t\t{} = {}'.format(name, id))


    f.write("""#pragma once
namespace dgmpp {{
	enum class {}: unsigned short {{
{}
    }};
}}""".format(typeName, ',\n'.join(rows)))

    return idsMap

def dumpAttributeTypes(env, f: io.IOBase):
    rows = list()
    idsMap = env['attributeIDsMap']
    names = list()
    for id, attribute in sorted(env['dogmaAttributes'].items()):
        try:
            maxAttributeID = attribute['maxAttributeID']
            maxAttributeName = idsMap[maxAttributeID]
        except:
            maxAttributeName = 'none'
        rows.append("\t\tconstexpr MetaInfo::Attribute {attributeName} = {{AttributeID::{attributeName}, AttributeID::{maxAttributeName}, {defaultValue}, {isStackable}, {highIsGood}}};".format(
            attributeName = idsMap[id],
            attributeID = id,
            maxAttributeName = maxAttributeName,
            defaultValue = attribute['defaultValue'],
            isStackable = 'true' if attribute['stackable'] else 'false',
            highIsGood = 'true' if attribute['highIsGood'] else 'false'))
        names.append("&Attributes::{}".format(idsMap[id]))

    f.write("""#pragma once
#include "MetaInfo.hpp"
namespace dgmpp {{
    namespace SDE {{
		namespace Attributes {{
{}
        }}
        constexpr const MetaInfo::Attribute* attributes[] {{
            {}
        }};
    }}
}}""".format('\n'.join(rows), ', '.join(names)))


def dumpModifier(env, modifier: Modifier, id):
    if modifier.modifyingAttribute == 'none':
        modifyingAttribute = 'AttributeID::none'
    else:
        modifyingAttribute = 'AttributeID::{}'.format(env['attributeIDsMap'][env['attributeNames'][modifier.modifyingAttribute]['attributeID']])

    args = [
        'MetaInfo::Modifier::ModifierType::{}'.format(modifier.func.esiName()),
        'MetaInfo::Modifier::Association::{}'.format(modifier.operation.esiName()),
        'MetaInfo::Modifier::Domain::{}'.format(modifier.domain.esiName()),
        'AttributeID::{}'.format(env['attributeIDsMap'][env['attributeNames'][modifier.modifiedAttribute]['attributeID']]),
        modifyingAttribute
        ]
    if modifier.func == Func.LocationGroupModifier:
        args.append('GroupID::{}'.format(env['groupIDsMap'][env['groupNames'][modifier.group]['groupID']]))
    elif modifier.func == Func.LocationRequiredSkillModifier or modifier.func == Func.OwnerRequiredSkillModifier:
        args.append('TypeID::{}'.format(env['typeIDsMap'][env['typeNames'][modifier.skillType]['typeID']]))
    elif modifier.func == Func.LocationRequiredDomainSkillModifier:
        args.append('MetaInfo::Modifier::Domain::{}'.format(modifier.domainID.esiName()))

    return '\t\t\tconstexpr MetaInfo::Modifier {id} = {{{args}}};'.format(id = id, args = ', '.join(args))

def dumpModifiers(env, modifiers, f: io.IOBase):
    m = {v: k for k, v in modifiers.items()}
    rows = [dumpModifier(env, v, 'modifier{}'.format(k)) for k, v in sorted(m.items())]

    f.write("""#pragma once
#include "MetaInfo.hpp"

namespace dgmpp {{
	namespace SDE {{
		namespace Modifiers {{
{}
        }}
    }}
}}""".format('\n'.join(rows)))


def dumpEffect(env, effectID, effect, modifiers):
    if 'modifierInfo' in effect:
        modifierInfo = [Modifier.fromDict(x, env) for x in effect['modifierInfo']]
        modifierInfo = ['&Modifiers::modifier{}'.format(modifiers[x]) for x in modifierInfo if x is not None]
    else:
        modifierInfo = []
    return '\t\t\tconstexpr auto {effectName} = MakeEffect(EffectID::{effectName}, MetaInfo::Effect::Category::{category}, {isOffensive}, {isAssistance}, _modifiers({modifierInfo}));'.format(
        effectName = env['effectIDsMap'][effectID],
        category = EffectCategory.fromString(effect['effectCategory']).esiName(),
        isOffensive = 'true' if effect['isOffensive'] else 'false',
        isAssistance = 'true' if effect['isAssistance'] else 'false',
        modifierInfo = ','.join(modifierInfo))


def dumpEffects(env, modifiers, f: io.IOBase):
    rows = [dumpEffect(env, k, v, modifiers) for k, v in sorted(env['dogmaEffects'].items())]

    f.write("""#pragma once
#include "MetaInfo.hpp"
#include "Modifiers.hpp"

namespace dgmpp {{
	namespace SDE {{
		namespace Effects {{
			using namespace MetaInfo;
{}
        }}
    }}
}}
""".format('\n'.join(rows)))

def dumpItemRequiredSkills(typeID, env):
    skills = list()
    try:
        attr = env['typeDogma'][typeID]['dogmaAttributes']
    except:
        attr = []
    for i in attr:
        if env['dogmaAttributes'][i['attributeID']]['name'] in {'requiredSkill1', 'requiredSkill2', 'requiredSkill3', 'requiredSkill4', 'requiredSkill5', 'requiredSkill6', 'requiredSkill7', 'requiredSkill8'}:
            skills.append('TypeID::{}'.format(env['typeIDsMap'][int(i['value'])]))
    return sorted(skills)

def dumpItemEffects(typeID, env):
    effects = list()
    try:
        fx = env['typeDogma'][typeID]['dogmaEffects']
    except:
        fx = []

    fx = sorted(fx, key = lambda x: EffectCategory.fromString(env['dogmaEffects'][x['effectID']]['effectCategory']).order())

    for i in fx:
        effects.append('&Effects::{}'.format(env['effectIDsMap'][i['effectID']]))
    return effects

def dumpAttribute(attributeName, value):
    return '_A(&Attributes::{}, {})'.format(attributeName, value);

def dumpItemAttributes(typeID, env):
    attributes = list()

    predefined = {'radius', 'mass', 'volume', 'capacity', 'raceID'}

    try:
        attr = env['typeDogma'][typeID]['dogmaAttributes']
    except:
        attr = []

    for i in attr:
        name = env['attributeIDsMap'][i['attributeID']]
        if name in predefined:
            predefined.remove(name)
        attributes.append(dumpAttribute(name, i['value']))

    type = env['typeIDs'][typeID]

    for name in predefined:
        if name in type and type[name] > 0:
            attributes.append(dumpAttribute(name, type[name]))

    return sorted(attributes)

def dumpItem(typeID, env):
    metaGroup = 'none'
    metaLevel = 0
    type = env['typeIDs'][typeID]
    groupID = type['groupID']
    group = env['groupIDs'][groupID]
    categoryID = group['categoryID']

    try:
        attributes = env['typeDogma'][typeID]['dogmaAttributes']
    except:
        attributes = []
    
    for i in attributes:
        name = env['attributeIDsMap'][i['attributeID']]

        if name == 'metaGroupID':
            id = int(i['value'])
            if id > 0:
                metaGroup = env['metaGroupIDsMap'][id]
        elif name == 'metaLevel':
            metaLevel = int(i['value'])
    
    return 'constexpr auto {typeName} = MakeType(TypeID::{typeName}, GroupID::{groupName}, CategoryID::{categoryName}, MetaInfo::Type::MetaGroup::{metaGroup}, {metaLevel},\n\t\t\t\t_attributes({attributes}),\n\t\t\t\t_effects({effects}),\n\t\t\t\t_typeIDs({typeIDs}));'.format(
        typeName = env['typeIDsMap'][typeID],
        groupName = env['groupIDsMap'][groupID],
        categoryName = env['categoryIDsMap'][categoryID],
        metaGroup = metaGroup,
        metaLevel = metaLevel,
        attributes = ','.join(dumpItemAttributes(typeID, env)),
        effects = ','.join(dumpItemEffects(typeID, env)),
        typeIDs = ','.join(dumpItemRequiredSkills(typeID, env)))

def dumpItems(env, f: io.IOBase):
    typeIDs = sorted(env['typeIDs'].items())
    rows = [dumpItem(typeID, env) for typeID, v in typeIDs]
    names = ['&Types::{}'.format(env['typeIDsMap'][typeID]) for typeID, v in typeIDs]
    f.write("""#pragma once
#include "MetaInfo.hpp"
#include "Attributes.hpp"
#include "Effects.hpp"

namespace dgmpp {{
	namespace SDE {{
		namespace Types {{
			using namespace MetaInfo;
			constexpr auto none = MakeType(TypeID::none, GroupID::corporation, CategoryID::owner, MetaInfo::Type::MetaGroup::none, 0, _attributes(), _effects(), _typeIDs());
{}
        }}
constexpr const MetaInfo::Type* types[] {{
&Types::none, {}
        }};
    }}
}}
""".format('\n'.join(rows), ', '.join(names)))

def dumpWarfareBuff(buff, env):
    id = buff['id']
    ids = ['{}_modifier{}'.format(id, i) for i, x in enumerate(buff['modifiers'])]
    modifiers = [dumpModifier(env, x, i) for i, x in zip(ids, buff['modifiers'])]

    return '{modifiers}\n\t\t\tconstexpr auto {id} = MakeBuff(WarfareBuffID::{id}, _modifiers({ids}));'.format(modifiers = '\n'.join(modifiers),
                                                                                                                                                  id = id,
                                                                                                                                                  ids = ', '.join(['&' + x for x in ids]))


def dumpWarfareBuffs(env, f: io.IOBase):
    bufIDs = sorted(env['warfareBuffs'].items())
    buffs = [dumpWarfareBuff(v, env) for k, v in bufIDs]
    ids = ['&WafrareBuffs::{}'.format(v['id']) for k, v in bufIDs]

    f.write("""#pragma once
#include "MetaInfo.hpp"
#include "Modifiers.hpp"

namespace dgmpp {{
	namespace SDE {{
		namespace WafrareBuffs {{
			using namespace MetaInfo;
{}
        }}
        constexpr const MetaInfo::WarfareBuff* warfareBuffs[] {{
{}
        }};
    }}
}}
""".format('\n'.join(buffs), ', '.join(ids)))

def dumpCommodities(env, f: io.IOBase):
    planetSchematicsTypeMap = env['planetSchematicsTypeMap']
    products = {x['typeID'] for x in planetSchematicsTypeMap if x['isInput'] == 0}
    tiers = list()
    tiers.append({x['typeID'] for x in planetSchematicsTypeMap if x['isInput'] not in products})

    i = 1
    while True:
        schematics = {x['schematicID'] for x in planetSchematicsTypeMap if x['typeID'] in tiers[i - 1] and x['isInput'] == 1}
        tier = {x['typeID'] for x in planetSchematicsTypeMap if x['schematicID'] in schematics and x['isInput'] == 0}
        if tier:
            tiers.append(tier)
            i = i + 1
        else:
            break
    rows = list()
    
    tiers = {typeID: tier for tier, types in enumerate(tiers) for typeID in types}
    ids = list()
    for typeID, tier in sorted(tiers.items()):
        row = '\t\t\tconstexpr MetaInfo::Commodity {typeName} = {{TypeID::{typeName}, MetaInfo::Commodity::Tier::{tier}, {volume} }};'.format(
            typeName = env['typeIDsMap'][typeID],
                tier = 'raw' if tier == 0 else 'tier{}'.format(tier),
                volume = env['typeIDs'][typeID]['volume'])
        rows.append(row)
        ids.append('&Commodities::{}'.format(env['typeIDsMap'][typeID]))

    f.write("""#pragma once
#include "MetaInfo.hpp"

namespace dgmpp {{
	namespace SDE {{
		namespace Commodities {{
{}
        }}
        constexpr const MetaInfo::Commodity* commodities[] {{ {} }};
    }}
}}
""".format('\n'.join(rows), ', '.join(ids)))

def dumpFacility(typeID, type, env):
    return '\t\t\tconstexpr MetaInfo::Facility {typeName} = {{TypeID::{typeName}, GroupID::{groupName}, {capacity}}};'.format(
        typeName = env['typeIDsMap'][typeID],
        groupName = env['groupIDsMap'][type['groupID']],
        capacity = type['capacity'] if 'capacity' in type else 0)

def dumpFacilities(env, f: io.IOBase):
    groups = [k for k, v in env['groupIDs'].items() if getName(v) in ["Extractors", "Command Centers", "Processors", "Storage Facilities", "Spaceports", "Extractor Control Units"]]
    types = {k: v for k, v in env['typeIDs'].items() if v['groupID'] in groups}
    rows = [dumpFacility(k, v, env) for k, v in sorted(types.items())]
    ids = [env['typeIDsMap'][k] for k, v in sorted(types.items())]
    f.write("""#pragma once
#include "MetaInfo.hpp"

namespace dgmpp {{
	namespace SDE {{
		namespace Facilities {{
{}
        }}
        constexpr const MetaInfo::Facility* facilities[] {{ {} }};
    }}
}}
""".format('\n'.join(rows), ', '.join(['&Facilities::' + x for x in ids])))

def dumpPort(x, env):
    return '_C(&Commodities::{}, {})'.format(env['typeIDsMap'][x['typeID']], x['quantity'])

def dumpSchematic(id, schematic, env):
    output = next(x for x in env['planetSchematicsTypeMap'] if x['schematicID'] == id and x['isInput'] == 0)
    inputs = {x['typeID']: x for x in env['planetSchematicsTypeMap'] if x['schematicID'] == id and x['isInput'] == 1}
    output = dumpPort(output, env)
    inputs = [dumpPort(x, env) for id, x in sorted(inputs.items())]
    return '\t\t\tconstexpr auto {typeName} = MakeSchematic(SchematicID::{typeName}, {cycleTime}s, {output}, _inputs({inputs}));'.format(
        typeName = safeName(schematic['schematicName']),
        cycleTime = schematic['cycleTime'],
        output = output,
        inputs = ', '.join(inputs)
        )

def dumpSchematics(env, f: io.IOBase):
    rows = [dumpSchematic(id, x, env) for id, x in sorted(env['planetSchematics'].items())]
    ids = [safeName(x['schematicName']) for id, x in sorted(env['planetSchematics'].items())]
    f.write("""#pragma once
#include "Commodities.hpp"

namespace dgmpp {{
	namespace SDE {{
		namespace Schematics {{
            using namespace std::chrono_literals;
{}
        }}
        constexpr const MetaInfo::Schematic* schematics[] {{ {} }};
    }}
}}
""".format('\n'.join(rows), ', '.join(['&Schematics::' + x for x in ids])))

def dumpSkills(env, f: io.IOBase):
    skills = {k: v for k, v in env['typeIDs'].items() if env['groupIDs'][v['groupID']]['categoryID'] == 16}
    skills = sorted(skills.items())

    names = ['\t\t\t&Types::{}'.format(env['typeIDsMap'][typeID]) for typeID, v in skills]

    f.write("""#pragma once
#include "Types.hpp"

namespace dgmpp {{
	namespace SDE {{
        constexpr const MetaInfo::Type* skills_array[] = {{
{}
        }};
    }}
}}
""".format(',\n'.join(names)))