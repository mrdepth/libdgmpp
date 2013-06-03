#include "Encoder.h"

using namespace eufe;

Encoder::Encoder(const char* filePath)
{
	of_ = fopen(filePath, "wb");
}

Encoder::~Encoder(void)
{
	if (of_)
		fclose(of_);
}

/*void Encoder::encode(int value)
{
	fwrite(&value, sizeof(value), 1, of_);
}

void Encoder::encode(float value)
{
	fwrite(&value, sizeof(value), 1, of_);
}

void Encoder::encode(size_t value)
{
	fwrite(&value, sizeof(value), 1, of_);
}
*/

void Encoder::encode(const std::string& value)
{
	int len = value.length();
	encode(len);
	fwrite(value.c_str(), sizeof(char), len, of_);
}
