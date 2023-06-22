#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"
#include <fstream>
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool checkVectors(vector<vector<int>>& expected_vector, vector<vector<int>>& real_vector) {
	for (int i = 0; i < expected_vector[0].size(); i++) {
		for (int j = 0; j < expected_vector[0].size(); j++) {
			if (expected_vector[i][j] != real_vector[i][j]) {
				return false;
			}
		}
	}
	return true;
}

namespace readRoadsTabletests
{
	TEST_CLASS(readRoadsTabletests)
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
			vector<vector<int>> matrixRoads;
			string filePath = (string(TEST_CASE_DIRECTORY) + "typical.csv");
			vector<vector<int>> expectedMatrixRoads = { {0, 1, 2},{1, 0, 2},{1,2,0} };
			matrixRoads.resize(expectedMatrixRoads.size());
			bool isException = false;
			try {
				readRoadsTable(filePath, matrixRoads);
			}
			catch (const InvalidInputFileException& e)
			{
				isException = true;
			}
			catch (const InvalidValueException& e) {
				isException = true;
			}		

			Assert::IsTrue(checkVectors(expectedMatrixRoads, matrixRoads));

		}

		TEST_METHOD(emptyStrings)
		{
			vector<vector<int>> matrixRoads;
			string filePath = (string(TEST_CASE_DIRECTORY) + "empty.csv");
			vector<vector<int>> expectedMatrixRoads = { {0, 1, 2},{1, 0, 2},{1,2,0} };
			matrixRoads.resize(expectedMatrixRoads.size());
			bool isException = false;
			try {
				readRoadsTable(filePath, matrixRoads);
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
		
		TEST_METHOD(extraStrings)
		{
			vector<vector<int>> matrixRoads;
			string filePath = (string(TEST_CASE_DIRECTORY) + "extrastring.csv");
			vector<vector<int>> expectedMatrixRoads = { {0, 1, 2},{1, 0, 2},{1,2,0} };
			matrixRoads.resize(expectedMatrixRoads.size());
			bool isException = false;
			try {
				readRoadsTable(filePath, matrixRoads);
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
