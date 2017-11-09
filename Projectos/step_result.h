#pragma once

#include <vector>

namespace
{
	struct step_result
	{
		bool is_hit;
		std::vector<int> page_table;
	};
}
