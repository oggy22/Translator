#include <unordered_map>
#include <sstream>
#include "..\language.h"

struct Serbian
{
	using letter = wchar_t;
	using string_t = std::basic_string < letter >;

	enum class word_type {
		именица, заменица, глагол, придев, прилог,
		РЕЧЕНИЦА,
		ИменичкаСинтагма,
		ГлаголскаСинтагма,
		ПрилошкаОдредба
	};

#define имен word_type::именица
#define зам word_type::заменица
#define глаг word_type::глагол
#define прид word_type::придев
#define прил word_type::прилог
#define РЕЧН word_type::РЕЧЕНИЦА
#define ИС word_type::ИменичкаСинтагма
#define Одр word_type::ПрилошкаОдредба

	enum class attribute_categories { падеж, број, род, лице };
#define пад attribute_categories::падеж
#define бр	attribute_categories::број
#define род	attribute_categories::род
#define лиц attribute_categories::лице

	enum class attributes
	{
		номинатив, генитив, датив, акузатив, вокатив, инструментал, локатив,
		лице1, лице2, лице3,
		једнина, множина,
		мушки, женски, средњи
	};
#define ном attributes::номинатив
#define ген attributes::генитив
#define дат attributes::датив
#define акуз attributes::акузатив
#define вок attributes::вокатив
#define инстр attributes::инструментал
#define лок attributes::локатив

#define муш attributes::мушки
#define жен attributes::женски
#define сред attributes::средњи
#define лиц1 attributes::лице1
#define лиц2 attributes::лице2
#define лиц3 attributes::лице3
#define једн attributes::једнина
#define множ attributes::множина

	using wt = word_type;
	using attrs = attributes;
	using cats = attribute_categories;

	const std::unordered_map<attrs, cats> belongs_to_category
	{
		// Падежи
		{ ном, cats::падеж },
		{ ген, cats::падеж },
		{ дат, cats::падеж },
		{ акуз, cats::падеж },
		{ вок, cats::падеж },
		{ инстр, cats::падеж },
		{ лок, cats::падеж },

		// Лица
		{ лиц1, cats::лице },
		{ лиц2, cats::лице },
		{ лиц3, cats::лице }
	};

	const std::vector<translator::word_rule<Serbian>> wordRules;

	/*const*/ std::vector<translator::dictionary_word<Serbian>> dictWords;

	/*const*/ std::vector<translator::rule<Serbian>> rules;

	/*const*/ std::vector<string_t> tests;

	Serbian()
		:
		wordRules(
	{
		// Глаголи:
		{ L"%ти", L"%м", глаг,{ лиц1, једн } },
		{ L"%ти", L"%ш", глаг,	{ лиц2, једн } },
		{ L"%ти", L"%",	глаг,	{ лиц3, једн } },
		{ L"%ти", L"%мо", глаг,	{ лиц1, множ } },
		{ L"%ти", L"%те", глаг,	{ лиц2, множ } },
		{ L"%ити", L"%е", глаг, { лиц3, множ } },

		// Именице:
		{ L"%а", L"%а", имен,{ једн, ном } },
		{ L"%а", L"%е", имен,{ једн, ген } },
		{ L"%а", L"%и", имен,{ једн, дат } },
		{ L"%а", L"%у", имен,{ једн, акуз } },
		{ L"%а", L"%ом", имен,{ једн, инстр } },

		{ L"%а", L"%е", имен,	{ множ, ном		} },
		{ L"%а", L"%а", имен,	{ множ, ген		} },
		{ L"%а", L"%ама", имен,	{ множ, дат		} },
		{ L"%а", L"%е", имен,	{ множ, акуз	} },
		{ L"%а", L"%ама", имен,	{ множ, инстр	} },
	}
			),

		dictWords(
	{
#include "Serbian_words.h"
	}),
		rules(
	{

		{ { РЕЧН },
		{ { зам, бр, лиц },{ глаг, бр, лиц } } },
		{ { РЕЧН },
		{ { имен, бр, лиц3 },{ глаг, бр, лиц } } },
		{ { Одр },
		{ { L"у" }, { имен, лок } } },
		{ { Одр },
		{ { L"у" }, { имен, акуз } } },
		{ { РЕЧН },
		{ РЕЧН, Одр } },
		{ { ИС },
		{ { прид, бр, пад }, { имен, бр, пад } } }
	})
	{
		translator::populate_words(dictWords, wordRules);
	}

	bool has_word(const string_t& st) const
	{
		for (const auto& w : dictWords)
		{
			for (const auto& word : w.words)
				if (word._word == st)
					return true;
		}
		return false;
	}

	template <typename Lambda>
	void traverse_words(Lambda fun) const
	{
		for (const auto& w : dictWords)
		{
			for (const auto& word : w.words)
				fun(word);
		}
	}
};