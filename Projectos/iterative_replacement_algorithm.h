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

	template <typename Derived>
	struct state
	{
	};

	template <typename Derived>
	struct iterative_replacement_algorithm
	{
		using derived_state = state<Derived>;
		using input = std::vector<int>;
		using input_const_iter = input::const_iterator;

		struct run_result
		{
			std::unique_ptr<derived_state> next_state;
			result result;
		};

		const std::string name;
		const int page_table_size;

		iterative_replacement_algorithm(std::string name, const int page_table_size);

		virtual auto make_initial_state() const -> std::unique_ptr<derived_state> = 0;
		virtual auto run(const derived_state& current_state, const input& all_input, const input_const_iter& current_input) const -> run_result = 0;

		virtual ~iterative_replacement_algorithm() = default;
	};

	template <typename Derived>
	iterative_replacement_algorithm<Derived>::iterative_replacement_algorithm(std::string name, const int page_table_size)
		: name(std::move(name)),
		  page_table_size(page_table_size)
	{
	}

	template <typename Derived>
	auto run_iterative_replacement_algorithm(const iterative_replacement_algorithm<Derived>& algorithm,
	                                         const std::vector<int>& all_input) -> std::vector<result>
	{
		auto results = std::vector<result>{};
		auto state = algorithm.make_initial_state();
		using std::move;

		for (auto index = all_input.cbegin(); index != all_input.cend(); ++index)
		{
			auto step = algorithm.run(*state, all_input, index);
			state = move(step.next_state);
			results.push_back(move(step.result));
		}

		return results;
	}
}
