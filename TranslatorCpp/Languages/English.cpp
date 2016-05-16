#include "English.h"

const map<English::attributes, English::attribute_categories> English::belongs_to_category
{
	{ per1, attribute_categories::person },
	{ per2, attribute_categories::person },
	{ per3, attribute_categories::person },
	{ sing, attribute_categories::plurality },
	{ plur, attribute_categories::plurality },
};

const English::string_t ENGLISH_BASE::stAlphabet("abcdefghijklmnopqrstuvwxyz");

const std::vector<translator::dictionary_word<English>> ENGLISH_BASE::dictWords
{
	{ "i", pron,{ sing, per1 },
	{
		{ "me",{ accus } },
		{ "my",{ posses } },
		{ "mine",{ posses, refl } },
		{ "myself",{ refl } },
	} },
	{ "you", pron,{ sing, per2 },
	{
		{ "you",{ accus } },
		{ "your",{ posses } },
		{ "yours",{ posses } },
		{ "yourself",{ refl } },
	} },
	{ "he", pron,{ sing, per3 } },
	{ "she", pron,{ sing, per3 } },
	{ "it", pron,{ sing, per3 } },
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
	{ "move", verb },
	{ "say", verb,{},{ { "said",{ past } },{ "said",{ perf } } } },
	{ "see", verb,{},{ { "saw",{ past } },{ "seen",{ perf } } } },
	{ "speak", verb,{},{ { "spoke",{ past } },{ "spoken",{ perf } } } },
	{ "talk", verb },
	{ "walk", verb },
	{ "want", verb },

	//Nouns
	{ "body", noun },
	{ "bus", noun },
	{ "crisis", noun },
	{ "house", noun },
	{ "man", noun },
	{ "policeman", noun },
	{ "potato", noun },
	{ "wife", noun },
	{ "woman", noun },
};

const std::vector<translator::word_rule<English>> ENGLISH_BASE::word_rules
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

	{ { "*" },{ "*ed" }, verb,{ past } },
	{ { "*e" },{ "*ed" }, verb,{ past } },
	{ { "*" },{ "*ed" }, verb,{ perf } },
	{ { "*e" },{ "*ed" }, verb,{ perf } },

	//// Pronouns
	{ { "*" },{ "*" }, pron,{} },
};

const std::vector<translator::rule<English>> ENGLISH_BASE::grammar_rules
{
	{ { Sent },
	{ { pron, sing, per },{ verb, sing, per } } },
};

English english;