#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

enum class word_type { noun, verb, pron };
enum class categories { gender, person, plurality };
enum class attributes { person1, person2, person3, male, female, neutral, singular, plural };

#define noun word_type::noun
#define verb word_type::verb
#define pron word_type::pron
#define gen categories::gender
#define per categories::person
#define plrt categories::plurality
#define per1 attributes::person1
#define per2 attributes::person2
#define per3 attributes::person3
#define mal attributes::male
#define fem attributes::female
#define neut attributes::neutral
#define sign attributes::singular
#define plur attributes::plural

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
	node n1(noun, categories::gender);
	node n2(noun, attributes::person1, attributes::female, categories::plurality);
	node n3{pron, attributes::singular };
}