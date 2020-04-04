#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int main(int argc, char *argv[]);

namespace TranslatorTest
{
	TEST_CLASS(MainTests)
	{
		void Main(char* arg)
		{
			char *argv[] = { "main", arg };
			int code = main(2, argv);

			Assert::AreEqual(0, code);
		}

#ifdef _DEBUG
		TEST_METHOD(command_help)
		{
			Main("-help");
		}

		TEST_METHOD(command_list)
		{
			Main("-list:EN");
		}

		TEST_METHOD(command_translate)
		{
			Main("-translate:EN-SR");
		}
#endif

		TEST_METHOD(command_random)
		{
			Main("-random:SR");
		}
	};
}