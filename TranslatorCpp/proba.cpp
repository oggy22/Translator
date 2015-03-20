#include <set>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

struct Serbian
{
	Serbian()
	{
	}

	enum class attributes
	{
		nom, gen, dat, akuz, vokat, instr, lok
	};

	enum class categories
	{
		padez, broj, lice
	};
};

class match
{
	std::set<Serbian::attributes> attrs;
	std::set<Serbian::categories> cats;

	//using Serbian;

public:
	match()
	{
	}

	match(const std::set<Serbian::attributes> &attrs, const std::set<Serbian::categories> &cats = std::set<Serbian::categories>())
		: attrs(attrs), cats(cats)
	{
	}
};

int main()
{
	std::set<Serbian::attributes> ats({ Serbian::attributes::akuz, Serbian::attributes::instr });
	match m1{ { Serbian::attributes::akuz, Serbian::attributes::instr } };
	match m2{ { Serbian::attributes::akuz, Serbian::attributes::instr }, {Serbian::categories::broj} };

	return 0;
}