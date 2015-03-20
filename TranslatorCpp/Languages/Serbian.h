#include "language.h"
#include <map>
#include <unordered_map>

struct Serbian
{
	using letter = wchar_t;
	using letters = std::basic_string < letter >;

	const char *id = "SR";
	const letters name = L"Srpski";

	const letter *alphabet;

	enum class word_type { именица, заменица, глагол };

	enum class attribute_categories { падеж, број, род };

	enum class attributes
	{
		номинатив, генитив, датив, акузатив,
		лиц1,лиц2,лиц3,
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

	std::vector<translator::dictionary_word<Serbian>> dictWords;

	Serbian()
		: dictWords(
	{
		{ L"ја", word_type::заменица, { attributes::лиц1, attributes::једн },
		{
			{ L"мене", { attributes::генитив, attributes::једн } },
			{ L"мени", { attributes::датив, attributes::једн } },
			{ L"мене", { attributes::акузатив, attributes::једн } }
		} },
		{ L"ти", word_type::заменица, { attributes::лиц2, attributes::једн } },
		{ L"он", word_type::заменица, { attributes::лиц3, attributes::једн } },
		{ L"она", word_type::заменица, { attributes::лиц3, attributes::једн } },
		{ L"оно", word_type::заменица, { attributes::лиц3, attributes::једн } },
	})
	{

	}
};