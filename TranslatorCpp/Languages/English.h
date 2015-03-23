#include "language.h"
#include <unordered_map>

struct English
{
	using letter = char;
	using string_t = std::basic_string < letter >;

	enum class word_type { noun, verb, pronoun, adjective, adverb, article, NP, VP };

	enum class attribute_categories { gender, plurality, person };

	enum class attributes
	{
		present, past, future, continous, perfect,
		per1, per2, per3,
		sing, plur,
		posses, refl, accus
	};

	const std::unordered_map<attributes, attribute_categories> belongs_to_category = std::unordered_map<attributes, attribute_categories>
	{
		{ attributes::per1, attribute_categories::person },
		{ attributes::per2, attribute_categories::person },
		{ attributes::per3, attribute_categories::person },
	};

	const std::vector<translator::dictionary_word<English>> dictWords;

	English()
		: dictWords(
	{
		{ "I", word_type::pronoun, { attributes::per1, attributes::sing },
		{
			{ "me", { attributes::accus } },
			{ "my", { attributes::posses } },
			{ "mine", { attributes::posses, attributes::refl } },
			{ "myself", { attributes::refl } },
		} },
		{ "you", word_type::pronoun, { attributes::per2, attributes::sing },
		{
			{ "you", { attributes::accus } },
			{ "your", { attributes::posses } },
			{ "yours", { attributes::posses } },
			{ "yourself", { attributes::refl } },
		} },
		{ "he", word_type::pronoun, { attributes::per3, attributes::sing } },
		{ "we", word_type::pronoun, { attributes::per1, attributes::plur } },
		{ "you", word_type::pronoun, { attributes::per2, attributes::plur } },
		{ "they", word_type::pronoun, { attributes::per3, attributes::plur } }
	})
	{
		std::vector<translator::word_rule<English>> word_rules
		{
			// Nouns
			{ "%", "%", word_type::noun, { attributes::sing } },
			{ "%", "%s", word_type::noun, { attributes::plur } },
			
			// Verbs
			{ "%",	"%",	word_type::verb, { attributes::sing, attributes::per1 } },
			{ "%",	"%",	word_type::verb, { attributes::sing, attributes::per2 } },
			{ "%",	"%s",	word_type::verb, { attributes::sing, attributes::per3 } },
			{ "%o", "%oes",	word_type::verb, { attributes::sing, attributes::per3 } },	//goes, does
			{ "%", "%",		word_type::verb, { attributes::plur } },
			
			// Pronouns
			{ "%", "%", word_type::noun, { } },
		};

		translator::populate_words(dictWords, word_rules);
	}
	//struct word dictionary_words = { { "Ja", "ja" } };
};