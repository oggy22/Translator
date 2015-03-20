#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "language.h"
#include "Serbian.h"
#include "English.h"

int main2()
{
	using SourceLanguage = Serbian;
	using DestinationLanguage = English;

	using namespace std;
	SourceLanguage source;
	DestinationLanguage destination;

	//translator::translator trans(source, destination);
	translator::translator<SourceLanguage, DestinationLanguage> trans(source, destination);

	cout << "Input a sentence:" << endl;
	SourceLanguage::letters text;

	//std::getline(text);
	std::locale mylocale("");   // get global locale
	
	std::cout.imbue(mylocale);  // imbue global locale	cin >> text;
	DestinationLanguage::letters translation = trans.translate(text);
	cout << translation << endl;

	return 0;
}