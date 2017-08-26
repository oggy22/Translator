#include "stdafx.h"
#include "../TranslatorCpp/Languages/English.h"
std::wostream& operator<<(std::wostream&wout, English::word_type wt)
{
	switch (wt)
	{
		case noun: wout << L"noun"; break;
		case verb: wout << L"verb"; break;
	default: FAIL("Unknown English::word_type");
	}
	return wout;
}
#include "wstring_outputs.h"

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
				if (!rule.used)
				{
					std::wstringstream wss;
					wss << rule << L" not used";
					Assert::Fail(wss.str().c_str());
				}
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

		TEST_METHOD(check_some_derived_words)
		{
			check_dictionary_word_exists<English>("doable");
			check_dictionary_word_exists<English>("talkable");
		}

		TEST_METHOD(english_grammar_rules)
		{
			test("i speak");
			test("you walks", false);
			test("he talks");
			test("she goes");
			test("she go", false);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(random_test)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(random_test)
		{
			for (int i = 0; i < 100; i++)
			{
				std::string str = translator::random_sentence<English>(0);
				Logger::WriteMessage(str.c_str());
				test(str);
			}
		}
	};
}