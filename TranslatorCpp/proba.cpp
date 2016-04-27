#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
#include "Languages\Serbian.h"
#include "Languages\English.h"

using namespace std;

void set_wide()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
}

int main1(void)
{
	while (false)
	{
		string s;
		cin >> s;
		reverse(s.begin(), s.end());
		cout << s << endl;
		//Sleep(1000);
	}
	auto& out = cout;
	using language_t = English;
	std::set<language_t::string_t> words;
	if (std::is_same<language_t::letter, wchar_t>::value)
		set_wide();
	English::traverse_word_forms([&](const translator::word_form<language_t>& word)
	{
		words.insert(word.word);
		//wcout << word.word << " ";
	});
	
	for (const auto& dw : English::dictWords)
	{
		out << dw.word << " (";
		for (const auto& wf : dw.words)
			out << wf.word << " ";
		out << ")" << endl;
	}

	//for (const auto& w : words)
	//	out << w << " ";
	
	while (true)
	{
		string st;
		//wcin >> st;
		//out << (words.count(st) ? "yes" : "no") << endl;
	}
	return 0;
}