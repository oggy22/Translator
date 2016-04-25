#include <unordered_map>
#include <sstream>
#include "..\language.h"

struct Serbian
{
	using letter = wchar_t;
	using string_t = std::basic_string < letter >;
	
	static const Serbian::string_t Serbian::stAlphabet;

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
		мушки, женски, средњи,
		позитив, компаратив, суперлатив,
		живо,

		//not real attributes as they are used for basis
		презентска_основа, перфектна_основа,
		основа_множине
	};

	using wt = word_type;
	using attrs = attributes;
	using cats = attribute_categories;

#define ном attrs::номинатив
#define ген attrs::генитив
#define дат attrs::датив
#define акуз attrs::акузатив
#define вок attrs::вокатив
#define инстр attrs::инструментал
#define лок attrs::локатив

#define муш attrs::мушки
#define жен attrs::женски
#define сред attrs::средњи
#define лиц1 attrs::лице1
#define лиц2 attrs::лице2
#define лиц3 attrs::лице3
#define једн attrs::једнина
#define множ attrs::множина
#define поз	attrs::позитив
#define комп attrs::компаратив
#define суп	attrs::суперлатив

#define жив attrs::живо

#define презосн attrs::презентска_основа
#define перфосн attrs::перфектна_основа
#define оснмнож attrs::основа_множине

	static const std::unordered_map<attrs, cats> belongs_to_category;

	static bool is_phony_attribute(attributes a)
	{
		return a == оснмнож || a == перфосн || a == презосн;
	}

	static const std::vector<translator::dictionary_word<Serbian>> dictWords;

	static const std::vector<translator::word_rule<Serbian>> word_rules;

	static const std::vector<translator::rule<Serbian>> grammar_rules;

	Serbian()
	{
#ifdef _DEBUG
		for (auto& rule : word_rules)
			rule.used = false;
#endif
		translator::populate_words<Serbian>();
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