#include <unordered_set>

#include "optimal.h"
#include <algorithm>
#include <unordered_map>

optimal::optimal(int page_table_size) : replacement_algorithm("Optimal", page_table_size)
{
}

auto optimal::run(const std::vector<int>& input) -> trace_result const
{
	auto result = trace_result{};

	using page_number = int;
	using next_page_use_iterator = std::vector<int>::const_iterator;
	auto table = std::unordered_map<int, next_page_use_iterator>{};

	for (auto i = 1; i <= page_table_size_; ++i)
	{
		table.insert({i * -1, input.cend()});
	}

	for (auto input_iter = input.cbegin(); input_iter != input.cend(); ++input_iter)
	{
		const auto next_use = std::find(input_iter + 1, input.cend(), *input_iter);
		auto table_iter = table.find(*input_iter);

		if (table_iter == table.cend())
		{
			result.misses++;

			table.erase(std::max_element(table.cbegin(), table.cend(), [](auto first_pair, auto second_pair)
			{
				return first_pair.second < second_pair.second;
			}));

			table.insert({*input_iter, next_use});
		}
		else
		{
			result.hits++;
			table_iter->second = next_use;
		}
	}

	return result;
}
