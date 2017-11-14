#pragma once

#include <set>
#include <vector>

#include "iterative_replacement_algorithm.h"
#include <algorithm>

using lru_state = std::set<int>;

struct lru_iterative_replacement_algorithm : iterative_replacement_algorithm<lru_state>
{
	auto make_initial_state() const -> std::unique_ptr<state> override;
	auto run_step(const state& current_state, const input& all_input,
	              const input_const_iter& current_input) const -> run_step_result override;

	explicit lru_iterative_replacement_algorithm(const int page_table_size);
};
