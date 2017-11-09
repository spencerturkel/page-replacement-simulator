#include <iostream>
#include <memory>
#include <numeric>
#include <string>

#include <cxxopts.hpp>

#include "file_input_retriever.h"
#include "iterative_replacement_algorithm.h"
#include "fifo_iterative_replacement_algorithm.h"
#include "lfu_iterative_replacement_algorithm.h"
#include "lru_iterative_replacement_algorithm.h"
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

auto make_options(int& argc, char**& argv) -> cxxopts::Options
{
	using namespace cxxopts;

	auto options = Options{"PageReplacementSimulator", "OS Group Project"};

	options.add_options()
		("f,file", "An input file, where each line is formatted as specified in the --input option", value<std::string>())
		("input", "A space-seperated string of positive integers representing a memory trace", value<std::vector<int>>())
		("p,pages", "Number of pages in simulated page table", value<int>()->default_value("4"))
		("s,show-steps", "Show each state of the page table when running an algorithm")
		("a,alg,algorithm", "Choose the algorithm to run. Must be one of 'all', 'fifo', 'lfu', 'lru', 'mfu', or 'opt'",
		 value<std::string>()->default_value("all"));

	options.parse_positional("input");

	options.parse(argc, argv);
	return options;
}

auto main(int argc, char** argv) -> int
{
	const auto options_parser = make_options(argc, argv);
	const auto all_inputs = make_retriever()->retrieve();
	const auto alg = options_parser["alg"].as<std::string>();
	const auto pages = options_parser["pages"].as<int>();
	const auto show_steps = options_parser["show-steps"].as<bool>();

	for (auto&& input : all_inputs)
	{
		if (alg == "all" || alg == "fifo")
		{
			report_iterative_algorithm<fifo_iterative_replacement_algorithm>(pages, input, show_steps);
		}

		if (alg == "all" || alg == "lfu")
		{
			report_iterative_algorithm<lfu_iterative_replacement_algorithm>(pages, input, show_steps);
		}

		if (alg == "all" || alg == "lru")
		{
			report_iterative_algorithm<lru_iterative_replacement_algorithm>(pages, input, show_steps);
		}

		if (alg == "all" || alg == "mfu")
		{
			report_iterative_algorithm<mfu_iterative_replacement_algorithm>(pages, input, show_steps);
		}

		if (alg == "all" || alg == "opt")
		{
			report_iterative_algorithm<optimal_iterative_replacement_algorithm>(pages, input, show_steps);
		}
	}

	std::cout << "Enter anything to exit...\n";

	std::cin.get();
}
