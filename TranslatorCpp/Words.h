#pragma once

#include "pattern.h"


namespace translator
{
	template <class Language>
	struct word_form;

	template <class Language>
	struct dictionary_word
	{
		using attr_t = typename Language::attributes;
		const typename Language::string_t word;
		const typename Language::word_type wordtype;
		const set<typename Language::attributes> attrs;
		mutable vector<word_form<Language>> words;	//todo: this is a hack

		const word_form<Language>& find_word_form(const set<attr_t>& attrs) const
		{
			for (const auto& w : words)
				if (w.attrs == attrs)
					return w;
			ASSERT(false);
		}

		const word_form<Language>& find_word_form(const attribute_manager<Language>& am) const
		{
			for (const auto& w : words)
				if (am.accepts(w.attrs))
					return w;

			ASSERT(false);
		}

		/// <summary>Checks if a word form with the given attribute exists</summary>
		bool operator()(attr_t a) const
		{
			for (const auto& w : words)
				if (w.attrs.size() == 1 && *w.attrs.begin() == a)
					return true;
			return false;
		}

		/// <summary>Checks if a word form with the given attributes exists</summary>
		bool operator()(attr_t a1, attr_t a2) const
		{
			for (const auto& w : words)
				if (w.attrs.size() == 2
					&& w.attrs.find(a1) != w.attrs.end()
					&& w.attrs.find(a2) != w.attrs.end())
					return true;
			return false;
		}

		/// <summary>Checks if a word form with the given attributes exists</summary>
		bool operator()(attr_t a1, attr_t a2, attr_t a3) const
		{
			for (const auto& w : words)
				if (w.attrs.size() == 3
					&& w.attrs.find(a1) != w.attrs.end()
					&& w.attrs.find(a2) != w.attrs.end()
					&& w.attrs.find(a3) != w.attrs.end())
					return true;
			return false;
		}

		const word_form<Language>& operator[](attr_t a) const
		{
			for (const auto& w : words)
			{
				if (w.attrs.size() == 1 && *w.attrs.begin() == a)
					return w;
			}
			ASSERT(false);
		}

		const word_form<Language>& operator[](const set<attr_t>& attrs) const
		{
			for (const auto& w : words)
			{
				if (w.attrs == attrs)
					return w;
			}
			ASSERT(false);
		}
	};

	template <class Language>
	struct word_form
	{
		using string_t = typename Language::string_t;
		string_t word;
		set<typename Language::attributes> attrs;
		const dictionary_word<Language> *p_dw;

		bool contains(typename Language::attributes a) const
		{
			return attrs.count(a) || p_dw->attrs.count(a);
		}
	};

	template <class EnumClass>
	class nullable
	{
		static_assert(std::is_enum<EnumClass>::value, "Language::attributes must be an enum");
		using underlying_type_t = typename std::underlying_type<EnumClass>::type;
		static const underlying_type_t VOID_VALUE = -1;

		union
		{
			underlying_type_t n;
			EnumClass attr;
		} data;

	public:
		nullable()
		{
			data.n = VOID_VALUE;
		}

		nullable(EnumClass attr)
		{
			data.attr = attr;
		}

		bool is_set() const
		{
			return data.n != VOID_VALUE;
		}

		EnumClass get() const
		{
			return data.attr;
		}
	};

	template <class Language>
	struct word_rule
	{
		pattern<typename Language::letter> source;
		pattern<typename Language::letter> destination;
		typename Language::word_type wt;
		using char_t = typename Language::letter;
		set<typename Language::attributes> attrs;
		nullable<typename Language::attributes> f;
#ifdef _DEBUG
		mutable bool used;
#endif
		bool is_set() const
		{
			return f.is_set();
		}
	};

	template <class Language>
	struct word_to_word_rule
	{
		pattern<typename Language::letter> source;
		pattern<typename Language::letter> destination;
		typename Language::word_type wt_source;
		typename Language::word_type wt_destination;
		set<typename Language::attributes> attrs;
		set<typename Language::attributes> attrs_added;	//e.g. deminutive

#ifdef _DEBUG
		mutable bool used;
#endif
	};
}