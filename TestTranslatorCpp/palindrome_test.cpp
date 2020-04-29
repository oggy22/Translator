#include "stdafx.h"
#include "../TranslatorCpp/Languages/Serbian.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TranslatorTest
{
	TEST_CLASS(PalindromeTest)
	{
	public:

		TEST_METHOD(ana_voli_milovana)
		{
			std::vector<std::wstring> words = { L"ана", L"воли", L"милована" };
			auto results = find_palindromes<wchar_t>(words, 8);

			Assert::AreEqual<const std::wstring&>(
				L"ана воли милована",
				*std::lower_bound(results.begin(), results.end(), L"ана воли милована"));
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(misa_vidi_vasim)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(misa_vidi_vasim)
		{
			std::vector<std::wstring> words;
			for (const auto& word : Serbian::dictWords())
			{
				for (const auto& form : word.words)
					words.push_back(form.word);
			}

			std::sort(words.begin(), words.end());
			words.erase(unique(words.begin(), words.end()), words.end());
			auto results = find_palindromes<wchar_t>(words, 8);

			// If vector of was initialized this way, the test would pass:
			//std::vector<std::wstring> words = { L"миша", L"види", L"вашим" };
			//auto results = find_palindromes<wchar_t>(words, 8);

			// Bug:
			Assert::IsTrue(results.count(L"миша види вашим"));
		}

		TEST_METHOD(trie_test)
		{
			std::vector<std::string> words = { "ab", "abb", "abc", "x", "xyz" };
			trie_node<char> root(words);
			Assert::IsTrue(!root.is_wordend());
			for (auto word : words)
			{
				trie_node<char> *p = root.traverse(word);
				Assert::IsNotNull(p);
				Assert::IsTrue(p->is_wordend());
			}
		}

		TEST_METHOD(serbian_palindromes)
		{
			std::vector<std::wstring> words;
			for (const auto& word : Serbian::dictWords())
			{
				for (const auto& form : word.words)
					words.push_back(form.word);
			}

			std::sort(words.begin(), words.end());
			words.erase(unique(words.begin(), words.end()), words.end());
			auto results = find_palindromes<wchar_t>(words, DebugRelease(4, 7));

			//Assert::IsTrue(results.count(L"ана"));
			Assert::IsTrue(results.count(L"ане жена"));
			Assert::IsTrue(results.count(L"могу дугом"));
			
			// Too long for Debug
#if NDEBUG
			Assert::IsTrue(results.count(L"ана воли милована"));
			Assert::IsTrue(results.count(L"мамин и татин имам"));
			Assert::IsTrue(results.count(L"мењате шетањем"));
			//Assert::IsTrue(results.count(L"мењати пса васпитањем"));
			Assert::IsTrue(results.count(L"миловање мења волим"));
			Assert::IsTrue(results.count(L"миловања сања волим"));
			Assert::IsTrue(results.count(L"могу деде дугом"));
			Assert::IsTrue(results.count(L"оне жене мене жено"));
#endif
		}

		bool contains(const std::vector<std::wstring>& container, const std::wstring& v)
		{
			auto it = std::lower_bound(
				container.begin(),
				container.end(),
				v);

			return it != container.end() && *it == v;
		}
	};
}