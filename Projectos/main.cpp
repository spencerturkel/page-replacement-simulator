// project 4

#include <iostream>
#include "input_retriever.h"
#include <fstream>
#include <string>
#include <sstream>

struct file_input_retriever : public input_retriever
{
	std::vector<int> retrieve() const override
	{
		auto result = std::vector<int>{};
		auto inputstream = std::ifstream{"inputfile.dat"};

		std::string line;
		std::cout << "Reading line\n";
		while (getline(inputstream, line))
		{
			if (line == "stop")
			{
				break;
			}
			int current_int;
//			std::stringstream ss{line};
			std::cout << "Line: " << line << '\n';
			inputstream >> current_int;
			result.push_back(current_int);

//			while (ss >> current_int)
//			{
//				std::cout << "current_int: " << current_int << '\n';
//				result.push_back(current_int);
//			}
		}

		return result;
	}
};

int main()
{
	file_input_retriever retriever;

	const auto result = retriever.retrieve();

	for (auto&& value : result)
	{
		std::cout << "Value: " << value << "\n";
	}

	std::cout << "Done reading\n";

	int n;
	std::cin >> n;
}
