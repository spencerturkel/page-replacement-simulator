#pragma once

#include "frequency_iterative_algorithm.h"

namespace
{
	auto page_used_greater_than(const page& left, const page& right) -> bool
	{
		return left.used > right.used;
	}

	struct lfu_iterative_replacement_algorithm : frequency_iterative_replacement_algorithm
	{
		explicit lfu_iterative_replacement_algorithm(const int page_table_size);
	};

	lfu_iterative_replacement_algorithm::lfu_iterative_replacement_algorithm(const int page_table_size)
		: frequency_iterative_replacement_algorithm("Least Frequently Used", page_table_size, page_used_greater_than)
	{
	}
}
