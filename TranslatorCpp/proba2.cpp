#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

enum class word_type { noun, verb, pron };
enum class categories { gender, person, plurality };
enum class attributes { per1, per2, per3, male, female, neutral, sing, plur };

class node
{
	set<attributes> attrs;
	set<categories> cats;

public:
	node(word_type wordtype)
	{
		cout << "node(word_type)" << endl;
	}

	template <typename... Values>
	node(word_type wordtype, attributes a, Values... values) : node(wordtype, values...)
	{
		cout << "node(word_type, attr, ...)" << endl;
		attrs.insert(a);
	}

	template <typename... Values>
	node(word_type wordtype, categories c, Values... values) : node(wordtype, values...)
	{
		cout << "node(word_type, cat, ...)" << endl;
		cats.insert(c);
	}
};

class rule
{
public:
	using right_type = vector<node>;
	using size_type = typename right_type::size_type;
	set<attributes> attrs;
	set<categories> cats;

	rule(node left, right_type right) : left(left), right(right)
	{
		attrs.clear();
	}



	node left;
	vector<node> right;

	size_type size() const
	{
		return right.size();
	}

};

int main()
{
	//Foo foo;
	node n1(word_type::noun, categories::gender);
	node n2(word_type::noun, attributes::per1, attributes::female, categories::plurality);
	node n3{ word_type::pron, attributes::sing };

}