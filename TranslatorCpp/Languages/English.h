#include <unordered_map>
#include <sstream>
#include "..\language.h"

struct English
{
	using letter = char;
	using string_t = std::basic_string < letter >;

	static const string_t stAlphabet;

	enum class word_type { noun, verb, pronoun, adjective, adverb, article, NP, VP, Sentence };
#define noun	word_type::noun
#define verb	word_type::verb
#define pron	word_type::pronoun
#define adj		word_type::adjective
#define adv		word_type::adverb
#define art		word_type::article
#define NP		word_type::NP
#define VP		word_type::VP
#define Sent	word_type::Sentence

	enum class attribute_categories { gender, plurality, person };

	enum class attributes
	{
		present, past, future, continous, perfect,
		per1, per2, per3,
		sing, plur,
		posses, refl, accus
	};

#define past attributes::past
#define perf attributes::perfect
#define per1 attributes::per1
#define per2 attributes::per2
#define per3 attributes::per3
#define sing attributes::sing
#define plur attributes::plur

	const std::set<attributes> phony_attrs{ };

	static const std::unordered_map<attributes, attribute_categories> belongs_to_category;

	static bool is_phony_attribute(attributes a)
	{
		return false;
	}

	static const std::vector<translator::dictionary_word<English>> dictWords;

	static const std::vector<translator::word_rule<English>> word_rules;

	static const std::vector<translator::rule<English>> grammar_rules;

	English()
	{
#ifdef _DEBUG
		for (auto& rule : word_rules)
			rule.used = false;
#endif
		translator::populate_words<English>();
	}

	template <typename Lambda>
	static void traverse_words(Lambda fun)
	{
		for (const auto& w : dictWords)
		{
			for (const auto& word : w.words)
				fun(word);
		}
	}
};