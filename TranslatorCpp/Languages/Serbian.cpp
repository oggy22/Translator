﻿#include "stdafx.h"
#include "Serbian.h"

const Serbian::string_t SERBIAN_BASE::stAlphabet(L"абвгдђежзијклљмнњопрстћуфхцчџш");

using attrs = Serbian::attributes;
using cats = Serbian::attribute_categories;

const map<attrs, cats> Serbian::belongs_to_category
{
	// Падежи
	{ ном, пад },
	{ ген, пад },
	{ дат, пад },
	{ акуз, пад },
	{ вок, пад },
	{ инстр, пад },
	{ лок, пад },

	// Лица
	{ лиц1, лиц },
	{ лиц2, лиц },
	{ лиц3, лиц },

	// Број
	{ једн, бр },
	{ множ, бр },
};

std::vector<translator::dictionary_word<Serbian>> SERBIAN_BASE::_dictWords
{
#include "Serbian_words.h"
};

const std::vector<translator::word_rule<Serbian>> SERBIAN_BASE::word_rules
{
#include "Serbian_word_rules.h"
};

const std::vector<translator::word_to_word_rule<Serbian>> SERBIAN_BASE::word_to_word_rules
{
	// Именице:

	{ L"*ац",	L"*чић",	имен, имен,{ жен }, { дем } }, //деминутив - мушкарац 
	{ L"*а",	L"*ица",	имен, имен,{ жен }, { дем } }, //деминутив - жена
	
	{ L"*а",	L"*етина",	имен, имен,	{ жен },{ ауг } }, //аугментатив - женетина
												  
	// Глаголи:
	{ L"*ти",	L"*ње",		глаг, имен,{ сред } },
	{ L"бити",	L"",		глаг, имен,{ сред } },
	{ L"*лети",	L"*љење",	глаг, имен,{ сред } },
	{ L"видети",L"виђање",	глаг, имен,{ сред } },
	{ L"јести",	L"једење",	глаг, имен,{ сред } },

	{ L"*ати",	L"*ајући",	глаг, прил },	//гледати, дати
	
	{ L"*",		L"*о",		прид, прил },	//брзо, лепо
	{ L"*ан",	L"*но",		прид, прил },	//брзо, лепо

	// Заменице:
	{ L"ја",	L"мој",		зам, прид },
	{ L"ти",	L"твој",	зам, прид },
	{ L"он",	L"његов",	зам, прид },
	{ L"она",	L"њен",		зам, прид },
	{ L"оно",	L"његов",	зам, прид },
	{ L"ми",	L"наш",		зам, прид },
	{ L"ви",	L"ваш",	зам, прид },
	{ L"они",	L"њихов",	зам, прид },
	{ L"оне",	L"њихов",	зам, прид },
	//{ L"она",	L"њихов",	зам, прид },	//Shadows "ona"

	// Присвојни придеви:
	{ L"*",		L"*ов",	имен, прид },	//Миланов, Ненадов, монахов
	{ L"коњ",	L"коњев",	имен, прид },	//Миланов, Ненадов, монахов
	{ L"*а",	L"*ин",	имен, прид },		//женин

	// Придев од именице:
	//{ L"*а",	L"*ски",	имен, прид },	//жена, свиња : TODO: shadowed by *a -> *in
	{ L"*еме",	L"*еменски",имен, прид },	//време, племе
};

const std::vector<translator::rule<Serbian>> SERBIAN_BASE::grammar_rules
{
	{ { РЕЧН },
	{ { зам, бр, лиц },{ глаг, бр, лиц } } },
	{ { РЕЧН },
	{ { имен, бр, лиц3 },{ глаг, бр, лиц } } },
	{ { Одр },
	{ { L"у" },{ имен, лок } } },
	{ { Одр },
	{ { L"у" },{ имен, акуз } } },
	{ { ИС, бр, пад, род },
	{ { прид, бр, пад, род }, { имен, бр, пад, род } } },
	{ { РЕЧН },
	{ РЕЧН, Одр } },
	{ { ИС },
	{ { прид, бр, пад },{ имен, бр, пад } } },
	{ { ГС },
	{ { глаг, прел }, { имен, акуз } } }
};

bool SERBIAN_BASE::initialized = false;

Serbian serbian;