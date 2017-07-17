#pragma once

#include "stdafx.h"
 
template <typename string_t = basic_string<Char>>
static bool starts_with(const string_t& str, const string_t& prefix)
{
	if (prefix.length() > str.length())
		return false;

	return equal(prefix.cbegin(), prefix.end(), str.cbegin());
}

template <typename string_t = basic_string<Char>>
static bool ends_with(const string_t& str, const string_t& sufix)
{
	if (sufix.length() > str.length())
		return false;

	return equal(sufix.cbegin(), sufix.end(), str.cbegin() + str.size() - sufix.size());
}

namespace translator
{
	using namespace std;

	template <typename Char>
	class pattern
	{
		using string_t = basic_string < Char >;
		string_t pre, post;
		bool has_joker;

		size_t length() const
		{
			return pre.length() + post.length();
		}

	public:
		pattern(const string_t& s)
		{
			const Char joker = Char('*');
			const typename string_t::size_type pos = s.find(joker);
			if (pos != string_t::npos)
			{
				ASSERT(0 <= pos && pos < s.length());
				ASSERT(s.find(joker, pos + 1) == string_t::npos);
				pre = s.substr(0, pos);
				post = s.substr(pos + 1);
				has_joker = true;
			}
			else
			{
				pre = s;
				has_joker = false;
			}
		}

		//TODO: This may need to be tested better
		bool operator>(const pattern& other) const
		{
			// Without a joker the rule can't be the stronger one
			if (!has_joker)
				return false;

			if (!other.has_joker)
				return starts_with(other.pre, pre) && ends_with(other.pre, post) && length() < other.pre.length();

			return starts_with(pre, other.pre) && ends_with(post, other.post);
		}

		bool match(const string_t& s) const
		{
			if (!has_joker)
				return pre == s;

			if (pre.length() + post.length() >= s.length())
				return false;

			if (s.compare(0, pre.length(), pre))
				return false;

			if (s.compare(s.length() - post.length(), post.length(), post))
				return false;

			return true;
		}

		string_t match_and_transform(const string_t& input, const pattern& to) const
		{
			ASSERT(has_joker == to.has_joker);

			if (!match(input))
				ASSERT(false);

			if (!has_joker)
				return to.pre;

			size_t core_len = input.length() - length();

			return to.pre + input.substr(pre.length(), core_len) + to.post;
		}

		void printw(std::wostream& wos) const
		{
			wos << std::wstring(pre.begin(), pre.end());
			if (has_joker)
				wos << L"*" << std::wstring(post.begin(), post.end());
		}
	};
}