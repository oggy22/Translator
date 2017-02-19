#include "stdafx.h"
#include "../TranslatorCpp/Languages/English.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
std::ofstream test_output("english_test.log");

namespace TranslatorTest
{
	TEST_CLASS(EnglishTests)
	{
		void test(const std::string& st, bool expected = true)
		{
			Assert::AreEqual(expected, translator::parse<English>(st));
		}

	public:
#ifdef _DEBUG
		TEST_METHOD(every_rule_used)
		{
			for (auto& rule : English::word_rules)
			{
				Assert::IsTrue(rule.used/*, (std::wstring)(rule.destination)*/);
			}
		}
#endif

		TEST_METHOD(every_word_composed_of_english_letters)
		{
			for (const auto& word : English::dictWords())
			{
				for (const auto& w : word.words)
				{
					for (char c : w.word)
						Assert::IsTrue(English::stAlphabet.find(c) != std::wstring::npos, ToString(w.word).c_str());
				}
			}
		}

		using attr_t = English::attributes;

		void test_word_forms(const translator::dictionary_word<English> &word, set<attr_t> set1)
		{
			for (attr_t a : set1)
				Assert::IsTrue(word(a), L"Missing wordform");
		}

		void test_word_forms(const translator::dictionary_word<English> &word, set<attr_t> set1, set<attr_t> set2)
		{
			for (attr_t a1 : set1)
				for (attr_t a2 : set2)
					Assert::IsTrue(word(a1, a2),
					(std::wstring(L"Missing wordform 2 attrs")).c_str());
		}

#undef noun
#undef sing
#undef plur

		TEST_METHOD(each_noun_singular_and_plural)
		{
			for (const auto& word : English::dictWords())
			{
				if (word.wordtype == English::word_type::noun)
				{
					Assert::AreEqual<size_t>(2, word.words.size(), L" doesn't have 2 forms");
					test_word_forms(word,
					{ English::attributes::sing, English::attributes::plur }
					);
				}
			}
		}

		TEST_METHOD(check_some_noun_forms)
		{
			check<English>("women", "woman", attr_t::plur);
		}

		TEST_METHOD(english_grammar_rules)
		{
			test("i speak");
			test("you walks", false);
			test("he talks");
			test("she goes");
			test("she go", false);
		}
	};
}