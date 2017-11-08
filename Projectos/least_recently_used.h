#pragma once
// least_recently_used.h
// LRU page replacement algorithm header

#include "replacement_algorithm.h"

class least_recently_used :
	public replacement_algorithm
{
public:
	auto run(const std::vector<int>& input)-> const trace_result override;

	explicit least_recently_used(int page_table_size);
	~least_recently_used() = default;
};