#pragma once
#include <string>

template <class Language>
void check_dictionary_word_exists(const typename Language::string_t& st)
{
	for (const auto& word : Language::dictWords())
		if (word.word == st)
			return;

	Assert::Fail(L"Word st wasn't found");
}

template <class Language, class... Attributes>
const typename Language::string_t get_dictionary_word(const typename Language::string_t& st, Attributes... attributes)
{
	for (const auto& word : Language::dictWords())
		if (word.word == st)
		{
			return word[{ attributes... }].word;
		}
	Assert::Fail(L"Word st wasn't found");
}

template <class Language, class... Attributes>
void check(const typename Language::string_t& stExpected, const typename Language::string_t& stDicWord, Attributes... attributes)
{
	Assert::AreEqual<const typename Language::string_t&>(stExpected, get_dictionary_word<Language>(stDicWord, attributes...));
}

template <typename char_t, typename string_t = std::basic_string<char_t>>
static bool is_palindrome(const string_t& str)
{
	for (size_t i = 0, j = str.size() - 1; i < j; i++, j--)
	{
		if (str[i] == char_t(' ')) i++;
		if (str[j] == char_t(' ')) j--;

		if (str[i] != str[j])
			return false;
	}

	return true;
}

template <typename char_t, typename string_t = std::basic_string<char_t>>
static void each_word_exists(const string_t& result, const std::vector<string_t>& words)
{
	std::basic_stringstream<char_t> stream(result);
	while (!stream.eof())
	{
		string_t word;
		stream >> word;
		std::reverse(word.begin(), word.end());

		auto it = std::lower_bound(words.begin(), words.end(), word);
		if (it == words.end())
			Assert::Fail(word.c_str());
	}
}
