#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "Languages\English.h"
#include "Languages\Serbian.h"

void testConio() {
	wchar_t buffer[0x1000];
	std::size_t numRead = 0;
	if (_cgetws_s(buffer, &numRead)) return;
	const std::wstring first(buffer, numRead);
	if (_cgetws_s(buffer, &numRead)) return;
	const std::wstring second(buffer, numRead);
	const std::wstring result = first + second + L'\n';
	_cputws(result.c_str());
}

int main5()
{
	using SourceLanguage = Serbian;
	using DestinationLanguage = English;

	using namespace std;
	SourceLanguage source;
	DestinationLanguage destination;

	//translator::translator trans(source, destination);
	//translator::translator<SourceLanguage, DestinationLanguage> trans(source, destination);

	cout << "Input a sentence:" << endl;
	SourceLanguage::string_t text;

	//std::getline(text);
	std::locale mylocale("");   // get global locale
	
	std::cout.imbue(mylocale);  // imbue global locale	cin >> text;
	DestinationLanguage::string_t translation /*= trans.translate(text)*/;
	cout << translation << endl;

	return 0;
}