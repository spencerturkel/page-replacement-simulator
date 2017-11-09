#include <fstream>
#include <string>
#include <sstream>

#include "file_input_retriever.h"

file_input_retriever::file_input_retriever(std::string file_name): file_name(std::move(file_name))
{
}

auto file_input_retriever::retrieve() const -> std::vector<std::vector<int>>
{
	auto result = std::vector<std::vector<int>>{};
	auto input_stream = std::ifstream{"inputfile", std::ios_base::binary};

	auto line = std::string{};

	while (std::getline(input_stream >> std::ws, line))
	{
		auto line_result = std::vector<int>{};
		auto line_stream = std::stringstream{line};
		auto current_int = int{};

		while (line_stream >> current_int)
		{
			line_result.push_back(current_int);
		}

		result.push_back(line_result);
	}

	return result;
}
