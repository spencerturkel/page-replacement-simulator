#include "iterative_replacement_algorithm.h"

namespace
{
	auto run_specialized(specialized* algorithm,
	                     const std::vector<int>& all_input) -> std::vector<result>
	{
		const iterative_replacement_algorithm<specialized>* alg = algorithm;
		return run_iterative_replacement_algorithm(*alg, all_input);
	}
}
