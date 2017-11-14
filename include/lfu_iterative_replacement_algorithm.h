#pragma once

#include "frequency_iterative_algorithm.h"

struct lfu_iterative_replacement_algorithm : frequency_iterative_replacement_algorithm
{
	explicit lfu_iterative_replacement_algorithm(const int page_table_size);
};
