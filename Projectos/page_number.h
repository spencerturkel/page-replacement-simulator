#pragma once
#include <cassert>


namespace
{
	struct page_number
	{
		const int value;

		explicit page_number(const int value) : value(value)
		{
			assert(value > 0);
		}

		operator int() const
		{
			return value;
		}
	};
}
