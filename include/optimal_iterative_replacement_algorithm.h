#pragma once

#include <vector>
#include <unordered_map>

#include "iterative_replacement_algorithm.h"

struct optimal_iterative_replacement_algorithm_state
{
	using next_page_use_iterator = std::vector<int>::const_iterator;
	using page_table = std::unordered_map<int, next_page_use_iterator>;

	page_table table;

	explicit optimal_iterative_replacement_algorithm_state(const int& page_table_size)
	{
		const auto vector = std::vector<int>{};

		for (auto i = 1; i <= page_table_size; ++i)
		{
			table.insert({-1 * i, vector.cend()});
		}
	}

	explicit optimal_iterative_replacement_algorithm_state(page_table table);
};

struct optimal_iterative_replacement_algorithm : iterative_replacement_algorithm<
		optimal_iterative_replacement_algorithm_state>
{
	optimal_iterative_replacement_algorithm(const int page_table_size);

	auto make_initial_state() const -> std::unique_ptr<state> override;
	auto run_step(const state& current_state, const input& all_input,
	              const input_const_iter& current_input) const -> run_step_result override;
};
