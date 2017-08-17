#include "stdafx.h"
#include <unordered_set>
#include "../TranslatorCpp/Languages/Serbian.h"
std::wostream& operator<<(std::wostream&wout, Serbian::word_type wt)
{
	switch (wt)
	{
	case Serbian::word_type::именица: wout << L"именица"; break;
	case Serbian::word_type::глагол: wout << L"глагол"; break;
	case Serbian::word_type::придев: wout << L"придев"; break;
	default: FAIL("Unknown Serbian::word_type");
	}
	return wout;
}

#include "wstring_outputs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
std::wofstream test_output("serbian_test.log");

TEST_MODULE_INITIALIZE(TestModuleInitialize)
{
	test_output.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	test_output << "Serbian" << std::endl;
}

namespace TranslatorTest
{
	TEST_CLASS(SerbianTests)
	{
		void test(const std::wstring& st, bool expected=true)
		{
			Assert::AreEqual(expected, translator::parse<Serbian>(st), st.c_str());
		}

	public:

#ifdef _DEBUG
		TEST_METHOD(every_rule_used)
		{
			for (auto& rule : Serbian::word_rules)
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

		TEST_METHOD(every_word_composed_of_serbian_letters)
		{
			std::unordered_set<wchar_t> alphabet;
			for (unsigned int i = 0; i < Serbian::stAlphabet.length(); i++)
				alphabet.insert(Serbian::stAlphabet[i]);

			for (const auto& word : Serbian::dictWords())
			{
				for (wchar_t c : word.word)
					if (alphabet.find(c) == alphabet.end())
						Assert::Fail(word.word.c_str());

				for (const auto& w : word.words)
				{
					for (wchar_t c : w.word)
						if (alphabet.find(c) == alphabet.end())
							Assert::Fail(w.word.c_str());
				}
			}
		}

		TEST_METHOD(every_noun_has_gender)
		{
			for (const auto& word : Serbian::dictWords())
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
			for (const auto& word : Serbian::dictWords())
			{
				if (word.wordtype == Serbian::word_type::именица)
				{
					Assert::IsTrue(7 * 2 <= word.words.size(), (word.word + L" has less than 14 forms").c_str());
					test_word_forms(word,
					{ attr_t::номинатив, attr_t::генитив, attr_t::датив, attr_t::акузатив, attr_t::вокатив, attr_t::инструментал, attr_t::локатив },
					{ attr_t::једнина, attr_t::множина });
				}
			}
		}

		TEST_METHOD(each_verb_has_2plurals_3persons_present_forms_and_inf)
		{
			for (const auto& word : Serbian::dictWords())
			{
				if (word.wordtype == Serbian::word_type::глагол)
				{
					Assert::AreEqual<size_t>(3 * 2 + 1, word.words.size(), (word.word + L" doesn't have 6 forms").c_str());
					
					test_word_forms(word,
					{ attr_t::инфинитив});

					test_word_forms(word,
					{ attr_t::једнина, attr_t::множина },
					{ attr_t::лице1, attr_t::лице2, attr_t::лице3 });
				}
			}
		}

		TEST_METHOD(each_adjective_has_3genders_2plurals_7cases)
		{
			for (const auto& word : Serbian::dictWords())
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
			for (const auto& word : Serbian::dictWords())
			{
				if (word.wordtype == Serbian::word_type::прилог)
				{
					if (ends_with<std::basic_string<wchar_t>>(word.word, L"ћи"))
					{
						Assert::AreEqual<size_t>(1, word.words.size(), (word.word + L" doesn't have 1 form").c_str());
						test_word_forms(word,
						{ attr_t::позитив }
						);
					}
					else
					{
						Assert::AreEqual<size_t>(3, word.words.size(), (word.word + L" doesn't have 3 forms").c_str());
						test_word_forms(word,
						{ attr_t::позитив, attr_t::компаратив, attr_t::суперлатив }
						);
					}
				}
			}
		}

#define CHECK check<Serbian>

		TEST_METHOD(check_some_noun_forms)
		{
			CHECK(L"жену", L"жена", attr_t::једнина, attr_t::акузатив);
			CHECK(L"коња", L"коњ", attr_t::једнина, attr_t::акузатив);
			CHECK(L"мишеви", L"миш", attr_t::множина, attr_t::номинатив);
			CHECK(L"орах", L"орах", attr_t::једнина, attr_t::акузатив);
			CHECK(L"ораси", L"орах", attr_t::множина, attr_t::номинатив);
			CHECK(L"орахе", L"орах", attr_t::множина, attr_t::акузатив);
			CHECK(L"човече", L"човек", attr_t::једнина, attr_t::вокатив);
			CHECK(L"људи", L"човек", attr_t::множина, attr_t::номинатив);
		}

		TEST_METHOD(check_some_noun_case_forms)
		{
			//Nouns
			CHECK(L"сунца", L"сунце", attr_t::једнина, attr_t::генитив);
			CHECK(L"времена", L"време", attr_t::једнина, attr_t::генитив);
			CHECK(L"племену", L"племе", attr_t::једнина, attr_t::датив);

			//Accusative male
			CHECK(L"човека", L"човек", attr_t::једнина, attr_t::акузатив);
			CHECK(L"кромпир", L"кромпир", attr_t::једнина, attr_t::акузатив);
		}

		TEST_METHOD(check_some_verb_forms)
		{
			CHECK(L"сам", L"бити", attr_t::једнина, attr_t::лице1);
			CHECK(L"идем", L"ићи", attr_t::једнина, attr_t::лице1);
			CHECK(L"једем", L"јести", attr_t::једнина, attr_t::лице1);
			CHECK(L"могу", L"моћи", attr_t::једнина, attr_t::лице1);
			CHECK(L"пије", L"пити", attr_t::једнина, attr_t::лице3);
			CHECK(L"можемо", L"моћи", attr_t::множина, attr_t::лице1);
			CHECK(L"пишемо", L"писати", attr_t::множина, attr_t::лице1);
			CHECK(L"хоћемо", L"хтети", attr_t::множина, attr_t::лице1);
		}

		TEST_METHOD(check_some_adjective_forms)
		{
			CHECK(L"лошег", L"лош", attr_t::мушки, attr_t::једнина, attr_t::генитив);
		}

		bool dictionary_word_exists(const std::wstring& st)
		{
			for (auto &w : Serbian::dictWords())
			{
				if (w.word == st)
					return true;
			}
			return false;
		}

		TEST_METHOD(serbian_derived_words)
		{
#define EXISTS(word) Assert::IsTrue(dictionary_word_exists(word), word)
#define NEXISTS(word) Assert::IsFalse(dictionary_word_exists(word), word)

			// глаг -> имен
			NEXISTS(L"биње");
			NEXISTS(L"волење");
			EXISTS(L"вољење");
			NEXISTS(L"видење");
			EXISTS(L"виђање");
			NEXISTS(L"јесње");
			EXISTS(L"једење");

			// имен -> прид
			NEXISTS(L"женаов");
			NEXISTS(L"коњов");
			EXISTS(L"коњев");

			// прид -> прил
			NEXISTS(L"ружано");
			EXISTS(L"ружно");

			// имен -> имен-деминутив
			EXISTS(L"женица");
			EXISTS(L"мушкарчић");

			// имен -> имен-аугментатив
			EXISTS(L"женетина");
			EXISTS(L"кућетина");
		}

		TEST_METHOD(serbian_grammar_rules)
		{
			test(L"ја гледам");
			test(L"ја радиш", false);
			test(L"ти радиш");
			test(L"он пева");
			test(L"он певам", false);

			// Именичке синтагме
			test(L"лепа жена");
			test(L"леп кућа", false);

			//// Прилошке одредбе
			test(L"у школу");
			test(L"у школа", false);

			// Реченице
			test(L"ја идем у школу");
			test(L"ја идем у школа", false);	// wrong case
			test(L"ја иде у школу", false);		// wrong verb declination

			// Прелазни глаголи
			test(L"видети школу");
			test(L"гледати кућу");
			test(L"ићи школу", false);
			test(L"играти кућу", false);
		}

		TEST_METHOD(dictionary_words_count)
		{
			// Update this number when necessary
			Assert::AreEqual<int>(188, Serbian::dictWords().size());
		}

		// This test helps keeping awereness of the number of word forms.
		// It should prevent from adding more word forms unintentionally.
		TEST_METHOD(word_forms_count)
		{
			int count = 0;
			for (auto& dw : Serbian::dictWords())
			{
				int increment = dw.words.size();
				Assert::IsFalse(increment == 0);
				count += increment;
			}

			// Update this number when necessary
			Assert::AreEqual<int>(3884, count);
		}

		TEST_METHOD(random_test)
		{
			for (int i = 0; i < 10; i++)
			{
				std::wstring str = translator::random_sentence<Serbian>(i);
				test(str);
			}
		}
	};
}