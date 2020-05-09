import os
import sys
import json
from utility import *
from patch import *
import io

validCategoryIDs = [1, 2, 4, 8, 17, 18, 20, 7, 6, 16, 23, 32, 41, 42, 43, 65, 66, 87]

SDE='./tmp/sde/'

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

with open(os.path.join(SDE, 'bsd/dgmEffects.json')) as f:
    dgmEffects = {v['effectID']: v for v in json.load(f)}
    dgmEffects = {k: v for k, v in dgmEffects.items() if k in validEffectIDs}

with open(os.path.join(SDE, 'fsd/metaGroups.json')) as f:
    metaGroups = {int(k): v for k,v in json.load(f).items()}
    metaGroupIDsMap = {k: safeName(v['nameID']['en']) for k, v in metaGroups.items()}

with open(os.path.join(SDE, 'bsd/planetSchematics.json')) as f:
    planetSchematics = {v['schematicID']: v for v in json.load(f)}

with open(os.path.join(SDE, 'bsd/planetSchematicsPinMap.json')) as f:
    planetSchematicsPinMap = json.load(f)

with open(os.path.join(SDE, 'bsd/planetSchematicsTypeMap.json')) as f:
    planetSchematicsTypeMap = json.load(f)

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
       'planetSchematics': planetSchematics,
       'planetSchematicsPinMap': planetSchematicsPinMap,
       'planetSchematicsTypeMap': planetSchematicsTypeMap}

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

env['categoryIDsMap'] = dumpIDs({k: getName(v) for k, v in categoryIDs.items()}, 'CategoryID', devnull)
env['groupIDsMap'] = dumpIDs({k: getName(v) for k, v in groupIDs.items()}, 'GroupID', devnull)
env['typeIDsMap'] = dumpIDs({k: getName(v) for k, v in typeIDs.items()}, 'TypeID', devnull)
env['attributeIDsMap'] = dumpIDs({k: v['name'] for k, v in dogmaAttributes.items()}, 'AttributeID', devnull)
env['effectIDsMap'] = dumpIDs({k: v['effectName'] for k, v in dogmaEffects.items()}, 'EffectID', devnull)
env['schematicIDsMap'] = dumpIDs({k: v['schematicName'] for k, v in planetSchematics.items()}, 'SchematicID', devnull)
env['warfareBuffIDsMap'] = dumpIDs({k: next(iter(v.values()))['id'] for k, v in env['warfareBuffs'].items()}, 'WarfareBuffID', devnull)
#dumpAttributes(env, attributeIDsMap, sys.stdout)
#dumpModifiers(env, modifiers, attributeIDsMap, typeIDsMap, groupIDsMap, sys.stdout)
#dumpEffects(env, modifiers,  sys.stdout)
#dumpItems(env, sys.stdout)
#dumpWarfareBuffs(env, sys.stdout)
#dumpCommodities(env, sys.stdout)
#dumpFacilities(env, sys.stdout)
dumpSchematics(env, sys.stdout)