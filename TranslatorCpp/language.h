#pragma once

#include "stdafx.h"
#include "attribute_manager.h"
#include "pattern.h"
#include "Words.h"
#include "Rules.h"

namespace translator
{
	using namespace std;

	// Creates all the words given dictionary word list and word rules.
	template<typename Language, typename string_t = Language::string_t>
	void populate_words()
	{
		for (auto& w : Language::dictWords())
		{
			using namespace std;

			// Traverse the rules backwards, so the most specific rules are encountered first
			for (auto p_r = Language::word_rules.crbegin(); p_r != Language::word_rules.crend(); p_r++)
			{
				auto& rule = *p_r;
				// Word type matches?
				if (rule.wt != w.wordtype)
					continue;

				if (any_of(
					rule.req_attrs.begin(),
					rule.req_attrs.end(),
					[&](const auto& attr) { return w.attrs.find(attr) == w.attrs.end(); }))
					continue;

				//Language::attributes a;
				//if (w.attrs.find(a) == w.attrs.end()) { }

				// Attribute combination exists already?
				if (any_of(w.words.begin(), w.words.end(), [&](const word_form<Language>& wf)
				{	return rule.attrs == wf.attrs;	}))
					continue;

				string_t stBase = w.word;
				if (rule.is_set())
				{
					// The extra attribute denotes either a word form, or if not,
					// the attribute is required to be present in the dictionary word
					if (w(rule.f.get()))
						stBase = w[rule.f.get()].word;
					else
						if (w.attrs.count(rule.f.get()) == 0)
							continue;
				}

				// Rule matches the source?
				if (!rule.source.match(stBase))
					continue;

#ifdef _DEBUG
				rule.used = true;
#endif

				// New word form to insert
				string_t word = rule.source.match_and_transform(stBase, rule.destination);

				w.words.emplace_back(word_form<Language> { word, rule.attrs});
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

	void to_lower(basic_string<char>& s);

	void to_lower(basic_string<wchar_t>& s);


	// Returns:
	// 1.0 if fully parsed
	// 0.0 if nothing longer than a word was parsed
	// 0 < parse < 1 partially parsed
	template <typename Language, typename letter = Language::letter, typename string_t = Language::string_t>
	float parse(typename Language::string_t s)
	{
		// construct a stream from the string
		std::basic_stringstream<typename Language::letter> strstr(s);

		// use stream iterators to copy the stream to the vector as whitespaces separate strings
		std::istream_iterator<string_t, letter> it(strstr);
		std::istream_iterator<string_t, letter> end;
		std::vector<string_t> vs(it, end);

		parsing_triangle<std::vector<parsing_node<Language>>> pt(vs.size());

		// Lowercase all the words
		for (auto &word : vs)
			to_lower(word);

		// Lexical analysis
		for (unsigned int i = 0; i < vs.size(); i++)
		{
			pt(i, i).emplace_back(parsing_node<Language>(vs[i]));

			for (auto p : Language::list_word_forms(vs[i]))
			{
				pt(i, i).emplace_back(parsing_node<Language>(*p));
			}
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
					case 3:
						for (int second = first + 1; second <= end; second++)
						{
							for (const parsing_node<Language>& pn1 : pt(first, second - 1))
							{
								attribute_manager<Language> am1;
								if (!pn1.accept(rule[0], am1))
									continue;
								for (int third = second + 1; third <= end; third++)
								{
									for (const parsing_node<Language>& pn2 : pt(second, third-1))
									{
										attribute_manager<Language> am2 = am1;
										if (!pn2.accept(rule[1], am2))
											continue;

										for (const parsing_node<Language>& pn3 : pt(third, end))
										{
											attribute_manager<Language> am3 = am2;
											if (!pn3.accept(rule[2], am3))
												continue;

											pt(first, end).emplace_back(parsing_node<Language>(rule, &pn1, &pn2, &pn3));
										}
									}
								}
							}
						}
						break;
					default:
						ASSERT(false);
						break;
					}
				}
#ifdef TEST
		test_output << "**********************************" << std::endl;
		test_output << "Parsing: '" << s << "'" << std::endl;
		pt.to_ostream(test_output, vs);
		test_output << "Root: " << pt(0, vs.size() - 1).size() << std::endl;
#endif
		if (vs.size() == 1)
			return 0.0f;

		for (size_t offset = vs.size() - 1; ; offset--)
		{
			for (size_t i = 0; i + offset < vs.size(); i++)
			{
				if (pt(i, i + offset).size() > 0)
					return float(offset) / (vs.size() - 1);
			}
		}

		FAIL("vs diagonal should have elements");
	}

	template<typename Language, typename Lambda>
	void getWords(const vector<dictionary_word<Language>>& words, Lambda lambda)
	{
		for (const auto& dw : words)
			for (auto& w : dw.words)
				lambda(w);
	}

	template <typename Language, typename char_t = typename Language::letter>
	class trie_node_words
	{
		using string_t = typename std::basic_string<char_t>;
		using char_tt = typename Language::letter;
		map<char_t, trie_node_words*> children;

		void add(const word_form<Language>& w, size_t pos)
		{
			ASSERT(pos <= w.word.length());
			if (pos == w.word.length())
				words_p.emplace_back(&w);
			else
			{
				char_t c = w.word[pos];
				if (children[c] == nullptr)
				{
					children[c] = new trie_node_words();
				}
				children[c]->add(w, pos + 1);
			}
		}

		trie_node_words* find(const string_t& s, size_t pos)
		{
			ASSERT(pos <= s.length());
			if (pos == s.length())
				return this;
			else
			{
				auto ptr = children[s[pos]];

				if (ptr == nullptr)
					return nullptr;

				return ptr->find(s, pos + 1);
			}
		}

	public:
		std::vector<const word_form<Language>*> words_p;

		void add(const word_form<Language>& w)
		{
			add(w, 0);
		}

		trie_node_words* find(const string_t& s)
		{
			return find(s, 0);
		}
	};

	template <typename Language, typename char_t = typename Language::letter>
	void words_root_init(trie_node_words<char_t>& root)
	{
		getWords<Language>(Language::dictWords(),
			[&](const word_form<Language>& w)
			{
				root.add(w);
			});
	}

	template <class Lang, class letter>
	class Language
	{
		static trie_node_words<Lang, letter> _root;
		static std::vector<dictionary_word<Lang>> _dictWords;

	public:
		using string_t = std::basic_string<letter>;

		static const map<letter, string_t> jokers;

		static const std::vector<word_rule<Lang>> word_rules;

		static const string_t stAlphabet;
		
		static const std::vector<dictionary_word<Lang>>& dictWords()
		{
			return _dictWords;
		}

		static std::experimental::generator<string_t> wordForms()
		{
			for (const auto& word : _dictWords)
				for (const auto& form : word.words)
					co_yield form.word;

			for (int i = 1; i < 1000; i++)
				co_yield number(i);
		}

		static string_t number(int n);

		static const std::vector<word_to_word_rule<Lang>> word_to_word_rules;

		static const std::vector<rule<Lang>> grammar_rules;

		static void check_for_duplicates()
		{
			for (unsigned i = 0; i<dictWords().size(); i++)
				for (unsigned j = i + 1; j < dictWords().size(); j++)
					if (Lang::is_duplicate(dictWords()[i], dictWords()[j]))
						FAIL("word already in");
		}

		// Creates all the words given dictionary word list and word-to-word rules.
		static void populate_derived_dict_words()
		{
			using string_t = Language::string_t;
			using dw_t = typename dictionary_word<Language>;
			std::vector<dictionary_word<Lang>> derived_words;

			for (auto& w : Lang::dictWords())
			{
				// All the applicable rules for the given word, mapped by derived word type
				myset<const word_to_word_rule<Lang>*> applicable_rules;

				for (auto& rule : Lang::word_to_word_rules)
				{
					if (rule.wt_source == w.wordtype && rule.source.match(w.word))
					{
						// Find the rule with the same destination and attributes added
						auto p_rule = std::find_if(applicable_rules.begin(), applicable_rules.end(),
							[&](const word_to_word_rule<Lang>* p)
						{
							return p->attrs_added == rule.attrs_added &&
								p->wt_destination == rule.wt_destination;
						});

						// Remove if found
						if (p_rule != applicable_rules.end())
							applicable_rules.erase(p_rule);

						// Word contains required attributes?
						if (!std::includes(
							w.attrs.begin(), w.attrs.end(),
							rule.req_attrs.cbegin(), rule.req_attrs.cend()
							))
							continue;

						applicable_rules.insert(&rule);
					}
				}

				for (auto& rule : applicable_rules)
				{
					string_t word = rule->source.match_and_transform(w.word, rule->destination);
#ifdef _DEBUG
					rule->used = true;
#endif
					if (word.empty())
						continue;

					derived_words.emplace_back(dictionary_word<Lang>
					{
						word,
							rule->wt_destination,
							rule->attrs_added
					});
				}
			}

			for (auto& w : derived_words)
				_dictWords.push_back(w);
		}

		template <typename Lambda>
		static void traverse_word_forms(Lambda fun)
		{
			for (const auto& w : _dictWords)
			{
				for (const auto& word : w.words)
					fun(word);
			}
		}

		static bool joker_can_replace(letter joker, letter c)
		{
			auto p = jokers.find(joker);
			if (p == jokers.end())
				return false;

			string_t st = p->second;

			if (st.find(c) == string_t::npos)
				return false;

			return true;
		}

		static bool is_joker(letter c)
		{
			return jokers.find(c) != jokers.end();
		}

		static std::experimental::generator<const word_form<Lang>*> list_word_forms(const string_t& str)
		{
			auto p_node = _root.find(str);
			if (p_node == nullptr)
				co_return;

			for (const word_form<Lang>* p : p_node->words_p)
			{
				co_yield p;
			}
		}

		static const dictionary_word<Lang>& find_dictionary_word(const string_t& st)
		{
			for (const dictionary_word<Lang>& w : _dictWords)
			{
				if (w.word == st)
				{
#ifdef _DEBUG
					// Check that only one such a word exists
					for (auto p_word = _dictWords.crbegin(); p_word != _dictWords.crend(); p_word++)
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

protected:
		Language()
		{
			Initialize();
		}

private:
		static bool initialized;

		static void Initialize()
		{
			ASSERT(!initialized);

#ifdef _DEBUG
			for (auto& rule : word_rules)
				rule.used = false;
			for (auto& rule : word_to_word_rules)
				rule.used = false;
#endif
			populate_derived_dict_words();
			populate_words<Lang>();
			initialized = true;

			check_for_duplicates();
			words_root_init<Lang>(_root);
		}
	};
}
