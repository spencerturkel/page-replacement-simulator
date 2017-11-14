#pragma once

#include "frequency_iterative_algorithm.h"

struct mfu_iterative_replacement_algorithm : frequency_iterative_replacement_algorithm
{
	explicit mfu_iterative_replacement_algorithm(int page_table_size);
};

