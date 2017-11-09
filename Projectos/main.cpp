#include <iostream>
#include <memory>
#include <string>

#include "file_input_retriever.h"
#include "first_in_first_out.h"
#include "iterative_replacement_algorithm.h"
#include "optimal.h"
#include "most_frequently_used.h"
#include "replacement_algorithm.h"
#include "least_recently_used.h"
#include "least_frequently_used.h"
#include "fifo_iterative_replacement_algorithm.h"
#include <numeric>

auto make_retriever() -> std::unique_ptr<input_retriever>
{
	return std::make_unique<file_input_retriever>();
}

auto make_algorithms() -> std::vector<std::unique_ptr<replacement_algorithm>>
{
	auto algorithms = std::vector<std::unique_ptr<replacement_algorithm>>{};

	constexpr auto number_of_pages = 4;

	algorithms.emplace_back(std::make_unique<first_in_first_out>(number_of_pages));
	algorithms.emplace_back(std::make_unique<optimal>(number_of_pages));
	algorithms.emplace_back(std::make_unique<most_frequently_used>(number_of_pages));
	algorithms.emplace_back(std::make_unique<least_recently_used>(number_of_pages));
	algorithms.emplace_back(std::make_unique<least_frequently_used>(number_of_pages));

	return algorithms;
}

auto main() -> int
{
	const auto algorithms = make_algorithms();
	const auto retriever = make_retriever();

	const auto all_inputs = retriever->retrieve();

	for (auto&& input : all_inputs)
	{
		std::cout << "Input: ";

		for (auto&& value : input)
		{
			std::cout << value << ' ';
		}

		std::cout << '\n';

		for (auto&& alg : algorithms)
		{
			const auto trace = alg->run(input);
			std::cout << "\tAlgorithm: " << alg->name << '\n';
			std::cout << "\t\tHits: " << trace.hits << '\n';
			std::cout << "\t\tMisses: " << trace.misses << "\n\n";
		}
	}

	const auto iterative = std::make_unique<fifo_iterative_replacement_algorithm>(4);

	const auto iterative_results = run_iterative_replacement_algorithm(*iterative, all_inputs.back());

	std::cout << "Iterative results\n";
	std::cout << "\tTotal Hits: " << std::accumulate(iterative_results.cbegin(), iterative_results.cend(), 0,
	                                                 [](const auto& left, const auto& right)
	                                                 {
		                                                 return left + int{right.is_hit};
	                                                 }) << "\n";

	std::cout << "\tPage Table Trace:\n";
	for (auto&& result : iterative_results)
	{
		std::cout << "\t\tPages: ";

		for (auto&& page : result.page_table)
		{
			std::cout << page << ' ';
		}

		std::cout << '\n';
	}

	std::cout << "Enter anything to exit...\n";

	std::cin.get();
}
