#include "..\language.h"

#define ENGLISH_BASE translator::Language<English, char>
struct English : public ENGLISH_BASE
{
	using letter = char;

	enum class word_type { noun, verb, pronoun, adjective, adverb, article, NP, VP, Sentence };
#define noun	English::word_type::noun
#define verb	English::word_type::verb
#define pron	English::word_type::pronoun
#define adj		English::word_type::adjective
#define adv		English::word_type::adverb
#define art		English::word_type::article
#define NP		English::word_type::NP
#define VP		English::word_type::VP
#define Sent	English::word_type::Sentence

	enum class attribute_categories { gender, plurality, person };

	enum class attributes
	{
		present, past, future, continous, perfect,
		per1, per2, per3,
		sing, plur,
		posses, refl, accus
	};

#define past English::attributes::past
#define perf English::attributes::perfect
#define per1 English::attributes::per1
#define per2 English::attributes::per2
#define per3 English::attributes::per3
#define sing English::attributes::sing
#define plur English::attributes::plur
#define accus English::attributes::accus
#define posses English::attributes::posses
#define refl English::attributes::refl

#define per English::attribute_categories::person

	static const map<attributes, attribute_categories> belongs_to_category;

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
		case word_type::article:
			return "article";
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
};