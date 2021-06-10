import os
import sys
import json
from utility import *
from patch import *
import io
import datetime

print(sys.argv)
validCategoryIDs = [1, 2, 4, 8, 17, 18, 20, 7, 6, 16, 23, 32, 41, 42, 43, 65, 66, 87]

#SDE = os.path.join(os.getcwd(), "sde")
SDE = sys.argv[1]
OUT = sys.argv[2]

with open(os.path.join(SDE, 'fsd/categoryIDs.json')) as f:
    categoryIDs = {int(k): v for k,v in json.load(f).items()}
    categoryIDs = {key: categoryIDs[key] for key in validCategoryIDs}
    for k, v in categoryIDs.items():
        v['categoryID'] = k
        v['categoryName'] = getName(v)

    categoryNames = {v['categoryName']: v for k, v in categoryIDs.items()}


with open(os.path.join(SDE, 'fsd/groupIDs.json')) as f:
    groupIDs = {int(k): v for k,v in json.load(f).items()}
    groupIDs = {k: v for k, v in groupIDs.items() if v['categoryID'] in validCategoryIDs}
    for k, v in groupIDs.items():
        v['groupID'] = k
        v['groupName'] = getName(v)

    groupNames = {v['groupName']: v for k, v in groupIDs.items()}

validGroupIDs = groupIDs.keys()

with open(os.path.join(SDE, 'fsd/typeIDs.json')) as f:
    typeIDs = {int(k): v for k,v in json.load(f).items()}
    typeIDs = {k: v for k, v in typeIDs.items() if v['groupID'] in validGroupIDs}
    for k, v in typeIDs.items():
        v['typeName'] = getName(v)
    typeIDs = {k: v for k, v in typeIDs.items() if 'typeName' in v and v['typeName']}


validTypeIDs = typeIDs.keys()

with open(os.path.join(SDE, 'fsd/typeDogma.json')) as f:
    typeDogma = {int(k): v for k,v in json.load(f).items()}
    typeDogma = {k: v for k, v in typeDogma.items() if k in validTypeIDs}
    for k, v in typeDogma.items():
        v['typeID'] = k

    typeNames = {typeIDs[k]['typeName']: v for k, v in typeDogma.items()}
    validEffectIDs = set([attribute['effectID'] for k, v in typeDogma.items() for attribute in v['dogmaEffects']])

with open(os.path.join(SDE, 'fsd/dogmaAttributes.json')) as f:
    dogmaAttributes = {int(k): v for k,v in json.load(f).items()}
    attributeNames = {v['name']: v for k, v in dogmaAttributes.items()}

with open(os.path.join(SDE, 'fsd/dogmaEffects.json')) as f:
    dogmaEffects = {int(k): v for k,v in json.load(f).items()}
    dogmaEffects = {k: v for k, v in dogmaEffects.items() if k in validEffectIDs}
    effectNames = {v['effectName']: v for k, v in dogmaEffects.items()}

# with open(os.path.join(SDE, 'fsd/dgmEffects.json')) as f:
#     dgmEffects = {v['effectID']: v for v in json.load(f)}
#     dgmEffects = {k: v for k, v in dgmEffects.items() if k in validEffectIDs}

with open(os.path.join(SDE, 'fsd/metaGroups.json')) as f:
    metaGroups = {int(k): v for k,v in json.load(f).items()}
    metaGroupIDsMap = {k: safeName(v['nameID']['en']) for k, v in metaGroups.items()}

with open(os.path.join(SDE, 'fsd/planetSchematics.json')) as f:
    planetSchematics = {int(k): v for k,v in json.load(f).items()}

# with open(os.path.join(SDE, 'bsd/planetSchematicsPinMap.json')) as f:
#     planetSchematicsPinMap = json.load(f)

# with open(os.path.join(SDE, 'bsd/planetSchematicsTypeMap.json')) as f:
#     planetSchematicsTypeMap = json.load(f)

env = {'categoryIDs': categoryIDs,
       'categoryNames': categoryNames,
       'groupIDs': groupIDs,
       'groupNames': groupNames,
       'typeIDs': typeIDs,
       'typeNames': typeNames,
       'dogmaAttributes': dogmaAttributes,
       'attributeNames': attributeNames,
       'dogmaEffects': dogmaEffects,
       'effectNames': effectNames,
       'typeDogma': typeDogma,
       'metaGroupIDsMap': metaGroupIDsMap,
       'planetSchematics': planetSchematics}
    #    'planetSchematicsPinMap': planetSchematicsPinMap,
    #    'planetSchematicsTypeMap': planetSchematicsTypeMap}

