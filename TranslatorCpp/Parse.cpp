﻿#include "stdafx.h"

#include <random>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <execution>
#include "Languages\English.h"
#include "Languages\Serbian.h"
#include "random_sentence.h"
#undef map
#include "palindrome.h"

void set_wide()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
}

template <typename string_t>
void remove(std::vector<string_t>& words, string_t word)
{
	auto it = std::lower_bound(words.begin(), words.end(), word);
	if ((*it) == word)
	{
		words.erase(it);
	}
}

using namespace std;

template <typename Language, typename string_t = Language::string_t>
void generate_random_sentences(map<size_t, string_t>& sents, int seed=0)
{
	for (int i = 0; i < 1000; i++)
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
		cout << "[COMMAND] can be:" << endl;
		cout << "list - print out all the words form the language" << endl;
		cout << "random - generate a random sentence" << endl;
		cout << "translate - generate a random sentence" << endl;
		cout << "palindrome [depth] - generate a random sentence" << endl;
		cout << "help - prints this info" << endl;
		cout << "[LANG] can be SR or EN" << endl;
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
			map<size_t, wstring> sents;
			setlocale(LC_ALL, "");
			generate_random_sentences<Serbian>(sents, seed);
			set_wide();
			for (auto const &pair : sents)
				std::wcout << pair.second << endl;
		}
		else if (stLang == "EN")
		{
			map<size_t, string> sents;
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

	bool palindrome_parse = starts_with<string>(argv[1], "-palindromep:");
	if (starts_with<string>(argv[1], "-palindrome:") || palindrome_parse)
	{
		string stLang = strchr(argv[1], ':')+1;
		if (stLang == "SR")
		{
			std::vector<wstring> words;
			for (const auto& word : Serbian::dictWords())
			{
				for (const auto& form : word.words)
					words.push_back(form.word);
			}

			std::sort(words.begin(), words.end());
			words.erase(unique(words.begin(), words.end()), words.end());

			remove<wstring>(words, L"бен");
			remove<wstring>(words, L"бена");
			remove<wstring>(words, L"бене");
			remove<wstring>(words, L"бени");
			remove<wstring>(words, L"бено");
			remove<wstring>(words, L"беној");
			remove<wstring>(words, L"бену");
			remove<wstring>(words, L"мојоме");
			remove<wstring>(words, L"окое");
			remove<wstring>(words, L"пила");
			remove<wstring>(words, L"чуна");
			remove<wstring>(words, L"чуне");
			remove<wstring>(words, L"чуни");
			remove<wstring>(words, L"чуну");

			int depth = 8;
			if (argc >= 3)
				depth = std::stoi(argv[2]);

			float min_parse = 0.0;
			if (argc >= 4)
				min_parse = std::stof(argv[3]);

			auto results = find_palindromes<wchar_t>(words, depth);

			// Trim those of form "A [palindrome] A"
			for (auto it = results.begin(); it != results.end();)
			{
				wstring pal = *it;
				size_t first = pal.find_first_of(L' ');
				size_t last = pal.find_last_of(L' ');
				if (first == pal.length() - last - 1)
				{
					results.erase(it++);
				}
				else
				{
					it++;
				}
			}

			std::vector<palindrome<wchar_t>> palindromes(results.begin(), results.end());

			std::sort(palindromes.begin(), palindromes.end(),
				[](const palindrome<wchar_t> & a, const palindrome<wchar_t> & b) -> bool
			{
				return a.average_word_length() < b.average_word_length();
			});

			set_wide();
			wcout
				<< "palindrome, chars, letters, words, avg. word, stddev. word"
				<< (palindrome_parse ? ", parsed" : "") <<  endl;

			if (palindrome_parse)
				std::for_each(std::execution::par, std::begin(palindromes), std::end(palindromes),
					[&](palindrome<wchar_t>& pal)
					{
						pal.parsed = translator::parse<Serbian>(pal.word());
					});

			for (auto palin : palindromes)
			{
				if (palin.word().length() == 0 || palin.parsed < min_parse)
					continue;

				wcout << palin.word();
				wcout << ',' << palin.number_of_chars();
				wcout << ',' << palin.number_of_letters();
				wcout << ',' << palin.number_of_words();
				wcout << ',' << palin.average_word_length();
				wcout << ',' << palin.stddev_word_legth();
				if (palindrome_parse)
					wcout << ',' << palin.parsed;
				wcout << endl;
			}
			wcout << results.size() << " results" << endl;
		}

		return 0;
	}

	cerr << "Unrecognized command" << endl;
	return -1;
}

char translator::capitalize(char c)
{
	return toupper(c);
}

wchar_t translator::capitalize(wchar_t c)
{
	wchar_t upper = towupper(c);
	return upper;
}

void translator::to_lower(basic_string<char>& s)
{
	for (basic_string<char>::iterator p = s.begin(); p != s.end(); ++p)
		*p = tolower(*p);
}

void translator::to_lower(basic_string<wchar_t>& s)
{
	for (basic_string<wchar_t>::iterator p = s.begin(); p != s.end(); ++p)
		*p = towlower(*p);
}

template<typename Char>
bool ends_with(const std::basic_string<Char>& value, const std::basic_string<Char>& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

template<>
bool translator::probability_accept(const dictionary_word<Serbian>& dw, std::default_random_engine& device)
{
	std::uniform_real_distribution<double> probability_dist(0.0, 1.0);

	if (dw.attrs.find(Serbian::attributes::деминутив) != dw.attrs.end())
		return probability_dist(device) < 0.4;

	if (dw.attrs.find(Serbian::attributes::аугментатив) != dw.attrs.end())
		return probability_dist(device) < 0.3;

	if (dw.wordtype == Serbian::word_type::именица && ends_with<wchar_t>(dw.word, L"ње"))
		return probability_dist(device) < 0.3;

	return true;
}

template<>
bool translator::probability_accept(const dictionary_word<English>& dw, std::default_random_engine& device)
{
	return true;
}