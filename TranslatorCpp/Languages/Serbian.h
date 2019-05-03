#include "..\language.h"

#define SERBIAN_BASE translator::Language<Serbian, wchar_t>
struct Serbian : public SERBIAN_BASE
{
	using letter = wchar_t;

	enum class word_type {
		именица, заменица, глагол, придев, прилог, остало,
		РЕЧЕНИЦА,
		ИменичкаСинтагма,
		ГлаголскаСинтагма,
		ПрилошкаОдредба
	};

#define имен Serbian::word_type::именица
#define зам Serbian::word_type::заменица
#define глаг Serbian::word_type::глагол
#define прид Serbian::word_type::придев
#define прил Serbian::word_type::прилог
#define остл Serbian::word_type::остало
#define РЕЧН Serbian::word_type::РЕЧЕНИЦА
#define ИС Serbian::word_type::ИменичкаСинтагма
#define ГС Serbian::word_type::ГлаголскаСинтагма
#define Одр Serbian::word_type::ПрилошкаОдредба

	enum class attribute_categories { падеж, број, род_, лице };
#define пад Serbian::attribute_categories::падеж
#define бр	Serbian::attribute_categories::број
#define род	Serbian::attribute_categories::род_
#define лиц Serbian::attribute_categories::лице

	enum class attributes
	{
		номинатив, генитив, датив, акузатив, вокатив, инструментал, локатив,
		лице1, лице2, лице3,
		једнина, множина,
		мушки, женски, средњи,
		позитив, компаратив, суперлатив,
		инфинитив,
		живо,
		дужи_облик,
		прелазни,
		аугментатив, деминутив,

		//not real attributes as they are used for basis
		презентска_основа, перфектна_основа,
		основа_множине, основа_позитива,
		основа_једнине
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
#define инф attrs::инфинитив
#define д_о attrs::дужи_облик
#define прел attrs::прелазни

#define ауг attrs::аугментатив
#define дем attrs::деминутив

#define презосн attrs::презентска_основа
#define перфосн attrs::перфектна_основа
#define оснмнож attrs::основа_множине
#define оснједн attrs::основа_једнине
#define оснпоз attrs::основа_позитива

	static const map<attrs, cats> belongs_to_category;

	static constexpr bool is_phony_attribute(attributes a)
	{
		return a == оснмнож
			|| a == перфосн
			|| a == презосн
			|| a == оснједн
			|| a == оснмнож
			|| a == оснпоз;
	}

	Serbian() : SERBIAN_BASE() {}

	static string_t wordtype_to_string_t(word_type wt)
	{
		switch (wt)
		{
		case word_type::именица:
			return L"именица";
		case word_type::заменица:
			return L"заменица";
		case word_type::глагол:
			return L"глагол";
		case word_type::придев:
			return L"придев";
		case word_type::прилог:
			return L"прилог";
		case word_type::остало:
			return L"остало";
		case word_type::РЕЧЕНИЦА:
			return L"РЕЧЕНИЦА";
		case word_type::ИменичкаСинтагма:
			return L"ИменичкаСинтагма";
		case word_type::ГлаголскаСинтагма:
			return L"ГлаголскаСинтагма";
		case word_type::ПрилошкаОдредба:
			return L"ПрилошкаОдредба";
		default:
			ASSERT(false);
		}
	}

	static bool is_duplicate(
		const translator::dictionary_word<Serbian>& w1,
		const translator::dictionary_word<Serbian>& w2)
	{
		if (w1.word != w2.word || w1.wordtype != w2.wordtype)
			return false;

		if (w1.wordtype == word_type::заменица)
			return w1.attrs == w2.attrs;

		if (w1.word == L"његов" || w1.word == L"њен" || w1.word == L"њихов")
			return false;

		return true;
	}

	static const word_type Sentence = word_type::РЕЧЕНИЦА;

	static constexpr bool is_word_type(word_type wt)
	{
		return wt == word_type::глагол ||
			wt == word_type::заменица ||
			wt == word_type::именица ||
			wt == word_type::придев ||
			wt == word_type::прилог;
	}

	static bool should_capitalize(const translator::word_form<Serbian> &w)
	{
		return false;
	}
};