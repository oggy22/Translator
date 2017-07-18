#include "stdafx.h"

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "Languages\English.h"
#include "Languages\Serbian.h"

void set_wide()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
}

int main()
{
	using SourceLanguage = Serbian;

	using namespace std;

	cout << "Input a sentence:" << endl;
	SourceLanguage::string_t text = L"ја читам";
	set_wide();
	bool success = translator::parse<SourceLanguage>(text);
	wcout << text << endl;
	wcout << (success ? "Success" : "Fail") << endl;
	return 0;
}