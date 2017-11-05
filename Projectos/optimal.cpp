#include "optimal.h"

optimal::optimal(int page_table_size) : replacement_algorithm("Optimal", page_table_size)
{
}

auto optimal::run(const std::vector<int>& input) -> trace_result const
{
	auto result = trace_result{};
	return result;
}
