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
			auto results = find_palindromes<wchar_t>(words, 30);
			
			Assert::AreEqual<const std::wstring&>(
				L"ана воли милована",
				*std::lower_bound(results.begin(), results.end(), L"ана воли милована"));
		}

		TEST_METHOD(trie_test)
		{
			std::vector<std::string> words = { "ab", "abb", "abc", "xyz" };
			trie_node<char> root(words);
			for (auto word : words)
				Assert::IsNotNull(root.traverse(word));
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
			auto results = find_palindromes<wchar_t>(words, 10);
			std::sort(results.begin(), results.end());

			Assert::IsTrue(contains(results, L"ана"));
			Assert::IsTrue(contains(results, L"могу дугом"));
			//Assert::IsTrue(contains(results, L"ана волимилована"));
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