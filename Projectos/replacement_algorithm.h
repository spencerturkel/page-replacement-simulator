#pragma once

#include <string>
#include <vector>

#include "trace_result.h"

class replacement_algorithm
{
public:
	const std::string name;

	virtual auto run(const std::vector<int>& input) -> trace_result const = 0;

//	replacement_algorithm(const replacement_algorithm&) = default;
//	replacement_algorithm(replacement_algorithm&&) = default;
//	replacement_algorithm& operator=(const replacement_algorithm&) = default;
//	replacement_algorithm& operator=(replacement_algorithm&&) = default;
	virtual ~replacement_algorithm() = default;
protected:
	int page_table_size_;
	explicit replacement_algorithm(int page_table_size);
};
