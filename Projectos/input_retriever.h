#pragma once
#include <vector>

struct input_retriever
{
	virtual ~input_retriever() = default;

	virtual std::vector<int> retrieve() const = 0;
};
