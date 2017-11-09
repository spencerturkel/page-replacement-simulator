#include <iostream>
#include <memory>
#include <numeric>
#include <string>

#include "file_input_retriever.h"
#include "iterative_replacement_algorithm.h"
#include "fifo_iterative_replacement_algorithm.h"
#include "mfu_iterative_replacement_algorithm.h"
#include "optimal_iterative_replacement_algorithm.h"

template <typename Algorithm>
auto report_iterative_algorithm(const int& page_table_size, std::vector<int> trace, const bool print_steps) -> void
{
	const auto algorithm = Algorithm{page_table_size};
	const auto iterative_results = run_iterative_replacement_algorithm(algorithm, trace);

	std::cout << "Algorithm: " << algorithm.name << "\n";

	std::cout << "\tPage Table Size: " << page_table_size << '\n';
	std::cout << "\tInput: ";

	for (auto&& input : trace)
	{
		std::cout << input << ' ';
	}

	std::cout << "\n\tTotal Hits: " << std::accumulate(iterative_results.cbegin(), iterative_results.cend(), 0,
	                                                   [](const auto& left, const auto& right)
	                                                   {
		                                                   return left + int{right.is_hit};
	                                                   }) << "\n";

	if (!print_steps)
	{
		return;
	}

	std::cout << "\tPage Table Trace:\n";
	for (auto result_index = 0u; result_index < iterative_results.size(); ++result_index)
	{
		const auto& result = iterative_results[result_index];

		std::cout << "\t\tStep " << result_index << '\n';

		std::cout << "\t\t\tInput: " << trace[result_index] << '\n';
		std::cout << "\t\t\t" << (result.is_hit ? "Hit" : "Miss") << '\n';

		std::cout << "\t\t\tPages: ";

		for (auto&& page : result.page_table)
		{
			std::cout << page << ' ';
		}

		std::cout << '\n';
	}
}

auto make_retriever() -> std::unique_ptr<input_retriever>
{
	return std::make_unique<file_input_retriever>();
}

auto main() -> int
{
	const auto all_inputs = make_retriever()->retrieve();

	for (auto&& input : all_inputs)
	{
		report_iterative_algorithm<fifo_iterative_replacement_algorithm>(4, input, false);
		report_iterative_algorithm<mfu_iterative_replacement_algorithm>(4, input, true);
		report_iterative_algorithm<optimal_iterative_replacement_algorithm>(4, input, false);
	}

	std::cout << "Enter anything to exit...\n";

	std::cin.get();
}
