#include <cassert>

template <typename T>
class matrix
{
	T *data;
	int rows, columns;

public:
	matrix(int rows, int columns)
		: rows(rows), columns(columns), data(new T[columns*rows])
	{}

	~matrix()
	{
		delete[] data;
	}

	T& operator()(int i, int j)
	{
		assert(0 <= i && i < rows);
		assert(0 <= j && j < columns);
		return data[i*columns + j];
	}
};