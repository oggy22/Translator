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
	case Serbian::word_type::прилог: wout << L"прилог"; break;
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

		TEST_METHOD(various_checks_for_serbian_letters)
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
					wchar_t prev_c = 0;
					for (wchar_t c : w.word)
					{
						if (alphabet.find(c) == alphabet.end())
							Assert::Fail(w.word.c_str());

						// Double letters are usually no-no
						if (prev_c == c)
						{
							if (c == L'ј' && w.word.find(L"најј") == 0)
							{
								// do nothing
							}
							else
								Assert::Fail(w.word.c_str());
						}

						prev_c = c;
					}
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

		void test_word_forms(const translator::dictionary_word<Serbian> &word, myset<attr_t> set1)
		{
			for (attr_t a : set1)
				Assert::IsTrue(word(a), L"Missing wordform");
		}

		void test_word_forms(const translator::dictionary_word<Serbian> &word, myset<attr_t> set1, myset<attr_t> set2)
		{
			for (attr_t a1 : set1)
				for (attr_t a2 : set2)
					Assert::IsTrue(word(a1,a2),
						(word.word + std::wstring(L"Missing wordform 2 attrs")).c_str());
		}

		void test_word_forms(const translator::dictionary_word<Serbian> &word, myset<attr_t> set1, myset<attr_t> set2, myset<attr_t> set3)
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
					std::wstringstream ss;
					ss << word.word << L" has less than 14 forms: " << word.words.size();
					Assert::IsTrue(7 * 2 <= word.words.size(), ss.str().c_str());
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
			CHECK(L"благом", L"благо", attr_t::једнина, attr_t::инструментал);
			CHECK(L"блага", L"благо", attr_t::множина, attr_t::номинатив);
			CHECK(L"времена", L"време", attr_t::једнина, attr_t::генитив);
			CHECK(L"вуче", L"вук", attr_t::једнина, attr_t::вокатив);
			CHECK(L"дрвету", L"дрво", attr_t::једнина, attr_t::датив);
			CHECK(L"жену", L"жена", attr_t::једнина, attr_t::акузатив);
			CHECK(L"зече", L"зец", attr_t::једнина, attr_t::вокатив);
			CHECK(L"имена", L"име", attr_t::једнина, attr_t::генитив);
			CHECK(L"јајетом", L"јаје", attr_t::једнина, attr_t::инструментал);
			CHECK(L"коња", L"коњ", attr_t::једнина, attr_t::акузатив);
			CHECK(L"људи", L"човек", attr_t::множина, attr_t::номинатив);
			CHECK(L"љубави", L"љубав", attr_t::множина, attr_t::генитив);
			CHECK(L"мишеви", L"миш", attr_t::множина, attr_t::номинатив);
			//CHECK(L"мисли", L"мисао", attr_t::једнина, attr_t::генитив);
			//CHECK(L"мисли", L"мисао", attr_t::множина, attr_t::номинатив);
			CHECK(L"мушкарци", L"мушкарац", attr_t::множина, attr_t::номинатив);
			CHECK(L"очи", L"око", attr_t::множина, attr_t::номинатив);
			CHECK(L"орах", L"орах", attr_t::једнина, attr_t::акузатив);
			CHECK(L"ораси", L"орах", attr_t::множина, attr_t::номинатив);
			CHECK(L"орахе", L"орах", attr_t::множина, attr_t::акузатив);
			CHECK(L"орлу", L"орао", attr_t::једнина, attr_t::датив);
			CHECK(L"псом", L"пас", attr_t::једнина, attr_t::инструментал);
			CHECK(L"петлу", L"петао", attr_t::једнина, attr_t::датив);
			CHECK(L"пиву", L"пиво", attr_t::једнина, attr_t::датив);
			CHECK(L"пилету", L"пиле", attr_t::једнина, attr_t::датив);
			CHECK(L"племену", L"племе", attr_t::једнина, attr_t::датив);
			CHECK(L"синови", L"син", attr_t::множина, attr_t::номинатив);
			CHECK(L"сунца", L"сунце", attr_t::једнина, attr_t::генитив);
			CHECK(L"човече", L"човек", attr_t::једнина, attr_t::вокатив);
			CHECK(L"унуци", L"унук", attr_t::множина, attr_t::номинатив);

			// Accusative male
			CHECK(L"човека", L"човек", attr_t::једнина, attr_t::акузатив);
			CHECK(L"милована", L"милован", attr_t::једнина, attr_t::акузатив);
			CHECK(L"кромпир", L"кромпир", attr_t::једнина, attr_t::акузатив);

			// време, племе, семе
			CHECK(L"времена", L"време", attr_t::једнина, attr_t::генитив);
			CHECK(L"времену", L"време", attr_t::једнина, attr_t::локатив);
			CHECK(L"племе", L"племе", attr_t::једнина, attr_t::акузатив);
			CHECK(L"семеном", L"семе", attr_t::једнина, attr_t::инструментал);
			CHECK(L"племена", L"племе", attr_t::множина, attr_t::номинатив);
			CHECK(L"семенима", L"семе", attr_t::множина, attr_t::инструментал);

			// Glagolske imenice
			CHECK(L"учења", L"учење", attr_t::једнина, attr_t::генитив);
			CHECK(L"учењу", L"учење", attr_t::једнина, attr_t::локатив);
		}

		TEST_METHOD(check_some_verb_forms)
		{
			CHECK(L"сам", L"бити", attr_t::једнина, attr_t::лице1);
			CHECK(L"идем", L"ићи", attr_t::једнина, attr_t::лице1);
			CHECK(L"једем", L"јести", attr_t::једнина, attr_t::лице1);
			CHECK(L"милујем", L"миловати", attr_t::једнина, attr_t::лице1);
			CHECK(L"могу", L"моћи", attr_t::једнина, attr_t::лице1);
			CHECK(L"пије", L"пити", attr_t::једнина, attr_t::лице3);
			CHECK(L"можемо", L"моћи", attr_t::множина, attr_t::лице1);
			CHECK(L"пишемо", L"писати", attr_t::множина, attr_t::лице1);
			CHECK(L"хоћемо", L"хтети", attr_t::множина, attr_t::лице1);
			CHECK(L"плачем", L"плакати", attr_t::једнина, attr_t::лице1);
		}

		TEST_METHOD(check_some_adjective_forms)
		{
			//CHECK(L"гледана", L"гледан", attr_t::женски, attr_t::једнина, attr_t::номинатив);
			CHECK(L"лошег", L"лош", attr_t::мушки, attr_t::једнина, attr_t::генитив);
			CHECK(L"моје", L"мој", attr_t::средњи, attr_t::једнина, attr_t::номинатив);
			CHECK(L"стара", L"стар", attr_t::женски, attr_t::једнина, attr_t::номинатив);
		}

		TEST_METHOD(check_some_adjverb_forms)
		{
			CHECK(L"веће", L"велико", attr_t::компаратив);
			CHECK(L"глупље", L"глупо", attr_t::компаратив);
			CHECK(L"боље", L"добро", attr_t::компаратив);
			CHECK(L"дуже", L"дуго", attr_t::компаратив);
			CHECK(L"жуће", L"жуто", attr_t::компаратив);
			CHECK(L"зеленије", L"зелено", attr_t::компаратив);
			CHECK(L"јаче", L"јако", attr_t::компаратив);
			CHECK(L"краће", L"кратко", attr_t::компаратив);
			CHECK(L"лепше", L"лепо", attr_t::компаратив);
			CHECK(L"мање", L"мало", attr_t::компаратив);
			CHECK(L"скупље", L"скупо", attr_t::компаратив);
			CHECK(L"црње", L"црно", attr_t::компаратив);
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
			EXISTS(L"полицајчев");
			EXISTS(L"сунчев");

			// прид -> прил
			EXISTS(L"јако");
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
			test(L"са пас", false);
			test(L"са псом");

			// Реченице
			test(L"ана воли милована");
			test(L"ана воли милован", false);
			test(L"ања воли миловања");
			test(L"ања воли миловање");
			//test(L"аца питам плема");
			test(L"ја идем у школу");
			test(L"ја идем у школа", false);	// wrong case
			test(L"ја иде у школу", false);		// wrong verb declination
			//test(L"малу школу ради", false);	// non-nominative predicate

			// Прелазни глаголи
			test(L"видети школу");
			test(L"гледати кућу");
			test(L"ићи школу", false);
			test(L"играти кућу", false);
		}

		TEST_METHOD(dictionary_words_count)
		{
			// Update this number when necessary
			Assert::AreEqual<int>(760, Serbian::dictWords().size());
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
			Assert::AreEqual<int>(17525, count);
		}

		TEST_METHOD(serbian_numbers_to_1000)
		{
			for (int i = 0; i < 1000; i++)
			{
				test_output << i << ": " << Serbian::number(i) << std::endl;
				Assert::IsTrue(Serbian::number(i) != L"");
			}
		}

		TEST_METHOD(serbian_numbers)
		{
			Assert::AreEqual(L"нула", Serbian::number(0).c_str());
			Assert::AreEqual(L"један", Serbian::number(1).c_str());
			Assert::AreEqual(L"два", Serbian::number(2).c_str());

			//10:
			Assert::AreEqual(L"десет", Serbian::number(10).c_str());
			Assert::AreEqual(L"једанаест", Serbian::number(11).c_str());
			Assert::AreEqual(L"дванаест", Serbian::number(12).c_str());
			Assert::AreEqual(L"четрнаест", Serbian::number(14).c_str());

			//20:
			Assert::AreEqual(L"двадесет", Serbian::number(20).c_str());
			Assert::AreEqual(L"двадесет један", Serbian::number(21).c_str());

			//30:
			Assert::AreEqual(L"тридесет", Serbian::number(30).c_str());
			Assert::AreEqual(L"тридесет два", Serbian::number(32).c_str());

			//90:
			Assert::AreEqual(L"деведесет један", Serbian::number(91).c_str());

			//100:
			Assert::AreEqual(L"сто", Serbian::number(100).c_str());
			Assert::AreEqual(L"сто један", Serbian::number(101).c_str());
			Assert::AreEqual(L"сто десет", Serbian::number(110).c_str());
			Assert::AreEqual(L"сто двадесет два", Serbian::number(122).c_str());

			//999:
			Assert::AreEqual(L"деветсто деведесет девет", Serbian::number(999).c_str());
		}

		TEST_METHOD(random_test)
		{
			for (int i = 0; i < 100; i++)
			{
				std::wstring str = translator::random_sentence<Serbian>(i);
				Logger::WriteMessage(str.c_str());
				test(str);
			}
		}
	};
}