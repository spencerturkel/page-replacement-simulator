// least_frequently_used.cpp
// LFU algorithm

#include "least_frequently_used.h"
#include <iostream>
#define PFRAMES 4
#define PAGES 50

least_frequently_used::least_frequently_used(const int page_table_size) : replacement_algorithm("Least Frequently Used", page_table_size)
{
}

auto least_frequently_used::run(const std::vector<int>& input) -> const trace_result
{
	// initialize variables
	auto result = trace_result{};
	int frames[PFRAMES]; 
	int pos[PAGES], time[PAGES];
	int temp;

	for (auto i = 0; i < page_table_size_; ++i) {
		frames[i] = -1;
	}

	for (auto i = 0; i < PAGES; ++i) {
		pos[i] = 0;
	}

	int position = 0;
	// loop over all pages
	while (position < input.size())
	{
		pos[input[position]]++;
		time[input[position]] = position;
		int flag = 1;
		int stamp = frames[0];
		int state;
		// loop over frames
		for (state = 0; state < page_table_size_; ++state)
		{
			if (frames[state] == -1 || frames[state] == input[position])
			{
				if (frames[state] != -1)
				{
					result.hits++;
				}
				flag = 0;
				frames[state] = input[position];
				break;
			}
			if (pos[stamp] > pos[frames[state]])
			{
				stamp = frames[state];
			}
		}
		if (flag)
		{
			int min = PAGES;
			for (state = 0; state < page_table_size_; ++state)
			{
				if (pos[frames[state]] == pos[stamp] && time[frames[state]] < min)
				{
					temp = state;
					min = time[frames[state]];
				}
			}
			pos[frames[temp]] = 0;
			frames[temp] = input[position];
		}
		if (position == 0) {
			std::cout << "-------------------" << std::endl;
		}
		for (int i = 0; i < PFRAMES; ++i)
		{
			std::cout << frames[i] << " ";
		}
		std::cout << std::endl;
		position++;
	}
	result.misses = input.size() - result.hits;
	return result;
}