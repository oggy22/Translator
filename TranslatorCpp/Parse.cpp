#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "Languages\Serbian.h"

void set_wide();

int main()
{
	using SourceLanguage = Serbian;

	using namespace std;
	SourceLanguage source;

	cout << "Input a sentence:" << endl;
	SourceLanguage::string_t text = L"ја читам";
	set_wide();
	bool success = translator::parse(source, text);
	wcout << text << endl;
	wcout << (success ? "Success" : "Fail") << endl;
	return 0;
}