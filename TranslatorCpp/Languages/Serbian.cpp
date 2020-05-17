#include "stdafx.h"
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

	// Род
	{ муш, род },
	{ жен, род },
	{ сред, род },
};

translator::trie_node_words<Serbian, wchar_t> SERBIAN_BASE::_root;
std::vector<translator::dictionary_word<Serbian>> SERBIAN_BASE::_dictWords
{
#include "Serbian_words.h"
};

std::wstring _number10(int n)
{
	switch (n)
	{
	case 0: return L"";
	case 1: return L"један";
	case 2: return L"два";
	case 3: return L"три";
	case 4: return L"четири";
	case 5: return L"пет";
	case 6: return L"шест";
	case 7: return L"седам";
	case 8: return L"осам";
	case 9: return L"девет";
	case 10: return L"десет";
	default:
		ASSERT(false);
	}
}

std::wstring _number20(int n)
{
	if (n <= 10)
		return _number10(n);
	switch (n)
	{
	case 11: return L"једанаест";
	case 14: return L"четрнаест";
	}

	return _number10(n - 10) + L"наест";	
}

std::wstring _number100(int n)
{
	if (n < 20) return _number20(n);
	std::wstring st10;
	switch (n / 10)
	{
	case 9: st10 = L"деведесет"; break;
	default: st10 = _number10(n / 10) + L"десет";
	}

	return st10 + (n%10 == 0 ? L"" : L" " + _number10(n % 10));
}

std::wstring _number1000(int n)
{
	if (n < 100)
		return _number100(n);
	
	if (n == 100)
		return L"сто";
	
	if (n < 200)
		return L"сто " + _number100(n - 100);

	int n100 = n / 100;
	return _number10(n100) + (n100 < 4 ? L"ста " : L"сто ") + _number100(n % 100);
}

std::wstring SERBIAN_BASE::number(int n)
{
	if (n == 0)
		return L"нула";

	return _number1000(n);
}

const std::vector<translator::word_rule<Serbian>> SERBIAN_BASE::word_rules
{
#include "Serbian_word_rules.h"
};

const std::vector<translator::word_to_word_rule<Serbian>> SERBIAN_BASE::word_to_word_rules
{
#include "Serbian_word_to_word_rules.h"
};

const std::vector<translator::rule<Serbian>> SERBIAN_BASE::grammar_rules
{
#include "Serbian_grammar.h"
};

bool SERBIAN_BASE::initialized = false;

Serbian serbian;