#include "Decoder.h"

using namespace eufe;

Decoder::Decoder(const char* filePath)
{
	if_ = fopen(filePath, "rb");
}

Decoder::~Decoder(void)
{
	if (if_)
		fclose(if_);
}

void Decoder::decode(std::string& value)
{
	std::string::size_type len;
	decode(len);
	char* buf = new char[len];
	fread(buf, len, 1, if_);
	value = buf;
	free(buf);
}