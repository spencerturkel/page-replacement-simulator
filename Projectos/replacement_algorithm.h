#pragma once

#include <string>
#include <vector>
#include "trace_result.h"

class replacement_algorithm
{
public:
	const std::string name;

	virtual auto run(const std::vector<int>& input) -> trace_result const = 0;

	virtual ~replacement_algorithm() = default;
protected:
	int page_table_size_;
	explicit replacement_algorithm(int page_table_size);
};

inline replacement_algorithm::replacement_algorithm(const int page_table_size): page_table_size_(page_table_size)
{
}
