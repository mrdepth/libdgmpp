# EVEUniverse Fitting Engine
Framework to calculate fitting stats for EVE Online writen on C++ with using Boost library.

Example
```plain
using namespace eufe;

Engine engine("eufe.sqlite");

boost::shared_ptr<Gang> gang = engine.getGang();
boost::shared_ptr<Character> character = gang->addPilot();
character1->setAllSkillsLevel(5);

boost::shared_ptr<Ship> gila = character1->setShip(17715); //17715 - Gila typeID
gila->addModule(10836); //10836 - Medium Shield Booster I typeID
gila->addModule(10836);
gila->addModule(10836);

float dps = gila->getWeaponDps();
Resistances resistances = gila->getResistances();
Tank tank gila->getEffectiveTank();
```