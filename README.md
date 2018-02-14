# Dogma++

Fitting engine for EVE Online written on C++

-------------------------------------------------------------------------------

## Requirements
- C++17 compiler

-------------------------------------------------------------------------------

## Installation
- Add sources from './src' to the project
- Include 'dgmpp.hpp'
-------------------------------------------------------------------------------

## Usage
	#include <iostream>
	#include "dgmpp.hpp"

	using namespace dgmpp;
	
	void main() {
		auto gang = Gang::Create();
		auto pilot = gang->addPilot();
		pilot->setSkillLevels(5);
		auto ship = pilot->ship(TypeID::dominix);
	
		auto ab = ship->addModule(TypeID::_100MNAfterburnerII);
		ab->state(Module::State::overloaded);
	
		std::cout << "Velocity: " << ship->velocity().count() << " m/s" << std::endl;
	}

