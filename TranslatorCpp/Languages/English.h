#include "..\language.h"

#define ENGLISH_BASE translator::Language<English, char>
struct English : public ENGLISH_BASE
{
	using letter = char;

	enum class word_type
	{
		noun, verb, pronoun, adjective, adverb, determiner, number, other, NP, VP, Sentence
	};

#define noun	English::word_type::noun
#define verb	English::word_type::verb
#define pron	English::word_type::pronoun
#define adj		English::word_type::adjective
#define adv		English::word_type::adverb
#define det		English::word_type::determiner
#define numb	English::word_type::number
#define othr	English::word_type::other
#define NP		English::word_type::NP
#define VP		English::word_type::VP
#define Sent	English::word_type::Sentence

	enum class attribute_categories { gender, plurality, person };

	enum class attributes
	{
		present, past, future, continous, perfect,
		per1, per2, per3,
		sing, plur,
		posses, refl, nom, accus
	};

#define pres English::attributes::present
#define past English::attributes::past
#define perf English::attributes::perfect
#define per1 English::attributes::per1
#define per2 English::attributes::per2
#define per3 English::attributes::per3
#define sing English::attributes::sing
#define plur English::attributes::plur
#define nom English::attributes::nom
#define accus English::attributes::accus
#define posses English::attributes::posses
#define refl English::attributes::refl

#define per English::attribute_categories::person
#define plt English::attribute_categories::plurality

	static const map<attributes, attribute_categories> belongs_to_category;

	static const map<char, string_t> jokers;

	static bool is_phony_attribute(attributes a)
	{
		return false;
	}

	English() : ENGLISH_BASE() {}

	static string_t wordtype_to_string_t(word_type wt)
	{
		switch (wt)
		{
		case word_type::adjective:
			return "adjective";
		case word_type::adverb:
			return "adverb";
		case word_type::determiner:
			return "determiner";
		case noun:
			return "noun";
		case NP:
			return "NP";
		case word_type::pronoun:
			return "pronoun";
		case word_type::Sentence:
			return "Sentence";
		case verb:
			return "verb";
		case VP:
			return "VP";
		default:
			ASSERT(false);
		}
	}

	static bool is_duplicate(
		const translator::dictionary_word<English>& w1,
		const translator::dictionary_word<English>& w2)
	{
		if (w1.word != w2.word || w1.wordtype != w2.wordtype)
			return false;

		if (w1.word == "you")
			return w1.attrs == w2.attrs;

		return true;
	}

	static const word_type Sentence = word_type::Sentence;

	static constexpr bool is_word_type(word_type wt)
	{
		return wt == word_type::adjective ||
			wt == word_type::adverb ||
			wt == word_type::determiner ||
			wt == noun ||
			wt == word_type::number ||
			wt == word_type::other ||
			wt == word_type::pronoun ||
			wt == verb;
	}

	static bool should_capitalize(const translator::word_form<English> &w)
	{
		if (w.p_dw->wordtype == word_type::pronoun && w.word == "i")
			return true;

		return false;
	}
};