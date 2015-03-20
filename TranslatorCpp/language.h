#pragma once

#include <string>
#include <set>
#include <vector>
#include <utility>
#include <cassert>

namespace translator
{
	template <typename Char>
	class pattern
	{
		using string_t = std::basic_string < Char >;
		std::basic_string<Char> pre, post;

	public:
		pattern(const std::basic_string<Char>& s)
		{
			const Char joker = Char('%');
			const string_t::size_type pos = s.find(joker);
			assert(0 <= pos && pos < s.length());
			assert(s.find(joker, pos + 1) == string_t::npos);
			pre = s.substr(0, pos);
			post = s.substr(pos + 1);
		}

		bool match(const std::basic_string<Char>& s)
		{
			if (s.compare(0, pre.length(), pre))
				return false;

			if (s.compare(s.length() - post.length(), post.length(), post))
				return false;

			return true;
		}
	};

	template <class Language>
	struct word_t
	{
		/*const*/ std::string _word;
		/*const */std::set<typename Language::attributes> attrs;
	};

	template <class Language>
	struct dictionary_word
	{
		/*const*/ typename Language::letters word;
		/*const*/ typename Language::word_type wordtype;
		/*const*/ std::set<typename Language::attributes> attrs;
		std::vector<word_t<Language>> words;

		dictionary_word(
			const typename Language::letters word,
			typename Language::word_type wt,
			const std::set<typename Language::attributes>& attrs,
			const std::vector<std::pair<typename Language::letters, std::set<typename Language::attributes>>>& s =
				  std::vector<std::pair<typename Language::letters, std::set<typename Language::attributes>>>()
				  )
			: word(word), wordtype(wt), attrs(attrs)
		{
			for (const auto& p : s)
			{ }
		}

		dictionary_word(const dictionary_word& dw) : word(dw.word), wordtype(dw.wordtype)
		{
		}

		const dictionary_word& operator=(const dictionary_word& dw)
		{
			word = dw.word;
			return *this;
		}
	};

	template <class Language>
	struct word_rule
	{
		pattern<typename Language::letter> source;
		pattern<typename Language::letter> destination;
		typename Language::word_type wt;
		std::set<typename Language::attributes> attrs;
	};

	template <class SourceLanguage, class DestinationLanguage>
	class translator
	{
		const SourceLanguage &source;
		const DestinationLanguage &destination;

	public:
		translator(const SourceLanguage& source, const DestinationLanguage& destination)
			: source(source), destination(destination)
		{ }

		typename DestinationLanguage::letters translate(const typename SourceLanguage::letters text)
		{
			std::wcout << "Trying to translate : " << text << std::endl;
			return DestinationLanguage::letters();
		}

	private:
		typename DestinationLanguage::letters translate(const std::vector<const typename SourceLanguage::letters> text)
		{

		}
	};
}