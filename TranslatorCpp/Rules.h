#pragma once

#include "Words.h"

namespace translator
{
	/// <summary>A single node in a rule, either left node, or any node on the right side</summary>
	template <class Language>
	class rule_node
	{
		using attrs_t = typename Language::attributes;
		using cats_t = typename Language::attribute_categories;

	public:
		const typename Language::string_t word;
		typename Language::word_type wordtype;
		attribute_manager<Language> am;

		const enum node_type_t { LITERAL, TOKEN } node_type;

		rule_node(
			typename Language::string_t word
		) : word(word), node_type(LITERAL) {}

		template <typename... Values>
		rule_node(
			typename Language::word_type wordtype, Values... values
		) : wordtype(wordtype), node_type(TOKEN), am(values...) {}

		bool accept(const word_form<Language>& w, map<cats_t, attrs_t>& values) const
		{
			ASSERT_WITH_MSG(false, "This should not be used");
			if (!word.empty() && word != w.word)
				return false;

			if (this->wordtype != w.p_dw->wordtype)
				return false;

			// Check attributes
			for (auto a : attrs)
			{
				if (w.attrs.count(a))
					continue;

				if (w.p_dw->attrs.count(a))
					continue;

				return false;
			}

			// Check categories
			for (auto c : cats)
			{
				auto iter = values.find(c);
				//if (iter != values.end() && iter->second != 
			}

			return true;
		}
	};

	/// <summary>Contains left node and right nodes of the rule.</summary>
	template <class Language>
	class rule
	{
	public:
		using node_t = rule_node<Language>;
		using size_type = typename vector<node_t>::size_type;

		node_t left;
		vector<node_t> right;

		size_type size() const
		{
			return right.size();
		}

		const node_t& operator[](int i) const
		{
			return right[i];
		}
	};

	template <class Language>
	class parsing_node
	{
		using string_t = typename Language::string_t;
		const string_t st;
		const word_form<Language>* const p_wf;
		const rule<Language>* const p_rule;
		const std::vector<const parsing_node*> children;
		const attribute_manager<Language> am;

	public:
#pragma region Constructors
		// Literal
		parsing_node(const string_t& st) : st(st), p_rule(nullptr), p_wf(nullptr)
		{
			ASSERT(is_literal() && !is_word_form() && !is_rule_application());
		}

		// Word Form
		parsing_node(const word_form<Language>& wf) : st(), p_wf(&wf), p_rule(nullptr), am(wf.attrs, wf.p_dw->attrs)
		{
			ASSERT(!is_literal() && is_word_form() && !is_rule_application());
		}

		// Rule Application
		template <typename...PN>
		parsing_node(const rule<Language>& r, const PN*... pn) : st(), p_wf(nullptr), p_rule(&r), children({ pn... })
		{
			check_parameters(pn...);
			ASSERT(!is_literal() && !is_word_form() && is_rule_application());
		}

		template <typename...PN>
		inline void check_parameters(const parsing_node<Language>* const pn, const PN* const ... pns)
		{
			check_parameters(pns...);
		}

		inline void check_parameters() {}
#pragma endregion

		bool is_literal() const
		{
			return st.size() > 0;
		}

		bool is_word_form() const
		{
			return p_wf != nullptr;
		}

		bool is_rule_application() const
		{
			return p_rule != nullptr;
		}

		int size() const
		{
			if (p_rule == nullptr)
				return 0;
			return p_rule->size();
		}

		typename Language::word_type get_wordtype() const
		{
			if (is_word_form())
				return p_wf->p_dw->wordtype;
			if (is_rule_application())
				return p_rule->left.wordtype;
			ASSERT(false);
		}

		/// <summary>Checks if attribute_manager can accept this parsing_node.
		/// Returns true iff attribute_manager has been updated</summary>
		bool accept(const rule_node<Language>& nd, attribute_manager<Language>& am) const
		{
			if (is_literal())
				return nd.node_type == nd.LITERAL && nd.word == this->st;

			attribute_manager<Language> copy_am(am);

			if (is_rule_application() && p_rule->left.wordtype != nd.wordtype)
				return false;

			if (is_word_form())
				if (this->p_wf->p_dw->wordtype != nd.wordtype)
					return false;

			// Check attribute requirements on the node
			for (auto attr : nd.am.attrs())
				if (!this->p_wf->contains(attr))
					return false;

			if (!(copy_am += nd.am))
				return false;

			if (!(copy_am += this->am))
				return false;

			am = copy_am;

			return true;
		}
	};

	template <typename Language>
	std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const parsing_node<Language>& pn)
	{
		if (!pn.is_literal())
			os << Language::wordtype_to_string_t(pn.get_wordtype());
		return os;
	}

	template <typename Language>
	std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const parsing_node<Language>& pn)
	{
		if (!pn.is_literal())
			os << Language::wordtype_to_string_t(pn.get_wordtype());
		return os;
	}
}