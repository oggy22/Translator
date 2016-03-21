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
#define РЕЧН word_type::РЕЧЕНИЦА
#define ИС word_type::ИменичкаСинтагма
#define Одр word_type::ПрилошкаОдредба

	enum class attribute_categories { падеж, број, род, лице };
#define пад attribute_categories::падеж
#define бр	attribute_categories::број
#define лиц attribute_categories::лице

	enum class attributes
	{
		номинатив, генитив, датив, акузатив, вокатив, инструментал, локатив,
		лице1, лице2, лице3,
		једнина, множина,
		мушки, женски, средњи
	};
#define акуз attributes::акузатив
#define вок attributes::вокатив
#define ген attributes::генитив
#define дат attributes::датив
#define жен attributes::женски
#define инстр attributes::инструментал
#define једн attributes::једнина
#define лиц1 attributes::лице1
#define лиц2 attributes::лице2
#define лиц3 attributes::лице3
#define лок attributes::локатив
#define множ attributes::множина
#define ном attributes::номинатив
#define сред attributes::средњи

	using wt = word_type;
	using attrs = attributes;
	using cats = attribute_categories;

	const std::unordered_map<attrs, cats> belongs_to_category = std::unordered_map<attrs, cats>
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

	/*const*/ std::vector<translator::dictionary_word<Serbian>> dictWords;

	/*const*/ std::vector<translator::rule<Serbian>> rules;

	/*const*/ std::vector<string_t> tests;

	Serbian()
		: dictWords(
	{
		// Заменице:
		{ L"ја", зам,{ лиц1, једн },
		{
			{ L"мене",{ attrs::генитив, attrs::једнина } },
			{ L"мени",{ attrs::датив, attrs::једнина } },
			{ L"мене",{ attrs::акузатив, attrs::једнина } }
		} },
		{ L"ти", word_type::заменица,{ attrs::лице2, attrs::једнина },
		{
			{ L"тебе",{ attrs::генитив, attrs::једнина } },
			{ L"теби",{ attrs::датив, attrs::једнина } },
			{ L"тебе",{ attrs::акузатив, attrs::једнина } },
		} },
		{ L"он", word_type::заменица,{ attrs::лице3, attrs::једнина } },
		{ L"она", word_type::заменица,{ attrs::лице3, attrs::једнина } },
		{ L"оно", word_type::заменица,{ attrs::лице3, attrs::једнина } },

			// Глаголи:
		{ L"волети", глаг,{} },
		{ L"гледати", глаг,{} },
		{ L"ићи", глаг,{} },
		{ L"певати", глаг,{} },
		{ L"радити", глаг,{} },

			// Именице:
		{ L"кућа", word_type::именица,{ attrs::женски } }
	}),
		rules(
	{

		{ { РЕЧН },
		{ { зам, бр, лиц },{ глаг, бр, лиц } } },
		{ { РЕЧН },
		{ { имен, бр, лиц3 },{ глаг, бр, лиц } } },
		{ { Одр },
		{ { L"у" },{ имен, лок } } },
		{ { Одр },
		{ { L"у" },{ имен, акуз } } },
		{ { РЕЧН },{ РЕЧН, Одр } },
		{ { ИС },
		{ { прид, бр, пад },{ имен, бр, пад } } }
	})
	{
		const std::vector<translator::word_rule<Serbian>> word_rules
		{
			//// Заменица:
			{ { L"%" },{ L"%" }, word_type::заменица,{ attrs::једнина, attrs::номинатив } },

			//// Глаголи:
			{ { L"%ти" },{ L"%м" }, глаг,{ attrs::једнина, лиц1 } },
			{ { L"%ти" },{ L"%ш" }, глаг,{ attrs::једнина, лиц2 } },
			{ { L"%ти" },{ L"%" }, глаг,{ attrs::једнина, лиц3 } },
			{ { L"%ти" },{ L"%мо" }, глаг,{ attrs::једнина, лиц1 } },
			{ { L"%ти" },{ L"%те" }, глаг,{ attrs::једнина, лиц2 } },
			{ { L"%ити" },{ L"%е" }, глаг,{ attrs::једнина, лиц3 } },

			//// Именице:
			{ { L"%" },{ L"%" }, word_type::глагол,{ attrs::једнина, attrs::номинатив } },
			{ { L"%а" },{ L"%е" }, word_type::глагол,{ attrs::једнина, attrs::генитив } },
			{ { L"%а" },{ L"%и" }, word_type::глагол,{ attrs::једнина, attrs::датив } },
			{ { L"%а" },{ L"%у" }, word_type::глагол,{ attrs::једнина, attrs::акузатив } },
			{ { L"%а" },{ L"%ом" }, word_type::глагол,{ attrs::једнина, attrs::инструментал } },
		};
		translator::populate_words(dictWords, word_rules);
	}
};