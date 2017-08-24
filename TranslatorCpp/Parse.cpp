#include "stdafx.h"

#include <random>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "Languages\English.h"
#include "Languages\Serbian.h"
#include "random_sentence.h"

void set_wide()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
}

using namespace std;

template <typename Language, typename string_t = Language::string_t>
void generate_random_sentences(map<int, string_t>& sents)
{
	int seed = rand();
	for (int i = 0; i < 100; i++)
	{
		string_t str = translator::random_sentence<Language>(seed++);
		sents[str.length()] = str;
	}
}

int main(int argc, char *argv[])
{
	std::random_device device2;
	auto seed = device2();
	std::default_random_engine device(seed);

	if (argc == 1)
	{
		cout << "Translator 1.0" << endl;
		cout << "Made by Oggy" << endl;
		cout << "-h or -help for help" << endl;
		return 0;
	}

	if (starts_with<string>(argv[1], "-random:"))
	{
		string stLang = argv[1] + strlen("-random:");
		if (stLang == "SR")
		{
			map<int, wstring> sents;
			generate_random_sentences<Serbian>(sents);
			set_wide();
			for (auto const &pair : sents)
				std::wcout << pair.second << endl;
		}
		else if (stLang == "EN")
		{
			map<int, string> sents;
			generate_random_sentences<English>(sents);
			for (auto const &pair : sents)
				std::cout << pair.second << endl;
		}
		else
		{
			std::cerr << "Unrecognized language: " << stLang << std::endl;
			return -1;
		}

		return 0;
	}

	if (starts_with<string>(argv[1], "-list:"))
	{
		string stLang = argv[1] + strlen("-list:");
		if (stLang == "SR")
		{
			set_wide();
			for (const auto& word : Serbian::dictWords())
			{
				wcout << word.word << endl;
				wcout << " ";
				for (const auto& form : word.words)
					wcout << form.word << " ";
				wcout << endl;
			}
		}
		else if (stLang == "EN")
		{
			cout << "Not implemented yet" << endl;
		}
		else
		{
			cerr << "Unrecognized language: " << stLang << endl;
			return -1;
		}
	}

	cerr << "Unrecognized command" << endl;
	return -1;
}

void print_help()
{
	cout << "Translator -[Argument]" << endl;
	cout << "[Argument] can be" << endl;
	cout << "help/h			: Print this screen" << endl;
	cout << "random:Lang	: Generates a random sentence, Lang - two chars language identifier" << endl;
}