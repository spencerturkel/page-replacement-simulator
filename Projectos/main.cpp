// project 4

#include <iostream>
#include <fstream>
#include <string>

#include "input_file_retriever.h"
#include "replacement_algorithm.h"
#include "first_in_first_out.h"
#include <memory>

int main()
{
	const auto algorithms = std::vector<std::unique_ptr<replacement_algorithm>>{std::make_unique<first_in_first_out>(4)};
	file_input_retriever retriever;

	const auto input = retriever.retrieve();

	for (auto&& alg : algorithms)
	{
		const auto trace = alg->run(input);
		std::cout << "Algorithm: " << alg->name << '\n';
		std::cout << "\tHits: " << trace.hits << '\n';
		std::cout << "\tMisses: " << trace.misses << "\n\n";
	}

	for (auto&& value : input)
	{
		std::cout << "Value: " << value << "\n";
	}

	std::cout << "Done reading\n";

	int n;
	std::cin >> n;
}
