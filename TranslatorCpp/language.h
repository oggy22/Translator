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

			for (auto p_r = Language::word_rules.crbegin(); p_r != Language::word_rules.crend(); p_r++)
			{
				auto& r = *p_r;
				// Word type matches?
				if (r.wt != w.wordtype)
					continue;

				// Attribute combination exists already?
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

			getWords<Language>(Language::dictWords(),
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
		static std::vector<dictionary_word<Lang>> _dictWords;

	public:
		using string_t = std::basic_string<letter>;

		static const std::vector<word_rule<Lang>> word_rules;

		static const string_t stAlphabet;
		
		static const std::vector<dictionary_word<Lang>>& dictWords()
		{
			return _dictWords;
		}

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
				map<Lang::word_type, const word_to_word_rule<Lang>*> applicable_rules;

				for (auto& rule : Lang::word_to_word_rules)
				{
					if (rule.wt_source == w.wordtype && rule.source.match(w.word))
					{
						applicable_rules[rule.wt_destination] = &rule;
					}
				}

				for (auto& pair : applicable_rules)
				{
					const auto& rule = *pair.second;
					string_t word = rule.source.match_and_transform(w.word, rule.destination);
#ifdef _DEBUG
					rule.used = true;
#endif
					if (word.empty())
						continue;

					derived_words.emplace_back(dictionary_word<Lang>
					{
						word,
							rule.wt_destination,
							rule.attrs
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
#ifdef _DEBUG
			for (auto& rule : word_to_word_rules)
				ASSERT(rule.used);
#endif

			check_for_duplicates();
		}
	};
}