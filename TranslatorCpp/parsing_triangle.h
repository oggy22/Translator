#include <ostream>
#include "Assert.h"

template <typename T>
class parsing_triangle
{
	T *data;
	size_t n;

public:
	parsing_triangle(size_t n)
		: n(n), data(new T[n*n])
	{}

	~parsing_triangle()
	{
		delete[] data;
	}

	const T& operator()(size_t i, size_t j) const
	{
		ASSERT(0 <= i && i <= j && j<n);
		return data[i*n + j];
	}

	T& operator()(size_t i, size_t j)
	{
		ASSERT(0 <= i && i <= j && j < n);
		return data[i*n + j];
	}

	template <typename Char, typename T>
	void to_ostream(std::basic_ostream<Char>& os, const std::vector<T>& words)
	{
		ASSERT(n == words.size());
		for (size_t delta = 0; delta < n; delta++)
			for (size_t start = 0; start < n - delta; start++)
			{
				int end = start + delta;

				// Print the words
				os << "'";
				for (int i = start; i < end; i++)
					os << words[i] << " ";
				os << words[end] << "'";

				//os << "(" << start << "," << end << ")";
				for (const auto& pn : this->operator()(start, end))
					os << pn << " ";
				os << std::endl;
			}
	}
};