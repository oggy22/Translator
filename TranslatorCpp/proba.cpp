#include <iostream>
#include <algorithm>
#include <string>
#include "windows.h"

using namespace std;

int main()
{
	while (true)
	{
		string s;
		cin >> s;
		reverse(s.begin(), s.end());
		cout << s << endl;
		//Sleep(1000);
	}
}