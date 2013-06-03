#pragma once
#include <stdio.h>
#include <string>

namespace eufe
{

	class Decoder
	{
	public:
		Decoder(const char* filePath);
		~Decoder(void);
		template<class T> void decode(T& value)
		{
			fread(&value, sizeof(value), 1, if_);
		}
		void decode(std::string& value);
	private:
		FILE* if_;
	};

}