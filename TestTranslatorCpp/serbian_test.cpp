#include "stdafx.h"
#include "../TranslatorCpp/Languages/Serbian.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TranslatorTest
{
	TEST_CLASS(SerbianTest)
	{
		void test(const std::wstring& st, bool expected=true)
		{
			Serbian serbian;
			if (expected)
				Assert::IsTrue(translator::parse<Serbian>(st, serbian));
			else
				Assert::IsFalse(translator::parse<Serbian>(st, serbian));
		}
		Serbian serbian;

	public:
		TEST_METHOD(every_word_composed_of_serbian_letters)
		{
			for (const auto& word : serbian.dictWords)
			{
				for (const auto& w : word.words)
				{
					for (wchar_t c : w._word)
						Assert::AreNotEqual(std::wstring::npos, serbian.stAlphabet.find(c));
				}
			}
		}

		TEST_METHOD(every_noun_has_gender)
		{
			for (const auto& word : serbian.dictWords)
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

		TEST_METHOD(each_noun_has_7cases)
		{
			for (const auto& word : serbian.dictWords)
			{
				if (word.wordtype == Serbian::word_type::именица)
					Assert::AreEqual<int>(7 * 2, word.words.size(), (word.word + L" doesn't have 14 forms").c_str());
			}
		}

		TEST_METHOD(each_verb_has_3x2_present_forms)
		{
			for (const auto& word : serbian.dictWords)
			{
				if (word.wordtype == Serbian::word_type::глагол)
					Assert::AreEqual<int>(3 * 2, word.words.size(), (word.word + L" doesn't have 6 forms").c_str());
			}
		}

		TEST_METHOD(serbian_rules)
		{
			test(L"ја гледам");
			test(L"ја радиш", false);
			test(L"ти радиш");
			test(L"он пева");
			test(L"он певам", false);
		}
	};
}