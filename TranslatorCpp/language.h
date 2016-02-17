#pragma once

#include <algorithm>
#include <cassert>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <iterator>

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
			const typename string_t::size_type pos = s.find(joker);
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
	struct word_t;

	template <class Language>
	struct dictionary_word
	{	//todo: these should be const. VS update 5 probably has this bug fixed.
		/*const*/ typename Language::string_t word;
		/*const*/ typename Language::word_type wordtype;
		/*const*/ set<typename Language::attributes> attrs;
		mutable vector<word_t<Language>> words;	//todo: this is a hack
	};

	template <class Language>
	struct word_t
	{
		typename Language::string_t _word;
		set<typename Language::attributes> attrs;
		dictionary_word<Language> *p_dw;

		bool contains(typename Language::attributes a) const
		{
			return attrs.count(a) || p_dw->attrs.count(a);
		}

		typename Language::attributes operator[](typename Language::attribute_categories c)
		{
			for (auto a : attrs)
				if (true)
					return 
		}
	};

	template <class Language>
	class node
	{
		using attrs_t = typename Language::attributes;
		using cats_t = typename Language::attribute_categories;

		typename Language::string_t word;
		typename Language::word_type wordtype;
		set<cats_t> cats;
		set<attrs_t> attrs;

	public:
		node(
			typename Language::string_t word,
			typename Language::word_type wordtype
			) : word(word), wordtype(wordtype) {}

		node(
			typename Language::word_type wordtype
			) : wordtype(wordtype) {}

		template <typename... Values>
		node(typename Language::word_type wordtype, attrs_t a, Values... values) : node(wordtype, values...)
		{
			attrs.insert(a);
		}

		template <typename... Values>
		node(typename Language::word_type wordtype, cats_t c, Values... values) : node(wordtype, values...)
		{
			cats.insert(c);
		}

		bool accept(const word_t<Language>& w, std::map<cats_t, attrs_t>& values) const
		{
			if (!word.empty() && word != w._word)
				return false;

			if (this->wordtype != w.p_dw->wordtype)
				return false;

			// Check attributes
			for (auto a : attrs)
			{
				if (w.attrs.count(a))
					continue;

				if (w.p_dw->attrs.count(a))
					continue;

				return false;
			}

			// Check categories
			for (auto c : cats)
			{
				auto iter = values.find(c);
				//if (iter != values.end() && iter->second != 
			}

			return true;
		}
	};

	template <class Language>
	struct rule
	{
		using node_t = node<Language>;
		using right_type = vector<node_t>;
		using size_type = typename right_type::size_type;
		
		node_t left;
		right_type right;
		
		size_type size() const
		{
			return right.size();
		}

		const node_t& operator[](int i) const
		{
			return right[i];
		}
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
	void populate_words(/*const*/ vector<dictionary_word<Language>>& words, const vector<word_rule<Language>> word_rules)
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

				typename Language::string_t word = r.source.match_and_transform(w.word, r.destination);
				assert(word.length() != 0);
				if (iter == new_words.end())
					new_words.emplace_back(word_t<Language> { word, r.attrs});
				else
					iter->_word = word;
			}
			w.words.insert(w.words.end(), new_words.begin(), new_words.end()); 
			std::for_each(w.words.begin(), w.words.end(), [&](word_t<Language>& dw)
			{
				dw.p_dw = &w;
			});
		}
	}

	template <typename Language>
	bool parse(typename Language::string_t s, const Language& language)
	{
		// construct a stream from the string
		std::basic_stringstream<typename Language::letter> strstr(s);

		// use stream iterators to copy the stream to the vector as whitespace separated strings
		std::istream_iterator<typename Language::string_t, typename Language::letter> it(strstr);
		std::istream_iterator<typename Language::string_t, typename Language::letter> end;
		std::vector<typename Language::string_t> vs(it, end);

		std::vector<std::set<word_t<Language>*>> words(vs.size());

		// Lexical analysis
		for (unsigned int i = 0; i < vs.size(); i++)
		{
			getWords<Language>(language.dictWords,
				[&](word_t<Language>& w)
			{
				if (w._word == vs[i])
					words[i].insert(&w);
			});
			if (words[i].size() == 0)
				return false;
		}

		// Syntax analysis
		for (const auto& rule : language.rules)
		{
			if (rule.size() != vs.size())
				continue;

			using attrs_t = typename Language::attributes;
			using cats_t = typename Language::attribute_categories;

			std::map<cats_t, attrs_t> values;
			for (unsigned int i = 0; i < rule.size(); i++)
			{
				if (!rule[i].accept(**words[i].begin(), values))
					return false;
			}

			return true;
		}

		return false;
	}

	template<typename Language, typename Lambda>
	void getWords(const vector<dictionary_word<Language>>& words, Lambda lambda)
	{
		for (const auto& dw : words)
			for (auto& w : dw.words)
				lambda(w);
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