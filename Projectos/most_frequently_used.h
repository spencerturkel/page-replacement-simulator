#pragma once
#include "replacement_algorithm.h"
class most_frequently_used :
	public replacement_algorithm
{
public:
	explicit most_frequently_used(int most_frequently_used);
	~most_frequently_used() = default;

	auto run(const std::vector<int>& input) -> trace_result const override;
};

