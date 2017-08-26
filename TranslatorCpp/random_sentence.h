#pragma once

#include "language.h"
#include <random>

namespace translator
{
	template<typename Language>
	const rule<Language>& get_random_rule(std::default_random_engine& device, typename Language::word_type wt = Language::Sentence)
	{
		std::uniform_int_distribution<int> uniform_dist(0, Language::grammar_rules.size() - 1);
		int pos;
		do
		{
			pos = uniform_dist(device);
		} while (Language::grammar_rules[pos].left.wordtype != wt);

		return Language::grammar_rules[pos];
	}

	template<typename Language>
	typename Language::attributes random_attr(typename Language::attribute_categories cat, std::default_random_engine& device)
	{
		auto size = Language::belongs_to_category.size();
		std::uniform_int_distribution<int> uniform_dist(0, size - 1);

		while (true)
		{
			auto iter = Language::belongs_to_category.begin();
			std::advance(iter, uniform_dist(device));
			if (iter->second == cat)
				return iter->first;
		}
	}

	template<typename Language>
	const dictionary_word<Language>& get_dictionary_word(
		std::default_random_engine& device,
		typename Language::word_type wt = Language::Sentence,
		typename attribute_manager<Language>& am = attribute_manager<Language>()
		)
	{
		std::uniform_int_distribution<int> uniform_dist(0, Language::dictWords().size() - 1);
		int pos;
		do
		{
			do
			{
				pos = uniform_dist(device);
			} while (Language::dictWords()[pos].wordtype != wt);
		
			const dictionary_word<Language>& dw = Language::dictWords()[pos];
			if (dw.can_accept(am))
				break;

		} while (!Language::dictWords()[pos].can_accept(am));

		return Language::dictWords()[pos];
	}

	template<typename Language, typename string_t = Language::string_t>
	class RNode
	{
		enum type { string, word, node } t;
		const string_t st;
		const dictionary_word<Language> *p_dw;
		const rule<Language> *p_rule;
		vector<RNode> children;
		attribute_manager<Language> am;

	public:
		RNode(const string_t& st) : st(st), t(RNode::string)
		{

		}

		RNode(const dictionary_word<Language>& dw, std::default_random_engine& device, const attribute_manager<Language>& am)
			: p_dw(&dw), t(RNode::word), am(am)
		{

		}

		RNode(const rule<Language>& r, std::default_random_engine& device, const attribute_manager<Language>& am = attribute_manager<Language>())
			: p_rule(&r), am(am), t(RNode::node)
		{
			for (auto child : r.right)
			{
				if (child.word != Language::string_t())
				{
					children.emplace_back(child.word);
				}
				else if (Language::is_word_type(child.wordtype))
				{
					const auto& dw = get_dictionary_word<Language>(device, child.wordtype, child.am);
					children.emplace_back(dw, device, child.am);
				}
				else
				{
					const rule<Language>& r = get_random_rule<Language>(device, child.wordtype);
					children.emplace_back(r, device);
				}
			}
		}

		~RNode()
		{
		}

		void consolidate_attributes(std::default_random_engine& device)
		{
			attribute_manager<Language> am;
			for (const auto& child : children)
			{
				am += child.am;
				if (child.t == RNode::word)
				{
					am += child.p_dw->attrs;
				}
			}

			// Assign attribute to each free_cat
			while (true)
			{
				bool found = false;
				typename Language::attributes attr;
				for (const auto& cat : am.free_cats())
				{
					attr = random_attr<Language>(cat, device);
					found = true;
					break;
				}

				if (!found)
					break;

				am += attr;
			}

			// Recursively consolidate children
			for (auto& child : children)
			{
				child.am += am;
				child.consolidate_attributes(device);
			}
		}

		string_t ToString() const
		{
			switch (t)
			{
			case RNode::string:
				return st;
			case RNode::word:
			{
				const word_form<Language>& w = p_dw->find_word_form(am);
				return w.word;
			}
			case RNode::node:
			{
				string_t stSum;
				for (auto &child : children)
				{
					stSum += child.ToString();
					stSum += string_t::value_type(' ');
				}
				return stSum.substr(0, stSum.size() - 1);
			}
			default:
				FAIL("impossible case");
			}
			return string_t();
		}
	};

	template<typename Language, typename string_t = Language::string_t>
	string_t random_sentence(int seed)
	{
		std::random_device rand;
		//cout << seed << endl;
		std::default_random_engine device(seed);
		//std::default_random_engine device;

		const rule<Language>& r = get_random_rule<Language>(device);

		RNode<Language> node(r, device);
		node.consolidate_attributes(device);
		return node.ToString();
	}
}