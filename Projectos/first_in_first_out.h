#pragma once
#include "replacement_algorithm.h"

class first_in_first_out :
	public replacement_algorithm
{
public:
	const std::string name = "First In First Out";
	auto run(const std::vector<int>& input)-> const trace_result override;

	explicit first_in_first_out(int page_table_size);
//	~first_in_first_out();
};