planetSchematicsTypeMap = [dict(y, **{'schematicID': schematicID, 'typeID': int(typeID)}) for (schematicID, x) in env['planetSchematics'].items() for (typeID, y) in x['types'].items()]
env['planetSchematicsTypeMap'] = planetSchematicsTypeMap
patch(env)

#empty = {k: v for k, v in dogmaeffects.items() if 'modifierinfo' not in v}
#for k, v in empty.items():
#    try:
#        v['preexpression'] = dgmeffects[k]['preexpression']
#    except:
#        v['preexpression'] = 59
#        pass

#empty = {k: {"name": v['effectname'], 'preexpression': v['preexpression']} for k, v in empty.items() if v['preexpression'] not in {59, 89, 130, 131, 114, 115, 706, 707, 288, 633, 706, 707, 3134, 185, 402, 403, 404, 472}}

modifiers = dict()
for id, effect in sorted(dogmaEffects.items()):
    try:
        for i in effect['modifierInfo']:
            modifier = Modifier.fromDict(i, env)
            if modifier and modifier not in modifiers:
                modifiers[modifier] = len(modifiers) + 1

    except:
        pass


devnull = open(os.devnull, 'w')

def getBuffID(b):
    group, buff = b
    return '{}{}'.format(buff['id'], group)

with open(os.path.join(OUT, 'CategoryID.hpp'), "w") as f:
    env['categoryIDsMap'] = dumpIDs({k: getName(v) for k, v in categoryIDs.items()}, 'CategoryID', f)
with open(os.path.join(OUT, 'GroupID.hpp'), "w") as f:
    env['groupIDsMap'] = dumpIDs({k: getName(v) for k, v in groupIDs.items()}, 'GroupID', f)
with open(os.path.join(OUT, 'TypeID.hpp'), "w") as f:
    env['typeIDsMap'] = dumpIDs({k: getName(v) for k, v in typeIDs.items()}, 'TypeID', f)
with open(os.path.join(OUT, 'AttributeID.hpp'), "w") as f:
    env['attributeIDsMap'] = dumpIDs({k: v['name'] for k, v in dogmaAttributes.items()}, 'AttributeID', f)
with open(os.path.join(OUT, 'EffectID.hpp'), "w") as f:
    env['effectIDsMap'] = dumpIDs({k: v['effectName'] for k, v in dogmaEffects.items()}, 'EffectID', f)
with open(os.path.join(OUT, 'SchematicID.hpp'), "w") as f:
    env['schematicIDsMap'] = dumpIDs({k: v['nameID']['en'] for k, v in planetSchematics.items()}, 'SchematicID', f)
with open(os.path.join(OUT, 'WarfareBuffID.hpp'), "w") as f:
    env['warfareBuffIDsMap'] = dumpIDs({k: v['id'] for k, v in env['warfareBuffs'].items()}, 'WarfareBuffID', f)

with open(os.path.join(OUT, 'Attributes.hpp'), "w") as f:
    dumpAttributeTypes(env, f)
with open(os.path.join(OUT, 'Modifiers.hpp'), "w") as f:
    dumpModifiers(env, modifiers, f)
with open(os.path.join(OUT, 'Effects.hpp'), "w") as f:
    dumpEffects(env, modifiers,  f)
with open(os.path.join(OUT, 'Types.hpp'), "w") as f:
    dumpItems(env, f)
with open(os.path.join(OUT, 'WarfareBuffs.hpp'), "w") as f:
    dumpWarfareBuffs(env, f)
with open(os.path.join(OUT, 'Commodities.hpp'), "w") as f:
    dumpCommodities(env, f)
with open(os.path.join(OUT, 'Facilities.hpp'), "w") as f:
    dumpFacilities(env, f)
with open(os.path.join(OUT, 'Schematics.hpp'), "w") as f:
    dumpSchematics(env, f)
with open(os.path.join(OUT, 'Skills.hpp'), "w") as f:
    dumpSkills(env, f)

with open(os.path.join(OUT, 'Version.hpp'), "w") as f:
    x = datetime.date.today().strftime("%F")
    f.write("""#pragma once

namespace dgmpp {{
	const SDEVersion sdeVersion{{"{}"}};
}}
""".format(x))
