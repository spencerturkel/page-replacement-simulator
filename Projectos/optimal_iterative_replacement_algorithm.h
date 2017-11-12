#pragma once

#include <vector>
#include <unordered_map>
#include "iterative_replacement_algorithm.h"
#include <algorithm>

namespace
{
	struct optimal_iterative_replacement_algorithm_state
	{
		using next_page_use_iterator = std::vector<int>::const_iterator;
		using page_table = std::unordered_map<int, next_page_use_iterator>;

		page_table table;

		explicit optimal_iterative_replacement_algorithm_state(const int& page_table_size)
		{
//			table.reserve(page_table_size);
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

	optimal_iterative_replacement_algorithm::optimal_iterative_replacement_algorithm(const int page_table_size)
		: iterative_replacement_algorithm<optimal_iterative_replacement_algorithm_state>(
			"Optimal", page_table_size)
	{
	}

	optimal_iterative_replacement_algorithm_state::optimal_iterative_replacement_algorithm_state(page_table table) : table(
		std::move(table))
	{
	}

	auto optimal_iterative_replacement_algorithm::make_initial_state() const -> std::unique_ptr<state>
	{
		return std::make_unique<state>(page_table_size);
	}

	using state = optimal_iterative_replacement_algorithm::state;
	using run_step_result = optimal_iterative_replacement_algorithm::run_step_result;

	auto make_step_result(state::page_table table, const bool is_hit) -> run_step_result
	{
		auto vector = std::vector<int>{};

		for (auto&& page : table)
		{
			vector.push_back(page.first);
		}

		return {
			std::make_unique<optimal_iterative_replacement_algorithm_state>(table), {is_hit, vector}
		};
	}

	auto optimal_iterative_replacement_algorithm::run_step(const state& current_state, const input& all_input,
	                                                       const input_const_iter& current_input) const -> run_step_result
	{
		const auto next_use = std::find(current_input + 1, all_input.cend(), *current_input);
		auto table = current_state.table;
		auto table_iter = table.find(*current_input);

		if (table_iter == table.cend())
		{
			auto unassigned_page = std::find_if(table.cbegin(), table.cend(), [](auto pair)
			{
				return pair.first < 0;
			});

			if (unassigned_page == table.cend())
			{
				const auto page_used_furthest_in_future = std::max_element(table.cbegin(), table.cend(),
				                                                           [](auto first_pair, auto second_pair)
				                                                           {
					                                                           return second_pair.first < 0 || first_pair.second <
						                                                           second_pair.second;
				                                                           });

				table.erase(page_used_furthest_in_future);
			}
			else
			{
				table.erase(unassigned_page);
			}

			table.insert({*current_input, next_use});
			return make_step_result(std::move(table), false);
		}

		table_iter->second = next_use;
		return make_step_result(std::move(table), true);
	}
}
