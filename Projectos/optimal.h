#pragma once
#include "replacement_algorithm.h"
class optimal :
	public replacement_algorithm
{
public:
	explicit optimal(int page_table_size);
	auto run(const std::vector<int>& input) -> trace_result const override;
};

