#include "Languages\Serbian.h"

const Serbian::string_t Serbian::stAlphabet(L"абвгдђежзијклљмнњопрстћуфхцчџш");

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
