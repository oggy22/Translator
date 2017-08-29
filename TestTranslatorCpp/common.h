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