#include "../include/lfu_iterative_replacement_algorithm.h"

namespace
{
  auto page_used_greater_than(const page& left, const page& right) -> bool
  {
  	return left.used > right.used;
  }
}

lfu_iterative_replacement_algorithm::lfu_iterative_replacement_algorithm(const int page_table_size)
	: frequency_iterative_replacement_algorithm("Least Frequently Used", page_table_size, page_used_greater_than)
{
}
