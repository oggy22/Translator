#include "language.h"
#include <unordered_map>

struct Serbian
{
	using letter = wchar_t;
	using string_t = std::basic_string < letter >;

	enum class word_type { именица, заменица, глагол, придев, прилог };

	enum class attribute_categories { падеж, број, род };

	enum class attributes
	{
		номинатив, генитив, датив, акузатив, инструментал,
		лиц1, лиц2, лиц3,
		једн, множ,
		муш, жен, сре
	};

	const std::unordered_map<attributes, attribute_categories> belongs_to_category = std::unordered_map<attributes, attribute_categories>
	{
		{ attributes::номинатив, attribute_categories::падеж },
		{ attributes::генитив, attribute_categories::падеж },
		{ attributes::датив, attribute_categories::падеж },
		{ attributes::номинатив, attribute_categories::падеж }
	};

	const std::vector<translator::dictionary_word<Serbian>> dictWords;

	Serbian()
		: dictWords(
	{
		// Заменице:
		{ L"ја", word_type::заменица, { attributes::лиц1, attributes::једн },
		{
			{ L"мене", { attributes::генитив, attributes::једн } },
			{ L"мени", { attributes::датив, attributes::једн } },
			{ L"мене", { attributes::акузатив, attributes::једн } }
		} },
		{ L"ти", word_type::заменица, { attributes::лиц2, attributes::једн },
		{
			{ L"тебе", { attributes::генитив, attributes::једн } },
			{ L"теби", { attributes::датив, attributes::једн } },
			{ L"тебе", { attributes::акузатив, attributes::једн } },
		} },
		{ L"он", word_type::заменица, { attributes::лиц3, attributes::једн } },
		{ L"она", word_type::заменица, { attributes::лиц3, attributes::једн } },
		{ L"оно", word_type::заменица, { attributes::лиц3, attributes::једн } },

		// Глаголи:
		{ L"волети", word_type::глагол, {} },
		{ L"гледати", word_type::глагол, {} },
		{ L"ићи", word_type::глагол, {} },

		// Именице:
		{ L"кућа", word_type::именица, {attributes::жен} }
	})
	{
		const std::vector<translator::word_rule<Serbian>> word_rules
		{
			// Глаголи:
			{ L"%ти", L"%м", word_type::глагол, { attributes::једн, attributes::лиц1 } },
			{ L"%ти", L"%ш", word_type::глагол, { attributes::једн, attributes::лиц2 } },
			{ L"%ти", L"%", word_type::глагол, { attributes::једн, attributes::лиц3 } },
			{ L"%ти", L"%мо", word_type::глагол, { attributes::множ, attributes::лиц1 } },
			{ L"%ти", L"%те", word_type::глагол, { attributes::множ, attributes::лиц2 } },
			{ L"%ити", L"%е", word_type::глагол, { attributes::множ, attributes::лиц3 } },

			// Именице:
			{ L"%", L"%", word_type::глагол, { attributes::једн, attributes::номинатив } },			
			{ L"%а", L"%е", word_type::глагол, { attributes::једн, attributes::генитив } },
			{ L"%а", L"%и", word_type::глагол, { attributes::једн, attributes::датив} },
			{ L"%а", L"%у", word_type::глагол, { attributes::једн, attributes::акузатив } },
			{ L"%а", L"%ом", word_type::глагол, { attributes::једн, attributes::инструментал } },
		};
		translator::populate_words(dictWords, word_rules);
	}
};