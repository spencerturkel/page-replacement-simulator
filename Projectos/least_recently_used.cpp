// least_recently_used.cpp
// LRU page replacement algorithm

#include "least_recently_used.h"
#define PFRAMES 4

least_recently_used::least_recently_used(const int page_table_size) : replacement_algorithm("Least Recently Used", page_table_size)
{
}

auto least_recently_used::run(const std::vector<int>& input) -> const trace_result
{
	auto result = trace_result{};
	int frames[PFRAMES], count[PFRAMES];

	for (auto i = 0; i < page_table_size_; ++i) {
		frames[i] = -1;
		count[i] = 0;
	}

	int position = 0;
	while(position < input.size()) {

		int state = 0, flag = 0; 

		while (state < page_table_size_) {
			// check if current page is in the frames
			if (input[position] == frames[state]) {
				flag = 1;
				count[state] = position + 1;
			}
			state++;
		}
		state = 0;

		// if page is not in the frames
		if (flag == 0) {
			int min = 0, cur = 0;
			while (cur < page_table_size_ - 1) {
				if (count[min] > count[cur + 1]) {
					min = cur + 1;
				}
				cur++;
			}
			frames[min] = input[position];
			count[min] = position + 1;
			result.misses++;
		}
		else {
			result.hits++;
		}
		position++;
	}
	return result;

}