#include <fstream>

#include "input_file_retriever.h"


std::vector<int> file_input_retriever::retrieve() const
{
	auto current_int = int{};
	auto result = std::vector<int>{};
	auto inputstream = std::ifstream{"inputfile", std::ios_base::binary};

	inputstream >> std::ws;

	while (inputstream >> current_int)
	{
		result.push_back(current_int);
	}

	return result;
}
