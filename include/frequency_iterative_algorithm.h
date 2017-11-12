#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "iterative_replacement_algorithm.h"

struct page
{
	int number;
	int used;
};

struct frequency_state
{
	using page_table = std::vector<page>;
	page_table table;

	explicit frequency_state(const int page_table_size);
	explicit frequency_state(page_table table);
};

struct frequency_iterative_replacement_algorithm : iterative_replacement_algorithm<frequency_state>
{
	using comparator = std::function<bool(const page&, const page&)>;
	comparator compare;
  static auto page_used_less_than(const page& one, const page& two) -> bool;

	auto make_initial_state() const -> std::unique_ptr<state> override;
	auto run_step(const state& current_state, const input& all_input,
	              const input_const_iter& current_input) const -> run_step_result override;

	explicit frequency_iterative_replacement_algorithm(std::string name, int page_table_size, comparator compare);
};
