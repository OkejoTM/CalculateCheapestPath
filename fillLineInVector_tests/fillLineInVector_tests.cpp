#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool checkVectors(const vector<int>& expected_vector, const vector<int>& real_vector)
{
	for (int i = 0; i < expected_vector.size(); i++) {
		if (expected_vector[i] != real_vector[i]) return false;
	}
}

namespace fillLineInVectortests
{
	TEST_CLASS(fillLineInVectortests)
	{
	public:
		
		TEST_METHOD(Typical)
		{
			string line = "3;1;2;0;";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = { 3,1,2,0 };
			fillLineInVector(line, real_vector, delimeter);
			Assert::IsTrue(checkVectors(expected_vector, real_vector));
		}

		TEST_METHOD(EmptyLine)
		{
			string line = "";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {};						
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}			
		}

		TEST_METHOD(ElementsInVectorIsLetters)
		{
			string line = "a;b;d;c";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(firstElemntIsEmpty)
		{
			string line = ";3;2;1";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(ElementsAreLettersWithDigits)
		{
			string line = "af3;d4;12";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(ElementsAreDigitsStartedWithZeros)
		{
			string line = "003;1;2;3;";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(LineContainsNegativeDigits)
		{
			string line = "-4;1;3";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(AllElemntsAreZerosButOne)
		{
			string line = "0;0;0;1";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {0,0,0,1};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::IsTrue(checkVectors(expected_vector, real_vector));
				
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(OneElements)
		{
			string line = "3";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {3};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::IsTrue(checkVectors(expected_vector, real_vector));
				
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(LineContainsOnlyDelimeters)
		{
			string line = ";;;;";
			char delimeter = ';';
			vector<int> real_vector;
			vector<int> expected_vector = {};
			try {
				fillLineInVector(line, real_vector, delimeter);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException& ex) {
			}
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		



	};
}
