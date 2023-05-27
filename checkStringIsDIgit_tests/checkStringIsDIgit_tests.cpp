#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace checkStringIsDIgittests
{
	TEST_CLASS(checkStringIsDIgittests)
	{
	public:
		
		TEST_METHOD(Typical)
		{
			string checkedString = "30";
			bool expected_result = true;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(EmptyString)
		{
			string checkedString = "";
			bool expected_result = false;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(StringIsNumberZero)
		{
			string checkedString = "0";
			bool expected_result = true;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(StartsWithZero)
		{
			string checkedString = "023";
			bool expected_result = false;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(StringIsNegativeDigit)
		{
			string checkedString = "-123";
			bool expected_result = false;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(SpaceBetweenDigits)
		{
			string checkedString = "1 3";
			bool expected_result = false;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(SpaceBeforeDigit)
		{
			string checkedString = " 123";
			bool expected_result = false;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(SpaceAfterDigit)
		{
			string checkedString = "32 ";
			bool expected_result = false;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}

		TEST_METHOD(HexFormDigit)
		{
			string checkedString = "1A";
			bool expected_result = false;
			bool real_result = checkStringIsDigit(checkedString);
			Assert::AreEqual((int)expected_result, (int)real_result);
		}
	};
}
