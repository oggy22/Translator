#pragma once

#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

#ifdef _DEBUG
#include <set>
#include <map>
#define set std::set
#define map std::map
#else
#include <unordered_set>
#include <unordered_map>
#define set std::unordered_set
#define map std::unordered_map
#endif

#include "parsing_triangle.h"
#include "Assert.h"

namespace translator
{
	using namespace std;

	template <typename Language>
	class attribute_manager
	{
		using attr_t = typename Language::attributes;
		using cat_t = typename Language::attribute_categories;
		map<cat_t, attr_t> mapping;
		set<cat_t> free_cat;
		set<attr_t> free_attr;

	public:
		attribute_manager() {}

		template <typename... Values>
		attribute_manager(attr_t attr, Values... values) : attribute_manager(values...)
		{
			ASSERT_WITH_MSG(!free_attr.count(attr), "Attribute already contained");
			free_attr.emplace(attr)
		}

		template <typename... Values>
		attribute_manager(cat_t cat, Values... values) : attribute_manager(values...)
		{
			ASSERT_WITH_MSG(free_cat.count(cat), "Category already contained");
			free_cat.emplace(cat)
		}

		template <typename... Args>
		attribute_manager(const set<attr_t>& attrs, Args... args) : attribute_manager(args...)
		{
			for (attr_t a : attrs)
			{
				auto pair = Language::belongs_to_category.find(a);
				if (pair == Language::belongs_to_category.end())
					free_attr.insert(a);
				else
					mapping[pair->second] = a;
			}
		}

		bool operator()(cat_t c) const
		{
			return mapping.count(c) > 0;
		}

		bool operator()(attr_t a) const
		{
			if (free_attr.count(a) > 0)
				return true;

			for (const auto& pair : mapping)
				if (pair.second == a)
					return true;

			return false;
		}

		bool operator[](cat_t c) const
		{
			auto iter = mapping.find(c);
			ASSERT(iter != mapping.end());
			return *iter;
		}

		bool operator+=(const attribute_manager<Language>& am)
		{
			for (const auto& pair : am.mapping)
				if (mapping.count(pair.first) > 0 && mapping[pair.first] != pair.second)
					return false;

			free_cat.insert(am.free_cat.begin(), am.free_cat.end());

			for (const auto& pair : am.mapping)
				mapping[pair.first] = pair.second;

			for (const auto& pair : mapping)
				free_cat.erase(pair.first);
			
			free_attr.insert(am.free_attr.begin(), am.free_attr.end());
			
			check_consistency();
			
			return true;
		}

		inline void check_consistency()
		{
			for (auto attr : free_attr)
				ASSERT(Language::belongs_to_category.count(attr) == 0);
			
			for (auto cat : free_cat)
				ASSERT(mapping.count(cat) == 0);
		}
	};

	template <typename Char>
	class pattern
	{
		using string_t = basic_string < Char >;
		string_t pre, post;

		size_t length() const
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
			const Char joker = Char('*');
			const typename string_t::size_type pos = s.find(joker);
			ASSERT(0 <= pos && pos < s.length());
			ASSERT(s.find(joker, pos + 1) == string_t::npos);
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

			size_t core_len = input.length() - length();

			return to.pre + input.substr(pre.length(), core_len) + to.post;
		}
	};

