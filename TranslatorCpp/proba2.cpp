#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void process(const vector<string> vec)
{
	for (auto s : vec)
	{
		s += "'";
		cout << s << endl;
	}
}

int main()
{
	const vector<string> v
	{
		"abc", "xyz", "12345"
	};

	process(v);

	std::for_each(v.begin(), v.end(), [&](const string& s)
	{
		cout << s << endl;
	});
}