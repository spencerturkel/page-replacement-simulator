#pragma once
#include "input_retriever.h"

struct file_input_retriever : public input_retriever
{
	std::vector<std::vector<int>> retrieve() const override;
};
