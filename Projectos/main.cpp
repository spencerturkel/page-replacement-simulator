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
