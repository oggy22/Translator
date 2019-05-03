#pragma once
#include <map>
#include <algorithm>
#include <vector>
#include <experimental/generator>
#include "Assert.h"

template <typename char_t>
class trie_node
{
	std::map<char_t, trie_node*> children;
	bool root;
	
	using string_t = std::basic_string<char_t>;

public:
	bool is_root() { return root; }

	// words must be sorted
	trie_node(std::vector<string_t>& words)
		: trie_node(convert(words), words.size(), this)
	{
		root = true;
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
		: root(false)
	{
		char_t c = 0;
		int start = -1;
		int i = 0;

		if (*words[0] == 0)
		{
			i = 1;
			root = true;
		}

		for (; i<count; i++)
		{
			// Create new
			if (c != *words[i])
			{
				if (start >= 0)
					children[c] = create_or_root(words + start, i - start, p_root);

				start = i;

				c = *words[i];
			}

			words[i]++;
		}
		if (start >= 0)
			children[c] = create_or_root(words + start, i - start, p_root);
	}

	std::experimental::generator<std::tuple<char_t, trie_node*>> recurse()
	{
		for (auto const&[c, pt] : children)
			co_yield std::tuple<char_t, trie_node<char_t>*>(c, pt);
	}

	static std::experimental::generator<std::tuple<char_t, trie_node*, trie_node*>>
		double_recurse(trie_node& t1, trie_node& t2)
	{
		for (auto const&[c, pt] : t1.children)
		{
			auto find = t2.children.find(c);
			if (find != t2.children.end())
				co_yield std::tuple<char_t, trie_node*, trie_node*>(c, pt, find->second);
		}
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

template <typename char_t, typename string_t = std::basic_string<char_t>>
std::vector<string_t> find_palindromes(std::vector<string_t>& words, int max_length)
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
	std::vector<string_t> results;
	trie_walker<char_t> tw(&root), twi(&rooti);
	recurse_tries(tw, twi, results, max_length);
	return results;
}

template <typename char_t, typename string_t = std::basic_string<char_t>>
struct trie_walker
{
	trie_node<char_t> *p_root, *p_node;
	std::basic_string<char_t> st;

	bool at_root()
	{
		return p_root == p_node;
	}

	trie_walker(trie_node<char_t> *p_root) : p_root(p_root), p_node(p_root) { }

	string_t last_word_backwads()
	{
		auto iter = std::find(st.rbegin(), st.rend(), char_t(' '));
		
		string_t ret(st.rbegin(), iter);
		return ret;
	}

	void move_forward(char_t c, trie_node<char_t> *p)
	{
		if (p_root == p_node && !st.empty())
			st += ' ';
		
		st += c;
		p_node = p;
	}

	void move_back(trie_node<char_t> *p)
	{
		p_node = p;
		st.pop_back();

		if (p_root == p_node && !st.empty())
			st.pop_back();
	}
};

template <typename char_t, typename string_t = std::basic_string<char_t>>
void recurse_tries(trie_walker<char_t>& tw, trie_walker<char_t>& twi, std::vector<string_t>& results, unsigned int max_length)
{
	// Both at word ends
	if (tw.at_root() && twi.at_root() && !tw.st.empty())
	{
		string_t post = twi.st;
		std::reverse(post.begin(), post.end());
		string_t result = tw.st + char_t(' ') + post;
		results.push_back(result);
	}
	// Both midword
	else if (!tw.at_root() && !twi.at_root())
	{
		if (twi.p_node->traverse(tw.last_word_backwads()))
		{
			string_t post = twi.st;
			std::reverse(post.begin(), post.end());
			string_t result = tw.st + post;
			results.push_back(result);
		}
	}
	
	for (auto[c, pn] : twi.p_node->recurse())
	{
		auto ptr = pn->traverse(tw.last_word_backwads());
		if (ptr != nullptr && ptr->is_root())
		{
			string_t pre = tw.st;
			if (tw.at_root())
				pre += char_t(' ');

			string_t post = twi.st;
			std::reverse(post.begin(), post.end());

			string_t result = pre + c + post;
			results.push_back(result);
		}
	}

	if (tw.st.length() > max_length)
		return;

	for (auto[c, pt, pti] : trie_node<char_t>::double_recurse(*tw.p_node, *twi.p_node))
	{
		// Store pointers
		auto p = tw.p_node;
		auto pi = twi.p_node;

		tw.move_forward(c, pt);
		twi.move_forward(c, pti);

		recurse_tries(tw, twi, results, max_length);
		
		tw.move_back(p);
		twi.move_back(pi);
	}
}
