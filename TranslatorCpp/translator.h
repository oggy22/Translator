#pragma once

#include "language.h"

namespace translator
{
	template <class Lang, class attr_t = typename Lang::attributes>
	class translator_node
	{
		const dictionary_word<Lang> word;
		const nullable<typename Lang::word_type> wt;
		myset<attr_t> attrs;

		void create_attrs()
		{
		}

		template <typename... Args>
		void create_attrs(attr_t attr, Args... args)
		{
			attrs.emplace(attr);
			create_attrs(args...);
		}

	public:
		template <typename... Args>
		translator_node(typename Lang::string_t st, Args... args)
			: word(Lang::find_dictionary_word(st))
		{
			create_attrs();
		}
	};

	template <class Lang1, class Lang2>
	struct translator
	{
		translator() { }

		static const string stConst;

		using word_type1 = typename Lang1::word_type;
		using word_type2 = typename Lang2::word_type;
		using attributes1 = typename Lang1::attributes;
		using attributes2 = typename Lang2::attributes;
		using categories1 = typename Lang1::attribute_categories;
		using categories2 = typename Lang2::attribute_categories;
		using trans_node1 = typename translator_node<Lang1>;
		using trans_node2 = typename translator_node<Lang2>;

		static const vector<std::pair<word_type1, word_type2>> wordtypes;
		static const vector<std::pair<attributes1, attributes2>> attrs;
		static const vector<std::pair<categories1, categories2>> cats;
		static const vector<std::pair<trans_node1, trans_node2>> translations;

		typename Lang2::string_t translate(const typename Lang1::string_t text)
		{
			wcout << "Trying to translate : " << text << endl;
			return Lang2::string_t();
		}

	private:
		typename Lang2::string_t translate(const vector<const typename Lang1::string_t> text)
		{
		}
	};
}