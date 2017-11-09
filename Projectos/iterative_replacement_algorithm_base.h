#pragma once

#include <vector>
#include "step_result.h"

struct iterative_replacement_algorithm_base
{
		using input = std::vector<int>;
		using input_const_iter = input::const_iterator;

		const std::string name;
		const int page_table_size;

		iterative_replacement_algorithm_base(std::string name, const int page_table_size);

		virtual ~iterative_replacement_algorithm_base() = default;
};
