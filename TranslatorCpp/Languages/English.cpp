#include "stdafx.h"
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

const map<char, English::string_t> ENGLISH_BASE::jokers
{
	{'#', "bcd"},
	{'@', "aeiouy"}
};

translator::trie_node_words<English, char> ENGLISH_BASE::_root;
std::vector<translator::dictionary_word<English>> ENGLISH_BASE::_dictWords
{
#pragma region Determiners
	{ "the", det },
	{ "a", det, {sing} },
	{ "this", det,{ sing } },
	{ "that", det,{ sing } },
	{ "these", det,{ plur } },
	{ "those", det,{ plur } },

	{ "my", det },
	{ "your", det },
	{ "his", det },
	{ "her", det },
	{ "its", det },
	{ "our", det },
	{ "their", det },

	{ "all", det, {plur} },
	{ "both", det, {plur} },
	{ "either", det },
	{ "neither", det },
	{ "each", det, {plur} },
	{ "every", det, {plur} },
#pragma endregion 

#pragma region Others
	{ "and", othr },
	{ "as", othr },
	{ "at", othr },
	{ "but", othr },
	{ "by", othr },
	{ "for", othr },
	{ "from", othr },
	{ "in", othr },
	{ "not", othr },
	{ "or", othr },
	{ "to", othr },
	{ "what", othr },
	{ "with", othr },
#pragma endregion

#pragma region Pronouns
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
#pragma endregion

#pragma region Verbs
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
	{ "will", verb },
#pragma endregion

#pragma region Nouns
	{ "body", noun },
	{ "bus", noun },
	{ "crisis", noun },
	{ "day", noun },
	{ "hand", noun },
	{ "house", noun },
	{ "life", noun },
	{ "man", noun },
	{ "person", noun },
	{ "policeman", noun },
	{ "potato", noun },
	{ "thing", noun },
	{ "time", noun },
	{ "wife", noun },
	{ "way", noun },
	{ "woman", noun },
	{ "world", noun },
	{ "year", noun },
#pragma endregion

#pragma region Adjectives
	{ "slow", adj },
	{ "quick", adj },
#pragma endregion

#pragma region Numbers
	{ "one", numb },
	{ "two", numb },
	{ "three", numb },
	{ "four", numb },
	{ "five", numb },
	{ "six", numb },
	{ "seven", numb },
	{ "eight", numb },
	{ "nine", numb },
	{ "ten", numb },
#pragma endregion
};

const std::vector<translator::word_rule<English>> ENGLISH_BASE::word_rules
{
	// Determiners
	{ { "*"}, {"*"}, det },

	// Nouns
	{ { "*" },{ "*" }, noun, { }, { sing } },
	{ { "*" },{ "*s" }, noun, { }, { plur } },
	{ { "*y" },{ "*ies" }, noun, { }, { plur } },
	{ { "*o" },{ "*oes" }, noun, { }, { plur } },
	{ { "*s" },{ "*ses" }, noun, { }, { plur } },
	{ { "*sis" },{ "*ses" }, noun, { }, { plur } },	// basis, crisis, diagnosis
	{ { "*man" },{ "*men" }, noun, { }, { plur } },	// man, woman, policeman

	//// Verbs
	{ { "*" },{ "*" }, verb, { }, { pres, sing, per1 } },
	{ { "*" },{ "*" }, verb, { }, { pres, sing, per2 } },
	{ { "*" },{ "*s" }, verb, { }, { pres, sing, per3 } },
	{ { "*o" },{ "*oes" }, verb, { }, { pres, sing, per3 } },	//goes, does

	{ { "*" },{ "*" }, verb, { }, { plur } },

	{ { "*" }, { "*ed" }, verb, { }, { past } },
	{ { "*e" },{ "*ed" }, verb, { }, { past } },
	{ { "*" }, { "*ed" }, verb, { }, { perf } },
	{ { "*e" },{ "*ed" }, verb, { }, { perf } },

	//// Pronouns
	{ { "*" },{ "*" }, pron, { }, { nom } },
};

std::string _number10(int n)
{
	if (n == 0)
		return "";

	ASSERT(n < 10);
	switch (n)
	{
	case 1: return "one";
	case 2: return "two";
	case 3: return "three";
	case 4: return "four";
	case 5: return "five";
	case 6: return "six";
	case 7: return "seven";
	case 8: return "eight";
	case 9: return "nine";
	case 10: return "ten";
	default:
		ASSERT(false);
	}
}

std::string _number20(int n)
{
	ASSERT(n < 20);
	if (n < 10)
		return _number10(n);

	if (n >= 16)
		return _number10(n - 10) + "teen";

	switch (n)
	{
	case 10: return "ten";
	case 11: return "eleven";
	case 12: return "twelve";
	case 13: return "thirteen";
	case 14: return "fourteen";
	case 15: return "fifteen";
	default:
		ASSERT(false);
	}
}

std::string _number100(int n)
{
	if (n < 20) return _number20(n);
	
	int n1 = n % 10;
	int n10 = n / 10;

	std::string ty;
	switch (n10)
	{
	case 2: ty = "twenty"; break;
	case 3: ty = "thirty"; break;
	case 4: ty = "forty"; break;
	case 5: ty = "fifty"; break;
	case 8: ty = "eighty"; break;
	default:
		ty = _number10(n / 10) + "ty";
	}
	if (n1 == 0)
		return ty;

	return ty + "-" + _number10(n % 10);
}

std::string _number1000(int n)
{
	if (n < 100) return _number100(n);

	return _number10(n / 100) + " hundred" + (n%100==0 ? "" : " and " + _number100(n % 100));
}

std::string ENGLISH_BASE::number(int n)
{
	if (n == 0)
		return "zero";

	return _number1000(n);
}

std::string ordinal_number(int n)
{
	//"*one" -> "*first";
	return _number100(n);
}

const std::vector<translator::word_to_word_rule<English>> ENGLISH_BASE::word_to_word_rules
{
	{"*", "*ly", adj, adv, {} },
	{"*", "*able", verb, adj, {} },
};

const std::vector<translator::rule<English>> ENGLISH_BASE::grammar_rules
{
	{ { Sent },
	{ { pron, sing, nom, per }, { verb, sing, per, pres } } },
};

bool ENGLISH_BASE::initialized = false;

English english;