#pragma region Words

	template <class Language>
	struct word_form;

	template <class Language>
	struct dictionary_word
	{
		using attr_t = typename Language::attributes;
		const typename Language::string_t word;
		const typename Language::word_type wordtype;
		const set<typename Language::attributes> attrs;
		mutable vector<word_form<Language>> words;	//todo: this is a hack

		const word_form<Language>& find_word_form(const set<attr_t>& attrs) const
		{
			for (const auto& w : words)
				if (w.attrs == attrs)
					return w;
			ASSERT(false);
		}
		
		/// <summary>Checks if a word form with the given attribute exists</summary>
		bool operator()(attr_t a) const
		{
			for (const auto& w : words)
				if (w.attrs.size() == 1 && *w.attrs.begin() == a)
					return true;
			return false;
		}

		/// <summary>Checks if a word form with the given attributes exists</summary>
		bool operator()(attr_t a1, attr_t a2) const
		{
			for (const auto& w : words)
				if (w.attrs.size() == 2
					&& w.attrs.find(a1) != w.attrs.end()
					&& w.attrs.find(a2) != w.attrs.end())
					return true;
			return false;
		}

		/// <summary>Checks if a word form with the given attributes exists</summary>
		bool operator()(attr_t a1, attr_t a2, attr_t a3) const
		{
			for (const auto& w : words)
				if (w.attrs.size() == 3
					&& w.attrs.find(a1) != w.attrs.end()
					&& w.attrs.find(a2) != w.attrs.end()
					&& w.attrs.find(a3) != w.attrs.end())
					return true;
			return false;
		}

		const word_form<Language>& operator[](attr_t a) const
		{
			for (const auto& w : words)
				if (w.attrs.size() == 1 && *w.attrs.begin() == a)
					return w;
			ASSERT(false);
		}

		const word_form<Language>& operator[](const set<attr_t>& attrs) const
		{
			for (const auto& w : words)
				if (w.attrs == attrs)
					return w;
			ASSERT(false);
		}
	};

	template <class Language>
	struct word_form
	{
		using string_t = typename Language::string_t;
		string_t word;
		set<typename Language::attributes> attrs;
		const dictionary_word<Language> *p_dw;

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

	template <class EnumClass>
	class nullable
	{
		static_assert(std::is_enum<EnumClass>::value, "Language::attributes must be an enum");
		using underlying_type_t = typename std::underlying_type<EnumClass>::type;
		static const underlying_type_t VOID_VALUE = -1;

		union
		{
			underlying_type_t n;
			EnumClass attr;
		} data;

	public:
		nullable()
		{
			data.n = VOID_VALUE;
		}

		nullable(EnumClass attr)
		{
			data.attr = attr;
		}

		bool is_set() const
		{
			return data.n != VOID_VALUE;
		}

		EnumClass get() const
		{
			return data.attr;
		}
	};

	template <class Language>
	struct word_rule
	{
		pattern<typename Language::letter> source;
		pattern<typename Language::letter> destination;
		typename Language::word_type wt;
		set<typename Language::attributes> attrs;
		nullable<typename Language::attributes> f;
#ifdef _DEBUG
		mutable bool used;
#endif
		bool is_set() const
		{
			return f.is_set();
		}
	};

#pragma endregion

#pragma region Rules

	/// <summary>A single node in a rule, either left node, or any node on the right side</summary>
	template <class Language>
	class rule_node
	{
		using attrs_t = typename Language::attributes;
		using cats_t = typename Language::attribute_categories;

	public:
		const typename Language::string_t word;
		typename Language::word_type wordtype;
		set<cats_t> cats;
		set<attrs_t> attrs;

		const enum node_type_t { LITERAL, TOKEN } node_type;

		rule_node(
			typename Language::string_t word
			) : word(word), node_type(LITERAL) {}

		//rule_node(
		//	typename Language::string_t word,
		//	typename Language::word_type wordtype
		//	) : word(word), wordtype(wordtype) {}

		rule_node(
			typename Language::word_type wordtype
			) : wordtype(wordtype), node_type(TOKEN) {}

		template <typename... Values>
		rule_node(typename Language::word_type wordtype, attrs_t a, Values... values) : rule_node(wordtype, values...)
		{
			attrs.insert(a);
		}

		template <typename... Values>
		rule_node(typename Language::word_type wordtype, cats_t c, Values... values) : rule_node(wordtype, values...)
		{
			cats.insert(c);
		}

		bool accept(const word_form<Language>& w, map<cats_t, attrs_t>& values) const
		{
			if (!word.empty() && word != w.word)
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

	/// <summary>Contains left node and right nodes of the rule.</summary>
	template <class Language>
	class rule
	{
	public:
		using node_t = rule_node<Language>;
		using size_type = typename vector<node_t>::size_type;
		
		node_t left;
		vector<node_t> right;
		
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
	class parsing_node
	{
		using string_t = typename Language::string_t;
		const string_t st;
		const word_form<Language>* const p_wf;
		const rule<Language>* const p_rule;
		const std::vector<const parsing_node*> children;
		const attribute_manager<Language> am;

	public:
		#pragma region Constructors
		// Literal
		parsing_node(const string_t& st) : st(st), p_rule(nullptr), p_wf(nullptr)
		{
			ASSERT(is_literal() && !is_word_form() && !is_rule_application());
		}

		// Word Form
		parsing_node(const word_form<Language>& wf) : st(), p_wf(&wf), p_rule(nullptr), am(wf.attrs, wf.p_dw->attrs)
		{
			ASSERT(!is_literal() && is_word_form() && !is_rule_application());
		}

		// Rule Application
		template <typename...PN>
		parsing_node(const rule<Language>& r, const PN*... pn) : st(), p_wf(nullptr), p_rule(&r), children({ pn... })
		{
			check_parameters(pn...);
			ASSERT(!is_literal() && !is_word_form() && is_rule_application());
		}

		template <typename...PN>
		inline void check_parameters(const parsing_node<Language>* const pn, const PN* const ... pns)
		{
			check_parameters(pns...);
		}

		inline void check_parameters() {}
		#pragma endregion

		bool is_literal() const
		{
			return st.size() > 0;
		}

		bool is_word_form() const
		{
			return p_wf != nullptr;
		}

		bool is_rule_application() const
		{
			return p_rule != nullptr;
		}

		int size() const
		{
			if (p_rule == nullptr)
				return 0;
			return p_rule->size();
		}

		/// <summary>Checks if attribute_manager can accept this parsing_node.
		/// Returns true iff attribute_manager has been updated</summary>
		bool accept(const rule_node<Language>& nd, attribute_manager<Language>& am) const
		{
			if (is_literal())
				return nd.node_type == nd.LITERAL && nd.word == this->st;

			//todo: Here should be attribute arithmetic
			return am += this->am;
		}
	};

#pragma endregion

	// Creates all the words given dictionary word list and word rules.
	template<typename Language, typename string_t = Language::string_t>
	void populate_words()
	{
		for (auto& w : Language::dictWords)
		{
			using namespace std;

			for (auto p_r = Language::word_rules.crbegin(); p_r != Language::word_rules.crend(); p_r++)
			{
				auto& r = *p_r;
				// Word type matches?
				if (r.wt != w.wordtype)
					continue;

				// Attribute combination already exists?
				if (any_of(w.words.begin(), w.words.end(), [&](const word_form<Language>& wf)
				{	return r.attrs == wf.attrs;	}))
					continue;

				string_t stBase = w.word;
				if (r.is_set())
				{
					// The extra attribute denotes either a word form, or if not,
					// the attribute is required to be present in the dictionary word
					if (w(r.f.get()))
						stBase = w[r.f.get()].word;
					else
						if (w.attrs.count(r.f.get()) == 0)
							continue;
				}

				// Rule matches the source?
				if (!r.source.match(stBase))
					continue;

#ifdef _DEBUG
				r.used = true;
#endif

				// New word form to insert
				string_t word = r.source.match_and_transform(stBase, r.destination);

				w.words.emplace_back(word_form<Language> { word, r.attrs});
			}
			std::for_each(w.words.begin(), w.words.end(), [&](word_form<Language>& dw)
			{
				dw.p_dw = &w;
			});
			w.words.erase(std::remove_if(
				w.words.begin(), w.words.end(),
				[](const auto& w)
			{
				return w.attrs.size() == 1 && Language::is_phony_attribute(*w.attrs.begin());
			}), w.words.end());
		}
	}

	template <typename Language, typename letter = Language::letter, typename string_t = Language::string_t>
	bool parse(typename Language::string_t s)
	{
		// construct a stream from the string
		std::basic_stringstream<typename Language::letter> strstr(s);

		// use stream iterators to copy the stream to the vector as whitespaces separate strings
		std::istream_iterator<string_t, letter> it(strstr);
		std::istream_iterator<string_t, letter> end;
		std::vector<string_t> vs(it, end);

		parsing_triangle<std::vector<parsing_node<Language>>> pt(vs.size());

		// Lexical analysis
		for (unsigned int i = 0; i < vs.size(); i++)
		{
			pt(i, i).emplace_back(parsing_node<Language>(vs[i]));

			getWords<Language>(Language::dictWords,
				[&](const word_form<Language>& w)
			{
				if (w.word == vs[i])
					pt(i,i).emplace_back(parsing_node<Language>(w));
			});
		}

		// Syntax analysis
		for (unsigned int len = 1; len <= vs.size(); len++)
			for (int first = 0; first + len <= vs.size(); first++)
				for (const auto& rule : Language::grammar_rules)
				{
					int end = first + len - 1;
					if (rule.size() > len)
						continue;
					
					switch (rule.size())
					{
					case 1:
						for (const parsing_node<Language>& pn : pt(first, end))
						{
							attribute_manager<Language> am;
							if (pn.accept(rule[0], am))
								pt(first, end).emplace_back(parsing_node<Language>(rule, &pn));
						}
						break;
					case 2:
						for (int second = first + 1; second <= end; second++)
						{
							for (const parsing_node<Language>& pn1 : pt(first, second - 1))
							{
								attribute_manager<Language> am1;
								if (!pn1.accept(rule[0], am1))
									continue;

								for (const parsing_node<Language>& pn2 : pt(second, end))
								{
									attribute_manager<Language> am2 = am1;
									if (!pn2.accept(rule[1], am2))
										continue;

									pt(first, end).emplace_back(parsing_node<Language>(rule, &pn1, &pn2));
								}
							}
						}
						break;
					default:
						ASSERT(false);
						break;
					}
				}

		return pt(0, vs.size() - 1).size() > 0;
	}

	template<typename Language, typename Lambda>
	void getWords(const vector<dictionary_word<Language>>& words, Lambda lambda)
	{
		for (const auto& dw : words)
			for (auto& w : dw.words)
				lambda(w);
	}

	template <class Lang, class letter>
	class Language
	{
	public:
		using string_t = std::basic_string<letter>;

		static const string_t stAlphabet;
		
		static const std::vector<dictionary_word<Lang>> dictWords;

		static const std::vector<word_rule<Lang>> word_rules;

		static const std::vector<rule<Lang>> grammar_rules;

		Language()
		{
#ifdef _DEBUG
			for (auto& rule : word_rules)
				rule.used = false;
#endif
			populate_words<Lang>();
		}

		template <typename Lambda>
		static void traverse_word_forms(Lambda fun)
		{
			for (const auto& w : dictWords)
			{
				for (const auto& word : w.words)
					fun(word);
			}
		}

		static const dictionary_word<Lang>& find_dictionary_word(const string_t& st)
		{
			for (const dictionary_word<Lang>& w : dictWords)
			{
				if (w.word == st)
				{
#ifdef _DEBUG
					// Check that only one such a word exists
					for (auto p_word = dictWords.crbegin(); p_word != dictWords.crend(); p_word++)
					{
						if (p_word->word == st)
						{
							ASSERT(&w == &*p_word);
							break;
						}
					}
#endif
					return w;
				}
			}
			ASSERT_WITH_MSG(false, "No such a word");
		}
	};

	
	template <class Lang, class attr_t = typename Lang::attributes>
	class translator_node
	{
		const dictionary_word<Lang> word;
		const nullable<typename Lang::word_type> wt;
		set<attr_t> attrs;

		void create_attrs()
		{
		}

		template <typename... Args>
		void create_attrs(attr_t attr, Args... args)
		{
			attrs.emplace(attr);
			create_attrs(args...);
		}

	public:
		template <typename... Args>
		translator_node(typename Lang::string_t st, Args... args)
			:  word(Lang::find_dictionary_word(st))
		{
			create_attrs();
		}
	};

	template <class Lang1, class Lang2>
	struct translator
	{
		translator() { }

		static const string stConst;

		using word_type1 = typename Lang1::word_type;
		using word_type2 = typename Lang2::word_type;
		using attributes1 = typename Lang1::attributes;
		using attributes2 = typename Lang2::attributes;
		using categories1 = typename Lang1::attribute_categories;
		using categories2 = typename Lang2::attribute_categories;
		using trans_node1 = typename translator_node<Lang1>;
		using trans_node2 = typename translator_node<Lang2>;

		static const vector<std::pair<word_type1, word_type2>> wordtypes;
		static const vector<std::pair<attributes1, attributes2>> attrs;
		static const vector<std::pair<categories1, categories2>> cats;
		static const vector<std::pair<trans_node1, trans_node2>> translations;

		typename Lang2::string_t translate(const typename Lang1::string_t text)
		{
			wcout << "Trying to translate : " << text << endl;
			return Lang2::string_t();
		}

	private:
		typename Lang2::string_t translate(const vector<const typename Lang1::string_t> text)
		{
		}
	};
}