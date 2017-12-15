#include "Cargo.h"

using namespace dgmpp;


Cargo::Cargo(std::shared_ptr<Item> const& item, size_t count): item_(item), count(count)
{
	
}

Cargo::~Cargo(void)
{
	
}

std::shared_ptr<Item> Cargo::getItem()
{
	return item_;
}
