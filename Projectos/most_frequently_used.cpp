#include <limits>
#include <queue>

#include "most_frequently_used.h"

struct page
{
	int number;
	int used;
};

auto table_compare(const page& one, const page& two) -> bool
{
	return one.used < two.used;
}

most_frequently_used::most_frequently_used(const int page_table_size): replacement_algorithm("Most Frequently Used", page_table_size)
{
}

auto most_frequently_used::run(const std::vector<int>& input) -> trace_result const
{
	auto result = trace_result{};
	auto table = std::vector<page>{};

	for (auto i = 0; i < page_table_size_; ++i)
	{
		table.push_back({ -1,  std::numeric_limits<int>::max()});
	}

	std::make_heap(table.begin(), table.end(), table_compare);

	for (auto&& value : input)
	{
		const auto found_page = std::find_if(table.begin(), table.end(), [&](const auto& page) -> auto
		{
			return page.number == value;
		});

		if (found_page == table.cend())
		{
			std::pop_heap(table.begin(), table.end(), table_compare);
			table.pop_back();
			table.push_back({value, 1});
			std::push_heap(table.begin(), table.end(), table_compare);
			result.misses++;
		}
		else
		{
			result.hits++;
			found_page->used++;
			std::make_heap(table.begin(), table.end(), table_compare);
		}
	}

	return result;
}
