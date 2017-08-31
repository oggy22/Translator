﻿#include "stdafx.h"

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
void generate_random_sentences(map<int, string_t>& sents, int seed=0)
{
	for (int i = 0; i < 100; i++)
	{
		string_t str = translator::random_sentence<Language>(seed++);
		sents[str.length()] = str;
	}
}

int main(int argc, char *argv[])
{
	std::random_device device;
	auto seed = device();

	if (argc == 1)
	{
		cout << "Translator 1.0" << endl;
		cout << "Made by Oggy" << endl;
		cout << "-h or -help for help" << endl;
		return 0;
	}

	if (std::strcmp(argv[1], "-help") == 0)
	{
		cout << "TranslatorCpp.exe -[COMMAND]" << endl;
		cout << "TranslatorCpp.exe -[COMMAND]:[LANG1]" << endl;
		cout << "TranslatorCpp.exe -[COMMAND]:[LANG1]:[LANG2]" << endl;
		cout << "[COMMAND] me be:" << endl;
		cout << "list - print out all the words form the language" << endl;
		cout << "random - generate a random sentence" << endl;
		cout << "translate - generate a random sentence" << endl;
		cout << "help- generate a random sentence" << endl;
		cout << "[LANG] me be SR or EN" << endl;
		return 0;
	}

	if (starts_with<string>(argv[1], "-translate:"))
	{
		cout << "Translate is not yet implemented" << endl;
		return 0;
	}
	
	if (starts_with<string>(argv[1], "-random:"))
	{
		string stLang = argv[1] + strlen("-random:");
		if (stLang == "SR")
		{
			map<int, wstring> sents;
			generate_random_sentences<Serbian>(sents, seed);
			set_wide();
			for (auto const &pair : sents)
				std::wcout << pair.second << endl;
		}
		else if (stLang == "EN")
		{
			map<int, string> sents;
			generate_random_sentences<English>(sents, seed);
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
			for (const auto& word : English::dictWords())
			{
				cout << word.word << endl;
				cout << " ";
				for (const auto& form : word.words)
					cout << form.word << " ";
				cout << endl;
			}
		}
		else
		{
			cerr << "Unrecognized language: " << stLang << endl;
			return -1;
		}

		return 0;
	}

	cerr << "Unrecognized command" << endl;
	return -1;
}