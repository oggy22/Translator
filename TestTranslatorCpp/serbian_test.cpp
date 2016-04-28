#include "stdafx.h"
#include "../TranslatorCpp/Languages/Serbian.h"
#include "common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TranslatorTest
{
	TEST_CLASS(SerbianTests)
	{
		void test(const std::wstring& st, bool expected=true)
		{
			Serbian serbian;
			Assert::AreEqual(expected, translator::parse<Serbian>(st));
		}

	public:

#ifdef _DEBUG
		TEST_METHOD(every_rule_used)
		{
			for (auto& rule : Serbian::word_rules)
			{
				Assert::IsTrue(rule.used/*, (std::wstring)(rule.destination)*/);
			}
		}
#endif

		TEST_METHOD(every_word_composed_of_serbian_letters)
		{
			for (const auto& word : Serbian::dictWords)
			{
				for (const auto& w : word.words)
				{
					for (wchar_t c : w.word)
						Assert::AreNotEqual(std::wstring::npos, Serbian::stAlphabet.find(c));
				}
			}
		}

		TEST_METHOD(every_noun_has_gender)
		{
			for (const auto& word : Serbian::dictWords)
			{
				if (word.wordtype == Serbian::word_type::именица)
				{
					Assert::IsTrue(
						word.attrs.count(Serbian::attributes::мушки) ||
						word.attrs.count(Serbian::attributes::женски) ||
						word.attrs.count(Serbian::attributes::средњи));
				}
			}
		}

		using attr_t = Serbian::attributes;

		void test_word_forms(const translator::dictionary_word<Serbian> &word, set<attr_t> set1)
		{
			for (attr_t a : set1)
				Assert::IsTrue(word(a), L"Missing wordform");
		}

		void test_word_forms(const translator::dictionary_word<Serbian> &word, set<attr_t> set1, set<attr_t> set2)
		{
			for (attr_t a1 : set1)
				for (attr_t a2 : set2)
					Assert::IsTrue(word(a1,a2),
						(word.word + std::wstring(L"Missing wordform 2 attrs")).c_str());
		}

		void test_word_forms(const translator::dictionary_word<Serbian> &word, set<attr_t> set1, set<attr_t> set2, set<attr_t> set3)
		{
			for (attr_t a1 : set1)
				for (attr_t a2 : set2)
					for (attr_t a3 : set3)
						Assert::IsTrue(word(a1, a2, a3),
							(word.word + std::wstring(L"Missing wordform 3 attrs")).c_str());
		}

		TEST_METHOD(each_noun_has_7cases_2numbers)
		{
			for (const auto& word : Serbian::dictWords)
			{
				if (word.wordtype == Serbian::word_type::именица)
				{
					Assert::AreEqual<size_t>(7 * 2, word.words.size(), (word.word + L" doesn't have 14 forms").c_str());
					test_word_forms(word,
					{ attr_t::номинатив, attr_t::генитив, attr_t::датив, attr_t::акузатив, attr_t::вокатив, attr_t::инструментал, attr_t::локатив },
					{ attr_t::једнина, attr_t::множина });
				}
			}
		}

		TEST_METHOD(each_verb_has_2plurals_3persons_present_forms)
		{
			for (const auto& word : Serbian::dictWords)
			{
				if (word.wordtype == Serbian::word_type::глагол)
				{
					Assert::AreEqual<size_t>(3 * 2, word.words.size(), (word.word + L" doesn't have 6 forms").c_str());
					test_word_forms(word,
					{ attr_t::једнина, attr_t::множина },
					{ attr_t::лице1, attr_t::лице2, attr_t::лице3 });
				}
			}
		}

		TEST_METHOD(each_adjective_has_3genders_2plurals_7cases)
		{
			for (const auto& word : Serbian::dictWords)
			{
				if (word.wordtype == Serbian::word_type::придев)
				{
					//Assert::AreEqual<size_t>(3 * 2 * 7, word.words.size(), (word.word + L" doesn't have 42 forms").c_str());
					test_word_forms(word,
					{ attr_t::мушки, attr_t::женски, attr_t::средњи },
					{ attr_t::једнина, attr_t::множина },
					{ attr_t::номинатив, attr_t::генитив, attr_t::датив, attr_t::акузатив, attr_t::вокатив, attr_t::инструментал, attr_t::локатив }
					);
				}
			}
		}

		TEST_METHOD(each_adverb_has_3comparatives)
		{
			for (const auto& word : Serbian::dictWords)
			{
				if (word.wordtype == Serbian::word_type::прилог)
				{
					Assert::AreEqual<size_t>(3, word.words.size(), (word.word + L" doesn't have 3 forms").c_str());
					test_word_forms(word,
					{ attr_t::позитив, attr_t::компаратив, attr_t::суперлатив }
					);
				}
			}
		}

#define CHECK check<Serbian>

		TEST_METHOD(check_some_noun_forms)
		{
			CHECK(L"коња",	L"коњ", attr_t::једнина, attr_t::акузатив);
			CHECK(L"орах", L"орах", attr_t::једнина, attr_t::акузатив);
			CHECK(L"ораси", L"орах", attr_t::множина, attr_t::номинатив);
			CHECK(L"орахе", L"орах", attr_t::множина, attr_t::акузатив);
			CHECK(L"мишеви", L"миш", attr_t::множина, attr_t::номинатив);
			CHECK(L"човече", L"човек", attr_t::једнина, attr_t::вокатив);
		}

		TEST_METHOD(check_some_verb_forms)
		{
			CHECK(L"сам", L"бити", attr_t::једнина, attr_t::лице1);
			CHECK(L"идем", L"ићи", attr_t::једнина, attr_t::лице1);
			CHECK(L"једем", L"јести", attr_t::једнина, attr_t::лице1);
			CHECK(L"могу", L"моћи", attr_t::једнина, attr_t::лице1);
			CHECK(L"можемо", L"моћи", attr_t::множина, attr_t::лице1);
			CHECK(L"пишемо", L"писати", attr_t::множина, attr_t::лице1);
			CHECK(L"хоћемо", L"хтети", attr_t::множина, attr_t::лице1);
		}

		TEST_METHOD(check_some_adjective_forms)
		{
			CHECK(L"лошег", L"лош", attr_t::мушки, attr_t::једнина, attr_t::генитив);
		}

		TEST_METHOD(serbian_grammar_rules)
		{
			test(L"ја гледам");
			test(L"ја радиш", false);
			test(L"ти радиш");
			test(L"он пева");
			test(L"он певам", false);
		}
	};
}