#pragma once

#include <deque>

#include "iterative_replacement_algorithm.h"

	struct fifo_iterative_replacement_algorithm_state
	{
		using queue = std::deque<int>;
		queue page_table;

		explicit fifo_iterative_replacement_algorithm_state(const int page_table_size) : page_table(page_table_size, -1)
		{
		}

		explicit fifo_iterative_replacement_algorithm_state(const queue page_table) : page_table(page_table)
		{
		}
	};

	struct fifo_iterative_replacement_algorithm : iterative_replacement_algorithm<
			fifo_iterative_replacement_algorithm_state>
	{
		explicit fifo_iterative_replacement_algorithm(const int page_table_size);

		auto make_initial_state() const -> std::unique_ptr<state> override;
		auto run_step(const state& current_state, const input& all_input,
		         const input_const_iter& current_input) const -> run_step_result override;
	};
