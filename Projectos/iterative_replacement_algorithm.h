#pragma once
#include <memory>
#include <vector>

namespace
{
	struct result
	{
		bool is_hit;
		std::vector<int> page_table;
	};

	template <typename State>
	struct iterative_replacement_algorithm
	{
		using state = State;
		using input = std::vector<int>;
		using input_const_iter = input::const_iterator;

		struct run_result
		{
			std::unique_ptr<state> next_state;
			result result;
		};

		const std::string name;
		const int page_table_size;

		iterative_replacement_algorithm(std::string name, const int page_table_size);

		virtual auto make_initial_state() const -> std::unique_ptr<state> = 0;
		virtual auto run(const state& current_state, const input& all_input, const input_const_iter& current_input) const -> run_result = 0;

		virtual ~iterative_replacement_algorithm() = default;
	};

	template <typename State>
	iterative_replacement_algorithm<State>::iterative_replacement_algorithm(std::string name, const int page_table_size)
		: name(std::move(name)),
		  page_table_size(page_table_size)
	{
	}
}
