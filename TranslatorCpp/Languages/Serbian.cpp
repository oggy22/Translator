#include "Serbian.h"

const Serbian::string_t SERBIAN_BASE::stAlphabet(L"абвгдђежзијклљмнњопрстћуфхцчџш");

using attrs = Serbian::attributes;
using cats = Serbian::attribute_categories;

const std::unordered_map<attrs, cats> Serbian::belongs_to_category
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

const std::vector<translator::dictionary_word<Serbian>> SERBIAN_BASE::dictWords
{
#include "Serbian_words.h"
};

const std::vector<translator::word_rule<Serbian>> SERBIAN_BASE::word_rules
{
#include "Serbian_word_rules.h"
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
	{ { РЕЧН },
	{ РЕЧН, Одр } },
	{ { ИС },
	{ { прид, бр, пад },{ имен, бр, пад } } }
};

Serbian serbian;