#include <unordered_map>
#include <sstream>
#include "..\language.h"

struct English
{
	using letter = char;
	using string_t = std::basic_string < letter >;

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

	const std::unordered_map<attributes, attribute_categories> belongs_to_category = std::unordered_map<attributes, attribute_categories>
	{
		{ per1, attribute_categories::person },
		{ per2, attribute_categories::person },
		{ per3, attribute_categories::person },
	};
	
	static bool is_phony_attribute(attributes a)
	{
		return false;
	}

	const std::vector<translator::word_rule<English>> wordRules;

	const std::vector<translator::dictionary_word<English>> dictWords;

	const std::vector<translator::rule_node<English>> nodes;

	const std::vector<translator::rule<English>> rules;

	English()
		:
	wordRules(
	{
		// Nouns
		{ { "%" },{ "%" }, noun, { sing } },
		{ { "%" },{ "%s" }, noun, { plur } },

		//// Verbs
		{ { "%" },{ "%" }, verb,{ sing, per1 } },
		{ { "%" },{ "%" }, verb,{ sing, per2 } },
		{ { "%o" },{ "%oes" }, verb,{ sing, per3 } },	//goes, does
		{ { "%" },{ "%s" }, verb,{ sing, per3 } },
		{ { "%" },{ "%" }, verb,{ plur } },
		
		{ { "%e" },{ "%ed" }, verb,{ past } },
		{ { "%" },{ "%ed" }, verb,{ past } },
		{ { "%e" },{ "%ed" }, verb,{ perf } },
		{ { "%" },{ "%ed" }, verb,{ perf } },

		//// Pronouns
		{ { "%" },{ "%" }, pron,{} },
	}),
	dictWords(
	{
		{ "I", pron, { sing, per1 },
		{
			{ "me", { attributes::accus } },
			{ "my", { attributes::posses } },
			{ "mine", { attributes::posses, attributes::refl } },
			{ "myself", { attributes::refl } },
		} },
		{ "you", pron, { sing, per2 },
		{
			{ "you", { attributes::accus } },
			{ "your", { attributes::posses } },
			{ "yours", { attributes::posses } },
			{ "yourself", { attributes::refl } },
		} },
		{ "he", pron, { sing, per3 } },
		{ "we", pron, { plur, per1 } },
		{ "you", pron, { plur, per2 } },
		{ "they", pron,{ plur, per3 } },
			
		//Verbs:
		{ "be", verb,{},
		{
			{ "am",{ sing, per1 } },
			{ "are",{ sing, per2 } },
			{ "is",{ sing, per3 } },
			{ "are",{ plur } },
			{ "was",{ past, sing, per1 } },
			{ "were",{ past, sing, per2 } },
			{ "was",{ past, sing, per3 } },
			{ "were",{ past, plur } },
			{ "been",{ perf } } }
		},
		{ "can", verb,{},
		{
			{ "can",{ sing, per3 } },
			{ "could",{ past } },
			{ "could", { perf } } }
		},
		{ "do", verb,{},{ { "did",{ past } },{ "done",{ perf } } } },
		{ "go", verb,{},{ { "went",{ past } },{ "gone",{ perf } } } },
		{ "have", verb,{},
		{
			{ "has",{ sing, per3 } },
			{ "had",{ past } },
			{ "had",{ perf } }
		} },
		{ "hear", verb,{},{ { "heard",{ past } },{ "heard",{ perf } } } },
		{ "say", verb,{},{ { "said",{ past } },{ "said",{ perf } } } },
		{ "see", verb,{},{ { "saw",{ past } },{ "seen",{ perf } } } },
		{ "talk", verb },
		{ "walk", verb },
		{ "want", verb },

		//Nouns
		{ "house", noun },
		{ "wife", noun },
		{ "woman", noun, {}, {{"women",{plur}} }},
	}),
	rules(
			{
				{
					{ Sent},
					{ word_type::pronoun }, {verb}
				}
			}
	)
	{


		translator::populate_words(dictWords, wordRules);
	}

	void parse(string_t s)
	{
		// construct a stream from the string
		std::basic_stringstream<letter> strstr(s);

		// use stream iterators to copy the stream to the vector as whitespace separated strings
		std::istream_iterator<string_t> it(strstr);
		std::istream_iterator<string_t> end;
		std::vector<string_t> results(it, end);
	}

	template <typename Lambda>
	void traverse_words(Lambda fun) const
	{
		for (const auto& w : dictWords)
		{
			for (const auto& word : w.words)
				fun(word);
		}
	}
};