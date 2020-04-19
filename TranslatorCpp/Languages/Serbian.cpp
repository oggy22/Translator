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
	{ { РЕЧН },
	{ { глаг, бр, лиц, повр },{ L"се" } } },
	{ { РЕЧН },
	{ { Одр }, { L"се" }, { глаг, бр, лиц, повр } } },
	{ { РЕЧН },
	{ { Одр }, { глаг, непрел, бр, лиц } } },

	// Recenice
	{ { РЕЧН },
	{ { имен, ном, бр, лиц }, { ГС, бр, лиц } } },
	{ { РЕЧН },
	{ { зам, ном, бр, лиц },{ глаг, непрел, бр, лиц } } },
	{ { РЕЧН },
	{ { имен, ном, бр },{ глаг, непрел, бр, лиц3 } } },
	{ { РЕЧН, бр },
	{ { ИС, ном, бр }, { глаг, непрел, бр, лиц3 } } },

	// Priloske odredbe
	{ { Одр },
	{ { L"без" },{ имен, ген } } },
	{ { Одр },
	{ { L"о" },{ имен, лок } } },
	{ { Одр },
	{ { L"око" },{ имен, ген } } },
	{ { Одр },
	{ { L"са" },{ имен, инстр } } },
	{ { Одр },
	{ { L"у" },{ имен, лок } } },
	{ { Одр },
	{ { L"у" },{ имен, акуз } } },

	// Imenicke singtagme
	{ { ИС, бр, пад, род },
	{ { прид, бр, пад, род }, { имен, бр, пад, род } } },
	{ { РЕЧН },
	{ РЕЧН, Одр } },
	{ { ИС },
	{ { прид, бр, пад }, { имен, бр, пад } } },
	{ { ИС, множ, муш, пад },
	{ { имен, једн, муш, пад }, { L"и" }, { имен, једн, муш, пад } } },
	{ { ИС, множ, жен, пад },
	{ { имен, једн, жен, пад }, { L"и" }, { имен, једн, жен, пад } } },

	// Glagolske singtagme
	{ { ГС, бр, лиц },
	{ { глаг, бр, лиц, прел }, { имен, акуз } } },
	{ { ГС, бр, лиц },
	{ { глаг, бр, лиц, прел }, { ИС, акуз } } },
	{ { ГС, бр, лиц },
	{ { глаг, бр, лиц, мод }, { L"да" }, { ГС, бр, лиц } } },
	{ { ГС, бр, лиц },
	{ { глаг, бр, лиц, мод2 }, { L"да" }, { ГС } } },
	{ { ГС, бр, лиц },
	{ { глаг, бр, лиц, непрел }, { прил } } },
	{ { ГС, бр, лиц },
	{ { прил }, { глаг, бр, лиц, непрел } } }
};

bool SERBIAN_BASE::initialized = false;

Serbian serbian;