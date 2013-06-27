#include "eufe.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <ios>
#include <queue>
#include <time.h>

using namespace eufe;

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cout<<"Usage: compiler source_database.sqlite output_dir"<<std::endl;
		return 0;
	}
	Compiler compiler = Compiler(argv[1], argv[2]);
	compiler.compile();
	return 0;
}