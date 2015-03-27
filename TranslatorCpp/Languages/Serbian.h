#include <unordered_map>
#include <sstream>
#include "..\language.h"

struct Serbian
{
	using letter = wchar_t;
	using string_t = std::basic_string < letter >;

	enum class word_type { именица, заменица, глагол, придев, прилог, РЕЧЕНИЦА, ИС, ГС };

	enum class attribute_categories { падеж, број, род, лице };
	
	enum class attributes
	{
		номинатив, генитив, датив, акузатив, инструментал,
		лиц1, лиц2, лиц3,
		једн, множ,
		муш, жен, сре
	};

	using wt = word_type;
	using attrs = attributes;
	using cats = attribute_categories;

	const std::unordered_map<attrs, cats> belongs_to_category = std::unordered_map<attrs, cats>
	{
		{ attrs::номинатив, cats::падеж },
		{ attrs::генитив, cats::падеж },
		{ attrs::датив, cats::падеж },
		{ attrs::номинатив, cats::падеж }
	};

	/*const*/ std::vector<translator::dictionary_word<Serbian>> dictWords;

	/*const*/ std::vector<translator::rule<Serbian>> rules;

	/*const*/ std::vector<string_t> tests;

	Serbian()
		: dictWords(
	{
		// Заменице:
		{ L"ја", word_type::заменица, { attrs::лиц1, attrs::једн },
		{
			{ L"мене", { attrs::генитив, attrs::једн } },
			{ L"мени", { attrs::датив, attrs::једн } },
			{ L"мене", { attrs::акузатив, attrs::једн } }
		} },
		{ L"ти", word_type::заменица, { attrs::лиц2, attrs::једн },
		{
			{ L"тебе", { attrs::генитив, attrs::једн } },
			{ L"теби", { attrs::датив, attrs::једн } },
			{ L"тебе", { attrs::акузатив, attrs::једн } },
		} },
		{ L"он", word_type::заменица, { attrs::лиц3, attrs::једн } },
		{ L"она", word_type::заменица, { attrs::лиц3, attrs::једн } },
		{ L"оно", word_type::заменица, { attrs::лиц3, attrs::једн } },

		// Глаголи:
		{ L"волети", word_type::глагол, {} },
		{ L"гледати", word_type::глагол, {} },
		{ L"ићи", word_type::глагол, {} },
		{ L"певати", word_type::глагол, {} },
		{ L"радити", word_type::глагол, {} },

		// Именице:
		{ L"кућа", word_type::именица, { attrs::жен } }
	}),
	rules(
			{
				{ { word_type::РЕЧЕНИЦА },
				{ { word_type::заменица, cats::број, cats::лице }, { word_type::глагол, cats::број, cats::лице } } },
				{ { word_type::РЕЧЕНИЦА },
				{ { word_type::именица, cats::број, attrs::лиц3 }, { word_type::глагол, cats::број, cats::лице } } },
			})
	{
		const std::vector<translator::word_rule<Serbian>> word_rules
		{
			//// Заменица:
			{ { L"%" }, { L"%" }, word_type::заменица, { attrs::једн, attrs::номинатив } },

			//// Глаголи:
			{ { L"%ти" }, { L"%м" }, word_type::глагол, { attrs::једн, attrs::лиц1 } },
			{ { L"%ти" }, { L"%ш" }, word_type::глагол, { attrs::једн, attrs::лиц2 } },
			{ { L"%ти" }, { L"%" }, word_type::глагол, { attrs::једн, attrs::лиц3 } },
			{ { L"%ти" }, { L"%мо" }, word_type::глагол, { attrs::множ, attrs::лиц1 } },
			{ { L"%ти" }, { L"%те" }, word_type::глагол, { attrs::множ, attrs::лиц2 } },
			{ { L"%ити" }, { L"%е" }, word_type::глагол, { attrs::множ, attrs::лиц3 } },

			//// Именице:
			{ { L"%" }, { L"%" }, word_type::глагол, { attrs::једн, attrs::номинатив } },
			{ { L"%а" }, { L"%е" }, word_type::глагол, { attrs::једн, attrs::генитив } },
			{ { L"%а" }, { L"%и" }, word_type::глагол, { attrs::једн, attrs::датив } },
			{ { L"%а" }, { L"%у" }, word_type::глагол, { attrs::једн, attrs::акузатив } },
			{ { L"%а" }, { L"%ом" }, word_type::глагол, { attrs::једн, attrs::инструментал } },
		};
		translator::populate_words(dictWords, word_rules);
	}
};