#include <iostream>
#include <memory>
#include <numeric>
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

	//	const auto iterative = std::make_unique<fifo_iterative_replacement_algorithm>(4);
	//	const auto iterative_results = run_iterative_replacement_algorithm(*iterative, all_inputs.back());

	const auto iter = fifo_iterative_replacement_algorithm{4};
	const auto& iterative_input = all_inputs.back();
	const auto iterative_results = run_iterative_replacement_algorithm(iter, iterative_input);


	std::cout << "Algorithm: " << iter.name << "\n";

	std::cout << "\tInput: ";

	for (auto&& input : iterative_input)
	{
		std::cout << input << ' ';
	}

	std::cout << "\n\tTotal Hits: " << std::accumulate(iterative_results.cbegin(), iterative_results.cend(), 0,
	                                                   [](const auto& left, const auto& right)
	                                                   {
		                                                   return left + int{right.is_hit};
	                                                   }) << "\n";

	std::cout << "\tPage Table Trace:\n";
	for (auto result_index = 0u; result_index < iterative_results.size(); ++result_index)
	{
		const auto& result = iterative_results[result_index];

		std::cout << "\t\tStep " << result_index << '\n';

		std::cout << "\t\t\tInput: " << iterative_input[result_index] << '\n';
		std::cout << "\t\t\t" << (result.is_hit ? "Hit" : "Miss") << '\n';

		std::cout << "\t\t\tPages: ";

		for (auto&& page : result.page_table)
		{
			std::cout << page << ' ';
		}

		std::cout << '\n';
	}

	std::cout << "Enter anything to exit...\n";

	std::cin.get();
}
