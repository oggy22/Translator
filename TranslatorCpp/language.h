#pragma once

#include <algorithm>
#include <cassert>
#include <set>
#include <string>
#include <vector>
#include <utility>

namespace translator
{
	using namespace std;

	template <typename Char>
	class pattern
	{
		using string_t = basic_string < Char >;
		string_t pre, post;

		int length() const
		{
			return pre.length() + post.length();
		}

		static bool starts_with(const string_t& str, const string_t& prefix)
		{
			if (prefix.length() > str.length())
				return false;

			return equal(prefix.cbegin(), prefix.end(), str.cbegin());
		}

		static bool ends_with(const string_t& str, const string_t& sufix)
		{
			if (sufix.length() > str.length())
				return false;

			return equal(sufix.cbegin(), sufix.end(), str.cbegin() + str.size() - sufix.size());
		}

	public:
		pattern(const string_t& s)
		{
			const Char joker = Char('%');
			const string_t::size_type pos = s.find(joker);
			assert(0 <= pos && pos < s.length());
			assert(s.find(joker, pos + 1) == string_t::npos);
			pre = s.substr(0, pos);
			post = s.substr(pos + 1);
		}

		bool operator>(const pattern& other)
		{
			return starts_with(pre, other.pre) && ends_with(post, other.post);
		}

		bool match(const basic_string<Char>& s) const
		{
			if (s.compare(0, pre.length(), pre))
				return false;

			if (s.compare(s.length() - post.length(), post.length(), post))
				return false;

			if (pre.length() + post.length() >= s.length())
				return false;

			return true;
		}

		string_t match_and_transform(const string_t& input, const pattern& to) const
		{
			if (!match(input))
				return string_t();

			int core_len = input.length() - length();

			return to.pre + input.substr(pre.length(), core_len) + to.post;
		}
	};

	template <class Language>
	struct word_t
	{
		typename Language::string_t _word;
		set<typename Language::attributes> attrs;
	};

	template <class Language>
	struct dictionary_word
	{	//todo: these should be const. VS update 5 probably has this bug fixed.
		/*const*/ typename Language::string_t word;
		/*const*/ typename Language::word_type wordtype;
		/*const*/ set<typename Language::attributes> attrs;
		mutable vector<word_t<Language>> words;	//todo: this is a hack
	};

	template <class Language>
	struct word_rule
	{
		pattern<typename Language::letter> source;
		pattern<typename Language::letter> destination;
		typename Language::word_type wt;
		set<typename Language::attributes> attrs;
	};

	template<typename Language>
	void populate_words(const vector<dictionary_word<Language>>& words, const vector<word_rule<Language>> word_rules)
	{
		for (auto& w : words)
		{
			using namespace std;
			vector<word_t<Language>> new_words;

			for (auto& r : word_rules)
			{
				if (r.wt != w.wordtype)
					continue;

				if (any_of(w.words.begin(), w.words.end(), [&](const word_t<Language>)
				{	return r.attrs == w.attrs;	}))
				continue;

				if (!r.source.match(w.word))
					continue;

				auto iter = find_if(new_words.begin(), new_words.end(),
					[&](const word_t<Language>& w)
				{
					return r.attrs == w.attrs;
				});

				Language::string_t word = r.source.match_and_transform(w.word, r.destination);
				assert(word.length() != 0);
				if (iter == new_words.end())
					new_words.emplace_back(word_t<Language> { word, r.attrs });
				else
					iter->_word = word;
			}
			w.words.insert(w.words.end(), new_words.begin(), new_words.end());
		}
	}

	template <class SourceLanguage, class DestinationLanguage>
	class translator
	{
		const SourceLanguage &source;
		const DestinationLanguage &destination;

	public:
		translator(const SourceLanguage& source, const DestinationLanguage& destination)
			: source(source), destination(destination)
		{ }

		typename DestinationLanguage::string_t translate(const typename SourceLanguage::string_t text)
		{
			wcout << "Trying to translate : " << text << endl;
			return DestinationLanguage::string_t();
		}

	private:
		typename DestinationLanguage::string_t translate(const vector<const typename SourceLanguage::string_t> text)
		{
		}
	};
}