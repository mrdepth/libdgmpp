# Dogma++

Fitting engine for EVE Online written on C++

-------------------------------------------------------------------------------

## Requirements
- Python 2.7
- Reverence plugin for Python (https://github.com/ntt/reverence)
- Cygwin
- sqlite3
- Installed EVE Online client

-------------------------------------------------------------------------------

## Installation
- Change the EVEPATH variable in ./dbinit/dump/datadump.py to your EVE Online game client path.
- Run ./dbinit/build.sh to build dgm.sqlite (requires Cygwin or OS X/Linux)

-------------------------------------------------------------------------------

## Usage
	auto engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("path_to/dgm.sqlite"));
	auto pilot = engine->getGang()->addPilot();
	auto dominix = pilot->setShip(645); //Dominix typeID
	auto afterburner = dominix->addModule(12066); //100MN Afterburner I typeID
	afterburner->setPreferredState(Module::STATE_OVERLOADED);
	auto velocity = dominix->getVelocity();
