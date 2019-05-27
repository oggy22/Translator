#pragma once
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <experimental/generator>
#include <cmath>
#include "Assert.h"

template <typename char_t, typename string_t = std::basic_string<char_t>>
struct trie_walker;

template <typename char_t>
class trie_node
{
	std::map<char_t, trie_node*> children;
	bool wordend;
	
	using string_t = std::basic_string<char_t>;

public:
	bool is_wordend() { return wordend; }

	// words must be sorted
	trie_node(std::vector<string_t>& words)
		: trie_node(convert(words), words.size(), this)
	{
		wordend = false;
	}

	static const char_t **convert(std::vector<string_t>& words)
	{
		const char_t **w = new const char_t*[words.size()];
		for (unsigned int i = 0; i < words.size(); i++)
			w[i] = words[i].c_str();

		return w;
	}

	trie_node* create_or_root(const char_t **words, int count, trie_node* p_root)
	{
		if (count == 1 && **words == 0)
			return p_root;

		return new trie_node(words, count, p_root);
	}

	trie_node(const char_t **words, int count, trie_node* p_root)
		: wordend(false)
	{
		char_t c = 0;
		int start = -1;
		int i = 0;

		if (*words[0] == 0)
		{
			i = 1;
			wordend = true;
		}

		for (; i<count; i++)
		{
			// Create new
			if (c != *words[i])
			{
				if (start >= 0)
					children[c] = new trie_node(words + start, i - start, p_root);

				start = i;

				c = *words[i];
			}

			words[i]++;
		}
		if (start >= 0)
			children[c] = new trie_node(words + start, i - start, p_root);
	}

	std::experimental::generator<std::tuple<char_t, trie_node*>> recurse()
	{
		for (auto const&[c, pt] : children)
			co_yield std::tuple<char_t, trie_node<char_t>*>(c, pt);
	}

	static std::experimental::generator<std::tuple<char_t, trie_node*, trie_node*>>
		double_recurse(
			std::map<char_t, trie_node*> map1,
			std::map<char_t, trie_node*> map2)
	{
		for (auto const&[c, pt] : map1)
		{
			auto find = map2.find(c);
			if (find != map2.end())
				co_yield std::tuple<char_t, trie_node*, trie_node*>(c, pt, find->second);
		}
	}

	static std::experimental::generator<std::tuple<char_t, trie_node*, trie_node*>>
		double_recurse(trie_node& t1, trie_node& t2)
	{
		for (auto t : double_recurse(t1.children, t2.children))
			co_yield t;
	}


	static std::experimental::generator<std::tuple<bool, bool, char_t, trie_node*, trie_node*>>
		double_recurse(trie_walker<char_t>& tw1, trie_walker<char_t>& tw2)
	{
		if (tw1.p_node->is_wordend() && tw2.p_node->is_wordend())
		{
			for (auto t : double_recurse(tw1.p_root->children, tw2.p_root->children))
				co_yield std::tuple<bool, bool, char_t, trie_node*, trie_node*>
				(true, true, std::get<0>(t), std::get<1>(t), std::get<2>(t));
		}

		if (tw1.p_node->is_wordend())
		{
			for (auto t : double_recurse(tw1.p_root->children, tw2.p_node->children))
				co_yield std::tuple<bool, bool, char_t, trie_node*, trie_node*>
				(true, false, std::get<0>(t), std::get<1>(t), std::get<2>(t));
		}

		if (tw2.p_node->is_wordend())
		{
			for (auto t : double_recurse(tw1.p_node->children, tw2.p_root->children))
				co_yield std::tuple<bool, bool, char_t, trie_node*, trie_node*>
				(false, true, std::get<0>(t), std::get<1>(t), std::get<2>(t));
		}

		for (auto t : double_recurse(tw1.p_node->children, tw2.p_node->children))
			co_yield std::tuple<bool, bool, char_t, trie_node*, trie_node*>
			(false, false, std::get<0>(t), std::get<1>(t), std::get<2>(t));
	}

	trie_node* traverse(const string_t& str)
	{
		return traverse(str.c_str());
	}

	trie_node* traverse(const char_t *p_str)
	{
		char_t c = *p_str;
		if (c == 0)
			return this;

		auto iter = children.find(c);
		if (iter == children.end())
			return nullptr;

		return iter->second->traverse(p_str + 1);
	}
};
//#undef set

