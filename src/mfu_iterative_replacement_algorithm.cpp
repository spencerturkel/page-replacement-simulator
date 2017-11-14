#include "../include/mfu_iterative_replacement_algorithm.h"


mfu_iterative_replacement_algorithm::
mfu_iterative_replacement_algorithm(const int page_table_size): frequency_iterative_replacement_algorithm(
	"Most Frequently Used", page_table_size, page_used_less_than)
{
}
