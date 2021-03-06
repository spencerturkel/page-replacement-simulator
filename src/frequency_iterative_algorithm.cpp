﻿#include <algorithm>
#include <functional>
#include <vector>

#include "../include/frequency_iterative_algorithm.h"

auto frequency_iterative_replacement_algorithm::page_used_less_than(const page& one, const page& two) -> bool
{
	return one.used < two.used;
}

namespace
{
  auto page_invalid(const page& p) -> bool
  {
	  return p.number == -1;
  }
}

frequency_state::frequency_state(const int page_table_size) : table(page_table_size, {-1 , -1})
{
}

frequency_state::frequency_state(page_table table): table(std::move(table))
{
}

auto frequency_iterative_replacement_algorithm::make_initial_state() const -> std::unique_ptr<state>
{
	return std::make_unique<frequency_state>(page_table_size);
}

auto frequency_iterative_replacement_algorithm::run_step(const state& current_state, const input& all_input,
                                                         const input_const_iter& current_input) const ->
run_step_result
{
	auto table = current_state.table;

	const auto found_page = std::find_if(table.begin(), table.end(), [&](const auto& page) -> auto
	{
		return page.number == *current_input;
	});

	const auto is_hit = found_page != table.cend();

	if (is_hit)
	{
		found_page->used++;
		std::make_heap(table.begin(), table.end(), compare);
	}
	else
	{
		const auto empty_entry = std::find_if(table.begin(), table.end(), page_invalid);

		if (empty_entry != table.cend())
		{
			*empty_entry = {*current_input, 1};

			if (std::none_of(table.cbegin(), table.cend(), page_invalid))
			{
				std::make_heap(table.begin(), table.end(), compare);
			}
		}
		else
		{
			std::pop_heap(table.begin(), table.end(), compare);
			table.pop_back();
			table.push_back({*current_input, 1});
			std::push_heap(table.begin(), table.end(), compare);
		}
	}

	auto pages_loaded = std::vector<int>{};

	for (const auto& page : table)
	{
		pages_loaded.push_back(page.number);
	}

	return {std::make_unique<state>(std::move(table)), {is_hit, pages_loaded}};
}

frequency_iterative_replacement_algorithm::
frequency_iterative_replacement_algorithm(std::string name, const int page_table_size, const comparator compare):
	iterative_replacement_algorithm(
		std::move(name), page_table_size), compare(std::move(compare))
{
}
