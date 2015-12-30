#include "Blob.h"

using namespace dgmpp;

Blob::Blob(const void* memory, size_t size) : memory_(memory), size_(size)
{
}

Blob::~Blob(void)
{
}

const void* Blob::getMemory()
{
	return memory_;
}

size_t Blob::getSize()
{
	return size_;
}