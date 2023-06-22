#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool checkVectors(vector<int>& expected_vector, vector<int>& real_vector) {
	for (int i = 0; i < expected_vector.size(); i++) {
		if (expected_vector[i] != real_vector[i]) {
				return false;
			}
		
	}
	return true;
}

namespace readCostsTabletests
{
	TEST_CLASS(readCostsTabletests)
	{
	public:
		#define TEST_CASE_DIRECTORY get_directory_name(__FILE__)

		string get_directory_name(string path) {
			const size_t last_slash_idx = path.rfind('\\');
			if (std::string::npos != last_slash_idx)
			{
				return path.substr(0, last_slash_idx + 1);
			}
			return "";
		}

		TEST_METHOD(typical)
		{
			vector<int> costs;
			string filePath = (string(TEST_CASE_DIRECTORY) + "typical.csv");
			vector<int> expectedCosts = {0, 1, 2};			
			bool isException = false;
			try {
				readCostsTable(filePath, costs);
			}
			catch (const InvalidInputFileException& e)
			{
				isException = true;
			}
			catch (const InvalidValueException& e) {
				isException = true;
			}

			Assert::IsTrue(checkVectors(expectedCosts, costs));

		}

		TEST_METHOD(emptyStrings)
		{
			string filePath = (string(TEST_CASE_DIRECTORY) + "empty.csv");			
			vector<int> costs;
			bool isException = false;
			try {
				readCostsTable(filePath, costs);
			}
			catch (const InvalidInputFileException& e)
			{
				isException = true;
			}
			catch (const InvalidValueException& e) {
				isException = true;
			}

			Assert::IsTrue(isException);

		}

	};
}
