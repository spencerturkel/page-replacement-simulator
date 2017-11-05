#include <iostream>
#include <memory>
#include <string>

#include "file_input_retriever.h"
#include "first_in_first_out.h"
#include "replacement_algorithm.h"
#include "most_frequently_used.h"

auto make_retriever() -> std::unique_ptr<input_retriever>
{
	return std::make_unique<file_input_retriever>();
}

auto make_algorithms() -> std::vector<std::unique_ptr<replacement_algorithm>>
{
	auto algorithms = std::vector<std::unique_ptr<replacement_algorithm>>{};

	constexpr auto number_of_pages = 4;

	algorithms.emplace_back(std::make_unique<first_in_first_out>(number_of_pages));
	algorithms.emplace_back(std::make_unique<most_frequently_used>(number_of_pages));

	return algorithms;
}

auto main() -> int
{
	const auto algorithms = make_algorithms();
	const auto retriever = make_retriever();

	const auto input = retriever->retrieve();

	for (auto&& alg : algorithms)
	{
		const auto trace = alg->run(input);
		std::cout << "Algorithm: " << alg->name << '\n';
		std::cout << "\tHits: " << trace.hits << '\n';
		std::cout << "\tMisses: " << trace.misses << "\n\n";
	}

	std::cout << "Enter anything to exit...\n";

	std::cin.get();
}
