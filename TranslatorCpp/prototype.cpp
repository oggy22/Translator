#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>

#include "Assert.h"

using namespace std;

enum class word_type { noun, verb, pron, NounPhrase, VerbPhrase, Preposition, Sentence };
enum class categories { gender, person, plurality };
enum class attributes { person1, person2, person3, male, female, neutral, singular, plural };

#define noun word_type::noun
#define verb word_type::verb
#define pron word_type::pron
#define NP word_type::NounPhrase
#define VP word_type::VerbPhrase
#define Prep word_type::Preposition
#define Sent word_type::Sentence

#define gen categories::gender
#define per categories::person
#define plrt categories::plurality
#define per1 attributes::person1
#define per2 attributes::person2
#define per3 attributes::person3
#define mal attributes::male
#define fem attributes::female
#define neut attributes::neutral
#define sing attributes::singular
#define plur attributes::plural

const map<attributes, categories> belongs
{
	{ per1, per },
	{ per2, per },
	{ per3, per },
	{ mal, gen },
	{ fem, gen },
	{ neut, gen },
	{ sing, plrt },
	{ plur, plrt },
};

class node
{
	string st;
	set<attributes> free_attrs;
	set<categories> free_cats;
	map<categories, attributes> mapping;

public:
	node(const string& st) : st(st)
	{
	}

	node(word_type wordtype)
	{
		cout << "node(word_type)" << endl;
	}

	template <typename... Values>
	node(word_type wordtype, attributes attr, Values... values) : node(wordtype, values...)
	{
		cout << "node(word_type, attr, ...)" << endl;
		auto p_cat = belongs.find(attr);
		if (p_cat != belongs.end())
		{
			auto cat = p_cat->second;
			ASSERT_WITH_MSG(mapping.count(cat) == 0, "The attribute from the same category set already");
			mapping[cat] = attr;
		}
		else
		{
			ASSERT_WITH_MSG(free_attrs.count(attr) == 0, "The attribute already added");
			free_attrs.insert(attr);
		}
	}

	template <typename... Values>
	node(word_type wordtype, categories cat, Values... values) : node(wordtype, values...)
	{
		cout << "node(word_type, cat, ...)" << endl;
		auto p_cat = mapping.find(cat);
		ASSERT_WITH_MSG(p_cat == mapping.end(), "The category alreay mapped");

		free_cats.insert(cat);
	}
};

class rule
{
public:
	using right_type = std::vector<node>;
	using size_type = typename right_type::size_type;
	
	node left;
	vector<node> right;

	set<attributes> attrs;
	set<categories> cats;

	rule(node left, right_type right) : left(left), right(right)
	{
		attrs.clear();
	}

	size_type size() const
	{
		return right.size();
	}
};

int main2()
{
	node n1(noun, categories::gender);
	node n2(noun, attributes::person1, attributes::female, categories::plurality);
	node n3{pron, attributes::singular };

	rule r1{ {Prep}, { {"in"}, {noun}} };
	rule r2{ {Sent}, {{pron, per3}, {verb, per3, sing}} };

	//cout << attributes::female << endl;
	return 0;
}