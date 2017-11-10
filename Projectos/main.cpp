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

auto make_options(char* name) -> cxxopts::Options
{
	using namespace cxxopts;
	using std::string;

	auto options = Options{name};

	options.positional_help("{space seperated positive integer page references}");
	options.parse_positional("input");

	options.add_options()
		("f,file", "An input file, where each line has space seperated positive integer page references",
		 value<string>()->default_value("PageFile"))
		("i,input", "Space seperated positive integer page references", cxxopts::value<std::vector<string>>())
		("h,help", "Print help")
		("p,pages", "Number of pages in simulated page table", value<int>()->default_value("4"))
		("s,steps", "Show each state of the page table when running an algorithm")
		("a,algorithm", "Choose the algorithm to run. Must be one of 'all', 'fifo', 'lfu', 'lru', 'mfu', or 'opt'",
		 value<string>()->default_value("all"));

	return options;
}

auto parse_input(const std::vector<std::string>& input) -> std::vector<int>
{
	//	std::cout << "Input was: " << input << "\n";
	//	auto ss = std::stringstream{input};
	//	auto next = int{};
	//	auto result = std::vector<int>{};
	//
	//	while (ss >> next)
	//	{
	//		if (next < 0)
	//		{
	//			throw std::runtime_error{"Input page numbers must not be negative"};
	//		}
	//
	//		result.push_back(next);
	//	}

	//	return result;

	auto result = std::vector<int>(input.size());

	std::transform(input.cbegin(), input.cend(), result.begin(), [](const std::string& str)
	{
		try
		{
			return std::stoi(str);
		}
		catch(std::exception)
		{
			throw std::runtime_error{ "Could not convert '" + str + "' to a page reference number" };
		}
	});

	return result;
}

auto run_from_options(const cxxopts::Options& options) -> void
{
	using std::string;

	const auto alg = options["algorithm"].as<std::string>();
	const auto pages = options["pages"].as<int>();
	const auto show_steps = static_cast<bool>(options.count("steps"));

	const auto all_inputs = options["file"].count() > 0 || options["input"].count() == 0
		                        ? file_input_retriever{
			                        options["file"].as<std::string>()
		                        }.retrieve()
		                        //		                        : std::vector<std::vector<int>>{parse_input(options["input"].as<string>())};
		                        : std::vector<std::vector<int>>{parse_input(options["input"].as<std::vector<string>>())};

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
}

auto on_exit(const int result) -> int
{
#ifdef _DEBUG
	std::cout << "Enter anything to exit...\n";

	std::cin.get();
#endif

	return result;
};

auto main(int argc, char** argv) -> int
{
	auto options = make_options(argv[0]);

	try
	{
		options.parse(argc, argv);

		if (options.count("help"))
		{
			std::cout << options.help();
			return on_exit(0);
		}

		run_from_options(options);
	}
	catch (cxxopts::OptionException exception)
	{
		std::cerr << exception.what() << "\n";
		std::cout << options.help() << "\n";
		return on_exit(1);
	}
	catch (std::runtime_error error)
	{
		std::cerr << error.what() << "\n";
		std::cout << options.help() << "\n";
		return on_exit(1);
	}

	return on_exit(0);
}
