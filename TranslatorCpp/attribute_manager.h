#pragma once

#include "stdafx.h"

namespace translator
{
	template <typename Language>
	class attribute_manager
	{
		using attr_t = typename Language::attributes;
		using cat_t = typename Language::attribute_categories;
		map<cat_t, attr_t> mapping;
		set<cat_t> free_cat;
		set<attr_t> free_attr;
	
		inline void check_consistency()
		{
			for (auto attr : free_attr)
				ASSERT(Language::belongs_to_category.count(attr) == 0);

			for (auto cat : free_cat)
				ASSERT(mapping.count(cat) == 0);
		}

	public:
		attribute_manager() {}

		template <typename... Values>
		attribute_manager(attr_t attr, Values... values) : attribute_manager(values...)
		{
			ASSERT_WITH_MSG(!free_attr.count(attr), "Free attribute already contained");

			auto p_c = Language::belongs_to_category.find(attr);
			if (p_c != Language::belongs_to_category.end())
				mapping[p_c->second] = attr;	// todo: assert that mapping for this category doesn't exist
			else
				free_attr.emplace(attr);
		}

		template <typename... Values>
		attribute_manager(cat_t cat, Values... values) : attribute_manager(values...)
		{
			ASSERT_WITH_MSG(!free_cat.count(cat), "Category already contained");
			free_cat.emplace(cat);
		}

		template <typename... Args>
		attribute_manager(const set<attr_t>& attrs, Args... args) : attribute_manager(args...)
		{
			for (attr_t a : attrs)
			{
				auto pair = Language::belongs_to_category.find(a);
				if (pair == Language::belongs_to_category.end())
					free_attr.insert(a);
				else
					mapping[pair->second] = a;
			}
		}

		bool operator()(cat_t c) const
		{
			return mapping.count(c) > 0;
		}

		bool operator()(attr_t a) const
		{
			if (free_attr.count(a) > 0)
				return true;

			for (const auto& pair : mapping)
				if (pair.second == a)
					return true;

			return false;
		}

		bool operator[](cat_t c) const
		{
			auto iter = mapping.find(c);
			ASSERT(iter != mapping.end());
			return *iter;
		}

		bool operator+=(const attribute_manager<Language>& am)
		{
			for (const auto& pair : am.mapping)
				if (mapping.count(pair.first) > 0 && mapping[pair.first] != pair.second)
					return false;

			free_cat.insert(am.free_cat.begin(), am.free_cat.end());

			for (const auto& pair : am.mapping)
				mapping[pair.first] = pair.second;

			for (const auto& pair : mapping)
				free_cat.erase(pair.first);

			free_attr.insert(am.free_attr.begin(), am.free_attr.end());

			check_consistency();

			return true;
		}

		bool has_all(const attribute_manager<Language>& am) const
		{
			for (const auto& pair : am.mapping)
			{
				auto iter = mapping.find(pair.first);
				if (iter == mapping.end() || iter->second != pair.second)
					return false;
			}

			for (auto a : am.free_attr)
				if (free_attr.count(a) == 0)
					return false;

			return true;
		}

		bool accepts(const attribute_manager<Language>& am) const
		{
			for (const auto& pair : am.mapping)
			{
				auto iter = mapping.find(pair.first);
				if (iter == mapping.end())
					continue;
				
				if (iter->second != pair.second)
					return false;
			}

			return true;
		}

		std::experimental::generator<attr_t> attrs() const
		{
			for (auto attr : free_attr)
			{
				co_yield attr;
			}

			for (auto pair : mapping)
			{
				co_yield pair.second;
			}
		}
	};
}