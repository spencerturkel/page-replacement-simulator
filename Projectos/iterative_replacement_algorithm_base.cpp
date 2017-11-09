#include <string>
#include "iterative_replacement_algorithm_base.h"

iterative_replacement_algorithm_base::iterative_replacement_algorithm_base(
	std::string name, const int page_table_size) : name(std::move(name)), page_table_size(std::move(page_table_size))
{
}
