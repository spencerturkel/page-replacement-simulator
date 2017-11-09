#pragma once

#include <cassert>
#include <deque>

#include "iterative_replacement_algorithm.h"
#include <algorithm>

namespace
{
	struct fifo_iterative_replacement_algorithm;

	template <>
	struct state<fifo_iterative_replacement_algorithm>
	{
		using queue = std::deque<int>;
		queue page_table;

		explicit state(const int page_table_size) : page_table(page_table_size, -1)
		{
			assert(page_table_size >= 0);
		}

		explicit state(const queue page_table) : page_table(page_table)
		{
		}
	};

	struct fifo_iterative_replacement_algorithm : iterative_replacement_algorithm<fifo_iterative_replacement_algorithm>
	{
		explicit fifo_iterative_replacement_algorithm(const int page_table_size);

		auto make_initial_state() const -> std::unique_ptr<derived_state> override;
		auto run(const derived_state& current_state, const input& all_input, const input_const_iter& current_input) const -> run_result override;
	};
}
