#pragma once
#include <stdio.h>
#include <string>

namespace eufe {

	class Encoder
	{
	public:
		Encoder(const char* filePath);
		~Encoder(void);
		//void encode(int value);
		//void encode(size_t value);
		//void encode(float value);
		//void encode(const std::string& value);
		template<class T> void encode(T value)
		{
			fwrite(&value, sizeof(value), 1, of_);
		}
		void encode(const std::string& value);
	private:
		FILE* of_;
	};

}