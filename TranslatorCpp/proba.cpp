#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>

using namespace std;

#define WIDE2

#ifdef WIDE
#define Char wchar_t
#define T(x) L##x
#define COUT wcout
#else
#define Char char
#define T(x) x
#define COUT cout
#endif

enum class attributes : char { per1, per2, per3, sing, plur };

struct word_t
{
	std::basic_string<Char> word;
	std::set<attributes> attrs;
};

struct dictionary_word
{
	std::basic_string<Char> word;
	std::set<attributes> attrs;
	std::vector<word_t> words;
};

struct two_numbers
{
	int x, y;
};

struct FakeLang
{
	std::vector<dictionary_word> words;
	FakeLang() :
		words(
	{
		{ T("abc"), { attributes::per1, attributes::sing }, { { T("abc"), {} } } },
		{ T("xyz"), { attributes::per2 }, { { T("abc") } } },
		{ T("a"), {}, {} }
	}
	)
	{

	}
};

int main2()
{
	std::vector<dictionary_word> words
	{
		{ T("abc"), { attributes::per1, attributes::sing }, { { T("abc") } } },
		{ T("xyz"), { attributes::per2 }, { { T("abc") } } },
		{ T("a"), {}, {} }
	};

	FakeLang fake_lang;

	vector<two_numbers> numbers;
	numbers.emplace_back(two_numbers{ 42, 13 });

	for (const dictionary_word& dw : words)
	{
		COUT << dw.word;
		for (auto x : dw.attrs)
			cout << int(x) << " ";
		cout << endl;
	}

	cout << sizeof(bool) << endl;

	return 0;
}