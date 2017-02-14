#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TranslatorTest
{
	TEST_CLASS(LanguageTests)
	{
	public:

		using pattern_n = translator::pattern<char>;
		using pattern_w = translator::pattern<wchar_t>;

		TEST_METHOD(pattern_match_test_narrow)
		{
			pattern_n p1("*s");
			Assert::IsTrue(p1.match("goes"));
			Assert::IsTrue(p1.match("toes"));
			Assert::IsTrue(p1.match("skins"));
			Assert::IsFalse(p1.match("so"));
			Assert::IsFalse(p1.match("skin"));

			pattern_n p2("pre*ing");
			Assert::IsTrue(p2.match("presenting"));
			Assert::IsTrue(p2.match("precautioning"));
			Assert::IsFalse(p2.match("presentation"));
			Assert::IsFalse(p2.match("going"));

			Assert::IsFalse(p1 > p2);
			Assert::IsFalse(p2 > p1);
		}

		TEST_METHOD(pattern_match_test_wide)
		{
			pattern_w p1(L"*ти");
			Assert::IsTrue(p1.match(L"радити"));
			Assert::IsTrue(p1.match(L"певати"));
			Assert::IsTrue(p1.match(L"јести"));
			Assert::IsFalse(p1.match(L"тим"));

			pattern_w p2(L"прет*ти");
			Assert::IsTrue(p2.match(L"претплатити"));
			Assert::IsFalse(p2.match(L"прети"));

			Assert::IsFalse(p1 > p2);
			Assert::IsTrue(p2 > p1);

			pattern_w lic1(L"*м");
			pattern_w lic2(L"*те");
			pattern_w past(L"пре*ла");
			Assert::AreEqual<std::wstring>(L"гледам", p1.match_and_transform(L"гледати", lic1));
			Assert::AreEqual<std::wstring>(L"радите", p1.match_and_transform(L"радити", lic2));
			Assert::AreEqual<std::wstring>(L"предала", p1.match_and_transform(L"дати", past));
		}

		TEST_METHOD(pattern_no_joker)
		{
			// Narrow strings
			pattern_n pn("you");
			Assert::IsTrue(pn.match("you"));
			Assert::IsFalse(pn.match("yours"));
			Assert::IsFalse(pn.match("yo"));
			pattern_n pn2("your");
			Assert::AreEqual<std::string>("your", pn.match_and_transform("you", pn2));

			// Wide strings
			pattern_w pw(L"они");
			Assert::IsTrue(pw.match(L"они"));
			Assert::IsFalse(pw.match(L"он"));
			Assert::IsFalse(pw.match(L"онима"));
			pattern_w pw2(L"њихов");
			Assert::AreEqual<std::wstring>(L"њихов", pw.match_and_transform(L"они", pw2));
		}
	};
}