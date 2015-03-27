#include "stdafx.h"
#include <initializer_list>
#include "../TranslatorCpp/Languages/Serbian.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TranslatorTest
{
	TEST_CLASS(SerbianTest)
	{
	public:

		void test(const std::initializer_list<std::wstring>& ss, bool expected=true)
		{
			Serbian serbian;
			for (const auto& s : ss)
			{
				if (expected)
					Assert::IsTrue(translator::parse<Serbian>(s, serbian));
				else
					Assert::IsFalse(translator::parse<Serbian>(s, serbian));
			}
		}

		TEST_METHOD(serbian_positive_tests)
		{
			test(
			{
				L"ја гледам",
				L"ти радиш",
				L"он пева",
			});
		}

		TEST_METHOD(serbian_negative_tests)
		{
			test(
			{
				L"ја радиш",
				L"он певам",
			}, false);
		}
	};
}