template <typename char_t, typename string_t = std::basic_string<char_t>>
std::set<string_t> find_palindromes(std::vector<string_t>& words, int max_length)
{
	// Create a trie out of words
	std::sort(words.begin(), words.end());
	trie_node<char_t> root(words);

	// Invert words
	for (string_t& word : words)
		std::reverse(word.begin(), word.end());

	// Create a trie out of inverses of words
	std::sort(words.begin(), words.end());
	trie_node<char_t> rooti(words);

	string_t st;
	std::set<string_t> results;
	trie_walker<char_t> tw(&root), twi(&rooti);
	recurse_tries(tw, twi, results, max_length);
	return results;
}

template <typename char_t, typename string_t = std::basic_string<char_t>>
struct trie_walker
{
	trie_node<char_t> *p_root, *p_node;
	std::basic_string<char_t> st;

	bool at_wordend()
	{
		return p_node->is_wordend();
	}

	trie_walker(trie_node<char_t> *p_root) : p_root(p_root), p_node(p_root) { }

	string_t last_word_backwads()
	{
		auto iter = std::find(st.rbegin(), st.rend(), char_t(' '));
		
		string_t ret(st.rbegin(), iter);
		return ret;
	}

	trie_node<char_t> *move_forward(bool sp, char_t c, trie_node<char_t> *np)
	{
		if (sp)
			st += ' ';
		st += c;

		trie_node<char_t> * p = p_node;
		p_node = np;
		return p;
	}

	void move_back(bool sp, trie_node<char_t> *np)
	{
		p_node = np;
		
		st.pop_back();
		if (sp)
			st.pop_back();
	}
};

template <typename char_t, typename string_t = std::basic_string<char_t>>
void recurse_tries(trie_walker<char_t>& tw, trie_walker<char_t>& twi, std::set<string_t>& results, unsigned int max_length)
{
	// Both at word ends
	if (tw.at_wordend() && twi.at_wordend() && !tw.st.empty())
	{
		string_t post = twi.st;
		std::reverse(post.begin(), post.end());
		string_t result = tw.st + char_t(' ') + post;
		results.insert(result);
	}
	// Both midword
	else if (!tw.at_wordend() && !twi.at_wordend())
	{
		if (twi.p_node->traverse(tw.last_word_backwads()))
		{
			string_t post = twi.st;
			std::reverse(post.begin(), post.end());
			string_t result = tw.st + post;
			results.insert(result);
		}
	}
	
	for (auto[b, bi, c, pn, pni] : trie_node<char_t>::double_recurse(tw, twi))
	{
		auto ptr = pn->traverse(twi.last_word_backwads());
		if (ptr != nullptr && ptr->is_wordend())
		{
			string_t pre = tw.st;
			if (tw.at_wordend())
				pre += char_t(' ');

			string_t post = twi.st;
			std::reverse(post.begin(), post.end());

			string_t result = pre + c + post;
			results.insert(result);
		}
	}

	if (tw.st.length() > max_length)
		return;

	for (auto[sp, spi, c, pt, pti] : trie_node<char_t>::double_recurse(tw, twi))
	{
		trie_node<char_t>* p = tw.move_forward(sp, c, pt);
		trie_node<char_t>* pi = twi.move_forward(spi, c, pti);

		recurse_tries(tw, twi, results, max_length);
		
		tw.move_back(sp, p);
		twi.move_back(spi, pi);
	}
}

template <typename char_t, typename string_t = std::basic_string<char_t>>
class palindrome
{
	string_t pal;
	int spaces = 0;

public:
	palindrome(const string_t& s) : pal(s)
	{
		if (s.size() == 0)
			return;

		ASSERT(s.front() != ' ');
		ASSERT(s.back() != ' ');
		for (unsigned i = 1; i < s.size(); i++)
		{
			ASSERT(s[i] != ' ' || s[i - 1] != ' ');
			if (s[i] == ' ')
				spaces++;
		}
	}

	const string_t& word() const
	{
		return pal;
	}

	int number_of_words() const
	{
		return spaces + 1;
	}

	int number_of_letters() const
	{
		return pal.size() - spaces;
	}

	int number_of_chars() const
	{
		return pal.size();
	}

	float average_word_length() const
	{
		return float(number_of_letters()) / number_of_words();
	}

	float stddev_word_legth() const
	{
		float avg = average_word_length();
		float sum = 0;
		int len = 0;
		for (char_t c : pal)
		{
			if (c != ' ')
			{
				len++;
			}
			else
			{
				sum += (len - avg) * (len - avg);
				len = 0;
			}
		}
		sum += (len - avg) * (len - avg);

		sum /= number_of_words();

		return sqrtf(sum);
	}
};