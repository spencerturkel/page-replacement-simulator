#pragma once
#include <memory>
#include <vector>

#include "step_result.h"

namespace
{
	template <typename State>
	struct iterative_replacement_algorithm
	{
		using state = State;
		using input = std::vector<int>;
		using input_const_iter = input::const_iterator;

		const std::string name;
		const int page_table_size;

		struct run_step_result
		{
			std::unique_ptr<state> next_state;
			step_result result;
		};

		iterative_replacement_algorithm(std::string name, const int page_table_size);

		virtual auto make_initial_state() const -> std::unique_ptr<state> = 0;
		virtual auto run_step(const state& current_state, const input& all_input,
		                      const input_const_iter& current_input) const -> run_step_result = 0;

		virtual ~iterative_replacement_algorithm() = default;
	};

	template <typename State>
	iterative_replacement_algorithm<State>::iterative_replacement_algorithm(std::string name, const int page_table_size)
		: name(std::move(name)), page_table_size(std::move(page_table_size))
	{
	}

	template <typename State>
	auto run_iterative_replacement_algorithm(const iterative_replacement_algorithm<State>& algorithm,
	                                         const std::vector<int>& all_input) -> std::vector<step_result>
	{
		auto results = std::vector<step_result>{};
		auto state = algorithm.make_initial_state();
		using std::move;

		for (auto index = all_input.cbegin(); index != all_input.cend(); ++index)
		{
			auto step = algorithm.run_step(*state, all_input, index);
			state = move(step.next_state);
			results.push_back(move(step.result));
		}

		return results;
	}
}
