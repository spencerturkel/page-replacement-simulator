#include <algorithm>
#include "../include/fifo_iterative_replacement_algorithm.h"

auto fifo_iterative_replacement_algorithm::make_initial_state() const -> std::unique_ptr<state>
{
	return std::make_unique<state>(page_table_size);
}

auto fifo_iterative_replacement_algorithm::run_step(const state& current_state,
                                               const input& all_input,
                                               const input_const_iter& current_input) const -> run_step_result
{
	auto page_table = current_state.page_table;
	const auto is_hit = std::find(page_table.cbegin(), page_table.cend(), *current_input) != page_table.cend();

	if (!is_hit)
	{
		page_table.pop_front();
		page_table.push_back(*current_input);
	}

	return {
		std::make_unique<state>(page_table), {is_hit, {page_table.cbegin(), page_table.cend()}}
	};
}

fifo_iterative_replacement_algorithm::fifo_iterative_replacement_algorithm(const int page_table_size):
	iterative_replacement_algorithm<fifo_iterative_replacement_algorithm_state>("First In First Out",
	                                                                            page_table_size)
{
}
