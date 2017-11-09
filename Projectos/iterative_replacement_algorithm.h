#pragma once
#include <string>
#include <vector>
#include <memory>

namespace
{
	struct result
	{
		bool is_hit;
		std::vector<int> page_table;
	};

	template <typename Derived>
	struct state
	{
	};

	template <typename Derived>
	struct iterative_replacement_algorithm
	{
		using derived_state = state<Derived>;

		struct run_result
		{
			std::unique_ptr<derived_state> next_state;
			result result;
		};

		virtual auto make_initial_state() const -> std::unique_ptr<derived_state> = 0;
		virtual auto run(const derived_state& current_state, const std::vector<int>& all_input,
		                 const std::vector<int>::const_iterator& current_index) const -> run_result = 0;

		virtual ~iterative_replacement_algorithm() = default;
	};

	struct specialized : iterative_replacement_algorithm<specialized>
	{
		auto run(const derived_state& current_state, const std::vector<int>& all_input,
		         const std::vector<int>::const_iterator& current_index) const -> run_result override = 0;
	};

	template<>
	struct state<specialized>
	{
		int a;
	};

	auto run_specialized(specialized* algorithm,
	                     const std::vector<int>& all_input) -> std::vector<result>;
}

template <typename Derived>
inline auto run_iterative_replacement_algorithm(const iterative_replacement_algorithm<Derived>& algorithm,
                                                const std::vector<int>& all_input) -> std::vector<result>
{
	auto results = std::vector<result>{};
	auto initial_state = algorithm.make_initial_state();
	return results;
}
