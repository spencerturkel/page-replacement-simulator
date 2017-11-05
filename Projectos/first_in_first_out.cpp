#include "first_in_first_out.h"
#include <deque>

auto first_in_first_out::run(const std::vector<int>& input) -> const trace_result
{
	auto result = trace_result{0, 0};
	std::deque<int> page_table;

	for (auto i = 0; i < page_table_size_; ++i)
	{
		page_table.push_back(-1);
	}

	for (auto&& value : input)
	{
		if (std::find(page_table.cbegin(), page_table.cend(), value) == page_table.cend())
		{
			result.misses++;
			page_table.pop_front();
			page_table.push_back(value);
		}
		else
		{
			result.hits++;
		}
	}

	return result;
}

first_in_first_out::first_in_first_out(const int page_table_size): replacement_algorithm(page_table_size)
{
}


first_in_first_out::~first_in_first_out()
{
}
