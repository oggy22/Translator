#include "stdafx.h"

#include "translator.h"
#include "Languages\English.h"
#include "Languages\Serbian.h"

using namespace std;
using EngSrb = translator::translator<English, Serbian>;

const string translator::translator<English, Serbian>::stConst;

static const vector<std::pair<EngSrb::word_type1, EngSrb::word_type2>> wordtypes
{
	{ noun, имен },
	{ verb, глаг },
	{ pron, зам },
	{ adj, прид },
	{ adv, прил },
};

static const vector<std::pair<translator::translator_node<English>, translator::translator_node<Serbian>>> translations
{
	// Verbs:
	{ {"hear"}, {L"чути"} },
	//{ {"move"}, {L"кућа"} },
	{ {"say"}, {L"казати"} },
	{ {"see"}, {L"видети"} },
	{ {"talk"}, {L"говорити"} },
	{ {"walk"}, {L"шетати"} },
	{ {"want"}, {L"желети"} },
	{ {"want"}, {L"хтети"} },

	// Nouns:
	{ {"house"}, {L"кућа"} },
	{ {"man"}, {L"човек"} },
	{ {"policeman"}, {L"полицајац"} },
	{ {"potato"}, {L"кромпир"} },
	{ {"wife"}, {L"жена"} },
	{ {"woman"}, {L"жена"} },
};