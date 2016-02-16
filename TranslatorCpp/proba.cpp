#include <initializer_list>

template <class T>
class  V {
public:

	V(){}
	V(const V<T>&& v){}
        V(const std::initializer_list<T> &v) {}
        ~V() {}
};

template <class L>
struct n
{
	n(
		V<int> attrs = V<int>()
		) {}
};

template <class L>
struct r
{
	n<L> l;
};

struct E
{
	V<r<E>> s;

	E()
		: 
	s({{ }})
	{
	}
};

int main()
{
	E e;
}