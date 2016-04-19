#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TranslatorTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(pattern_match_test_narrow)
		{
			translator::pattern<char> p1("*s");
			Assert::IsTrue(p1.match("goes"));
			Assert::IsTrue(p1.match("toes"));
			Assert::IsTrue(p1.match("skins"));
			Assert::IsFalse(p1.match("so"));
			Assert::IsFalse(p1.match("skin"));

			translator::pattern<char> p2("pre*ing");
			Assert::IsTrue(p2.match("prescreening"));
			Assert::IsTrue(p2.match("prematuring"));
			Assert::IsFalse(p2.match("presenation"));
			Assert::IsFalse(p2.match("going"));

			Assert::IsFalse(p1 > p2);
			Assert::IsFalse(p2 > p1);

			//p1.match_and_transform()
		}

		TEST_METHOD(pattern_match_test_wide)
		{
			translator::pattern<wchar_t> p1(L"*ти");
			Assert::IsTrue(p1.match(L"радити"));
			Assert::IsTrue(p1.match(L"певати"));
			Assert::IsTrue(p1.match(L"јести"));
			Assert::IsFalse(p1.match(L"тим"));

			translator::pattern<wchar_t> p2(L"прет*ти");
			Assert::IsTrue(p2.match(L"претплатити"));
			Assert::IsFalse(p2.match(L"прети"));

			Assert::IsFalse(p1 > p2);
			Assert::IsTrue(p2 > p1);

			translator::pattern<wchar_t> lic1(L"*м");
			translator::pattern<wchar_t> lic2(L"*те");
			translator::pattern<wchar_t> past(L"пре*ла");
			Assert::AreEqual<std::wstring>(L"гледам", p1.match_and_transform(L"гледати", lic1));
			Assert::AreEqual<std::wstring>(L"радите", p1.match_and_transform(L"радити", lic2));
			Assert::AreEqual<std::wstring>(L"предала", p1.match_and_transform(L"дати", past));
		}
	};
}