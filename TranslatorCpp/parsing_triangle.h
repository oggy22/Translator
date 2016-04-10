#include "Assert.h"

template <typename T>
class parsing_triangle
{
	T *data;
	int n;

public:
	parsing_triangle(int n)
		: n(n), data(new T[n*n])
	{}

	~parsing_triangle()
	{
		delete[] data;
	}

	T& operator()(int i, int j)
	{
		ASSERT(0 <= i && i <=j && j<n);
		return data[i*n + j];
	}
};