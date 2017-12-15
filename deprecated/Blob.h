#pragma once
#include "types.h"

namespace dgmpp {

	class Blob
	{
	public:
		Blob(const void* memory, size_t size);
		~Blob(void);
		const void* getMemory();
		size_t getSize();
	private:
		const void* memory_;
		size_t size_;
	};
}