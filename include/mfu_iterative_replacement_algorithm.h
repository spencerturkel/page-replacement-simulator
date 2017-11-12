#pragma once

#include "frequency_iterative_algorithm.h"

struct mfu_iterative_replacement_algorithm : frequency_iterative_replacement_algorithm
{
	explicit mfu_iterative_replacement_algorithm(int page_table_size);
};


mfu_iterative_replacement_algorithm::
mfu_iterative_replacement_algorithm(const int page_table_size): frequency_iterative_replacement_algorithm(
	"Most Frequently Used", page_table_size, page_used_less_than)
{
}
