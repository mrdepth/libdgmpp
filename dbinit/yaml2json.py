import os
import sys
import yaml
import json

def yaml2json(path):
    with open(path, 'r', encoding='utf-8') as f:
        out = os.path.splitext(path)[0] + '.json'
        obj = yaml.load(f.read(), yaml.CLoader)
        with open(out, 'w', encoding='utf-8') as fout:
            json.dump(obj, fout)
        

dir='./tmp/sde/bsd'
files = [x for x in os.listdir(dir) if os.path.splitext(x)[1] == '.yaml']
for x in files:
    yaml2json(os.path.join(dir, x))

#print(sys.argv)
#yaml.load(Loader = yaml.CLoader)
