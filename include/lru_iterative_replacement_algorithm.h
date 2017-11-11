#pragma once

#include <set>
#include <vector>

#include "iterative_replacement_algorithm.h"
#include <algorithm>

namespace
{
	using lru_state = std::set<int>;

	struct lru_iterative_replacement_algorithm : iterative_replacement_algorithm<lru_state>
	{
		auto make_initial_state() const -> std::unique_ptr<state> override;
		auto run_step(const state& current_state, const input& all_input,
		              const input_const_iter& current_input) const -> run_step_result override;

		explicit lru_iterative_replacement_algorithm(const int page_table_size);
	};

	auto lru_iterative_replacement_algorithm::make_initial_state() const -> std::unique_ptr<state>
	{
		return std::make_unique<state>();
	}

	auto lru_iterative_replacement_algorithm::run_step(const state& current_state, const input& all_input,
	                                                   const input_const_iter& current_input) const -> run_step_result
	{
		auto table = current_state;
		const auto is_hit = std::find(table.cbegin(), table.cend(), *current_input) != table.cend();

		if (!is_hit)
		{
			if (current_state.size() == page_table_size)
			{
				const auto least_recently_used = std::accumulate(table.cbegin(), table.cend(),
				                                                 std::make_reverse_iterator(current_input),
				                                                 [&](const auto& least, const auto& page)
				                                                 {
					                                                 const auto last_use = std::find(
						                                                 std::make_reverse_iterator(current_input), all_input.crend(),
						                                                 page);
					                                                 return std::max(least, last_use);
				                                                 });
				table.erase(*least_recently_used);
			}

			table.insert(*current_input);
		}

		const auto vector = std::vector<int>{table.cbegin(), table.cend()};
		return {std::make_unique<state>(std::move(table)), {is_hit, vector}};
	}

	lru_iterative_replacement_algorithm::
	lru_iterative_replacement_algorithm(const int page_table_size) : iterative_replacement_algorithm<lru_state>(
		"Least Recently Used", page_table_size)
	{
	}
}
