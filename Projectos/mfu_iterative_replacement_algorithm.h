#pragma once

#include "iterative_replacement_algorithm.h"
#include <vector>
#include <algorithm>

namespace
{
	struct page
	{
		int number;
		int used;
	};

	auto page_invalid(const page& p) -> bool
	{
		return p.number == -1;
	}

	auto operator<(const page& one, const page& two) -> bool
	{
		return one.used < two.used;
	}

	struct mfu_state
	{
		using page_table = std::vector<page>;
		page_table table;

		explicit mfu_state(const int page_table_size);
		explicit mfu_state(page_table table);
	};

	mfu_state::mfu_state(const int page_table_size) : table(page_table_size, {-1 , -1})
	{
	}

	mfu_state::mfu_state(page_table table): table(std::move(table))
	{
	}

	struct mfu_iterative_replacement_algorithm : iterative_replacement_algorithm<mfu_state>
	{
		auto make_initial_state() const -> std::unique_ptr<state> override;
		auto run_step(const state& current_state, const input& all_input,
		              const input_const_iter& current_input) const -> run_step_result override;

		explicit mfu_iterative_replacement_algorithm(int page_table_size);
	};

	auto mfu_iterative_replacement_algorithm::make_initial_state() const -> std::unique_ptr<state>
	{
		return std::make_unique<mfu_state>(page_table_size);
	}

	auto mfu_iterative_replacement_algorithm::run_step(const state& current_state, const input& all_input,
	                                                   const input_const_iter& current_input) const -> run_step_result
	{
		auto table = current_state.table;
		auto is_hit = bool{};

		const auto empty_entry = std::find_if(table.begin(), table.end(), page_invalid);

		if (empty_entry != table.cend())
		{
			*empty_entry = {*current_input, 1};

			if (std::none_of(table.cbegin(), table.cend(), page_invalid))
			{
				std::make_heap(table.begin(), table.end());
			}
		}
		else
		{
			const auto found_page = std::find_if(table.begin(), table.end(), [&](const auto& page) -> auto
			{
				return page.number == *current_input;
			});

			is_hit = found_page != table.cend();

			if (is_hit)
			{
				found_page->used++;
				std::make_heap(table.begin(), table.end());
			}
			else
			{
				std::pop_heap(table.begin(), table.end());
				table.pop_back();
				table.push_back({*current_input, 1});
				std::push_heap(table.begin(), table.end());
			}
		}

		auto pages_loaded = std::vector<int>{};

		for (const auto& page : table)
		{
			pages_loaded.push_back(page.number);
		}

		return {std::make_unique<state>(std::move(table)), {is_hit, pages_loaded}};
	}

	mfu_iterative_replacement_algorithm::
	mfu_iterative_replacement_algorithm(const int page_table_size): iterative_replacement_algorithm(
		"Most Frequently Used", page_table_size)
	{
	}
}
