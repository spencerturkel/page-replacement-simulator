#pragma once
#include "input_retriever.h"

struct file_input_retriever : input_retriever
{
	std::string file_name;

	explicit file_input_retriever(std::string file_name);

	std::vector<std::vector<int>> retrieve() const override;
};
