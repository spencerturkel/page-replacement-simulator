// project 4

#include <iostream>
#include <fstream>
#include <string>

#include "input_file_retriever.h"

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
