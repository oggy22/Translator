#include "English.h"


const std::unordered_map<English::attributes, English::attribute_categories> English::belongs_to_category
{
	{ per1, attribute_categories::person },
	{ per2, attribute_categories::person },
	{ per3, attribute_categories::person },
};

const English::string_t English::stAlphabet("abcdefghijklmnopqrstuvwxyz");

const std::vector<translator::dictionary_word<English>> English::dictWords
{
	{ "i", pron,{ sing, per1 },
	{
		{ "me",{ attributes::accus } },
		{ "my",{ attributes::posses } },
		{ "mine",{ attributes::posses, attributes::refl } },
		{ "myself",{ attributes::refl } },
	} },
	{ "you", pron,{ sing, per2 },
	{
		{ "you",{ attributes::accus } },
		{ "your",{ attributes::posses } },
		{ "yours",{ attributes::posses } },
		{ "yourself",{ attributes::refl } },
	} },
	{ "he", pron,{ sing, per3 } },
	{ "we", pron,{ plur, per1 } },
	{ "you", pron,{ plur, per2 } },
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
		{ "could",{ perf } } }
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
	{ "woman", noun,{},{ { "women",{ plur } } } },
};

const std::vector<translator::rule<English>> English::grammar_rules
{
	{
		{ Sent },
		{ word_type::pronoun },{ verb }
	}
};

const std::vector<translator::word_rule<English>> English::word_rules
{
	// Nouns
	{ { "*" },{ "*" }, noun,{ sing } },
	{ { "*" },{ "*s" }, noun,{ plur } },
	{ { "*y" },{ "*ies" }, noun,{ plur } },
	{ { "*o" },{ "*oes" }, noun,{ plur } },
	{ { "*s" },{ "*ses" }, noun,{ plur } },
	{ { "*sis" },{ "*ses" }, noun,{ plur } },	// basis, crisis, diagnosis
	{ { "*man" },{ "*men" }, noun,{ plur } },	// man, woman, policeman

												//// Verbs
	{ { "*" },{ "*" }, verb,{ sing, per1 } },
	{ { "*" },{ "*" }, verb,{ sing, per2 } },
	{ { "*" },{ "*s" }, verb,{ sing, per3 } },
	{ { "*o" },{ "*oes" }, verb,{ sing, per3 } },	//goes, does

	{ { "*" },{ "*" }, verb,{ plur } },

	{ { "*e" },{ "*ed" }, verb,{ past } },
	{ { "*" },{ "*ed" }, verb,{ past } },
	{ { "*e" },{ "*ed" }, verb,{ perf } },
	{ { "*" },{ "*ed" }, verb,{ perf } },

	//// Pronouns
	{ { "*" },{ "*" }, pron,{} },
};

English english;