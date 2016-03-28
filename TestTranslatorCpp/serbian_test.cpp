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