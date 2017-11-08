#pragma once
// least_frequently_used
// LFU algorithm header

#include "replacement_algorithm.h"

class least_frequently_used :
	public replacement_algorithm
{
public:
	auto run(const std::vector<int>& input)-> const trace_result override;

	explicit least_frequently_used(int page_table_size);
	~least_frequently_used() = default;
};
