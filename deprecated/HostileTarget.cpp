//
//  HostileTarget.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 30.11.15.
//
//

#include "HostileTarget.h"

using namespace dgmpp;

const HostileTarget HostileTarget::defaultTarget = HostileTarget();

HostileTarget::HostileTarget(Float range, Float angularVelocity, Float signature, Float velocity): range(range), angularVelocity(angularVelocity), signature(signature), velocity(velocity) {
	
}
