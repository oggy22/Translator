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

	/// <summary>
	/// Represents strings with asterix and jokers for example "*s".
	/// Knows how to compare them, match to words and transform.
	/// </summary>
	/// <typeparam name="Lang">Language</typeparam>
	template <typename Lang>
	class pattern
	{
		using char_t = typename Lang::letter;
		using string_t = basic_string <char_t>;
		string_t pre, post;
		bool has_asterisk;

		size_t length() const
		{
			return pre.length() + post.length();
		}

	public:
		pattern(const string_t& s)
		{
			const char_t asterisk = char_t('*');
			const typename string_t::size_type pos = s.find(asterisk);
			if (pos != string_t::npos)
			{
				ASSERT(0 <= pos && pos < s.length());
				ASSERT(s.find(asterisk, pos + 1) == string_t::npos);
				pre = s.substr(0, pos);
				post = s.substr(pos + 1);
				has_asterisk = true;
			}
			else
			{
				pre = s;
				has_asterisk = false;
			}
		}

		//TODO: This may need to be tested better
		bool operator>(const pattern& other) const
		{
			// Without a joker the rule can't be the stronger one
			if (!has_asterisk)
				return false;

			if (!other.has_asterisk)
				return starts_with(other.pre, pre) && ends_with(other.pre, post) && length() < other.pre.length();

			return starts_with(pre, other.pre) && ends_with(post, other.post);
		}

		bool match(const string_t& s) const
		{
			if (!has_asterisk)
				return pre == s;

			if (pre.length() + post.length() >= s.length())
				return false;

			for (int i = 0; i < pre.length(); i++)
			{
				if (pre[i] == s[i])
					continue;
			
				if (Lang::joker_can_replace(pre[i], s[i]))
					continue;

				return false;
			}

			size_t start = s.length() - post.length();
			for (int i = 0; i < post.length(); i++)
			{
				if (post[i] == s[start + i])
					continue;

				if (Lang::joker_can_replace(post[i], s[start + i]))
					continue;

				return false;
			}

			return true;
		}

		string_t match_and_transform(const string_t& input, const pattern& to) const
		{
			ASSERT(has_asterisk == to.has_asterisk);

			if (!match(input))
				ASSERT(false);

			if (!has_asterisk)
				return to.pre;

			size_t core_len = input.length() - length();

			const char_t joker = char_t('#');

			if (to.post.length() > 1 && to.post[1] == joker)
			{

			}

			string_t res = convert(to.pre, pre, input) + input.substr(pre.length(), core_len) + convert(to.post, post, input.substr(pre.length() + core_len));
			for (int i = 0; i < res.length(); i++)
			{
				
			}
			return res;
		}

		void printw(std::wostream& wos) const
		{
			wos << std::wstring(pre.begin(), pre.end());
			if (has_asterisk)
				wos << L"*" << std::wstring(post.begin(), post.end());
		}

private:
		static string_t convert(string_t str, string_t base, string_t source)
		{
			//ASSERT(str.length() <= source.length());

			string_t res = str;
			int j = 0;
			for (int i = 0; i < res.length(); i++)
			{
				if (!Lang::is_joker(str[i]))
					continue;

				while (j < base.length() && base[j] != str[i]) j++;
				if (j >= base.length())
					throw "The joker not found in base";
				
				ASSERT(base[j] == str[i]);

				res[i] = source[j];
			}
			return res;
		}
	};
}
