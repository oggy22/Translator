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

	T& operator()(size_t i, size_t j)
	{
		ASSERT(0 <= i && i <=j && j<n);
		return data[i*n + j];
	}
};