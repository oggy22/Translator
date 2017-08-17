#pragma once
template <class Char>
std::wostream& operator<<(std::wostream &wout, const translator::pattern<Char>& pt)
{
	pt.printw(wout);
	return wout;
}

template <class Language>
std::wostream& operator<<(std::wostream &wout, const translator::word_rule<Language>& wr)
{
	wout << L"'" << wr.source << L"'->'" << wr.destination << L"' " << wr.wt;
	return wout;
}