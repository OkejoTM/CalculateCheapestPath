#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace onlySpacestests
{
	TEST_CLASS(onlySpacestests)
	{
	public:
		
		TEST_METHOD(Typical)
		{
			string checkedString = "   ";
			bool expected_result = true;
			bool real_result = onlySpaces(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(EmptyString)
		{
			string checkedString = "";
			bool expected_result = true;
			bool real_result = onlySpaces(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(OnlySpaces)
		{
			string checkedString = " ";
			bool expected_result = true;
			bool real_result = onlySpaces(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(OneSymbolNotSpace)
		{
			string checkedString = "3";
			bool expected_result = false;
			bool real_result = onlySpaces(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(OnySymbolBetweenSpaces)
		{
			string checkedString = "   o  ";
			bool expected_result = false;
			bool real_result = onlySpaces(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(StringDontContainSpaces)
		{
			string checkedString = "1231rfas";
			bool expected_result = false;
			bool real_result = onlySpaces(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}
	};
}
