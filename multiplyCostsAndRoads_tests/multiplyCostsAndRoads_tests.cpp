#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool checkVectors(const vector<vector<int>>& expected_matrix, const vector<vector<int>>& real_matrix)
{
	for (int i = 0; i < expected_matrix.size(); i++) {
		for (int j = 0; j < expected_matrix[0].size(); j++) {
			if (expected_matrix[i][j] != real_matrix[i][j]) return false;
		}
	}
}

namespace multiplyCostsAndRoadsAndRoadstests
{
	TEST_CLASS(multiplyCostsAndRoadsAndRoadstests)
	{
	public:
		
		TEST_METHOD(Typical)
		{
			vector<vector<int>> real_matrix = { {0,4,2,4,10},{2,0,4,3,2},{1,4,0,0,4},{2,4,0,0,2},{1,1,3,5,0} };
			vector<int> costs = { 2,4,6,8,10 };
			vector<vector<int>> expected_matrix = { {0,8,4,8,20},{8,0,16,12,8},{6,24,0,0,24},{16,32,0,0,16},{10,10,30,50,0} };
			multiplyCostsAndRoads(real_matrix, costs);
			Assert::IsTrue(checkVectors(expected_matrix, real_matrix)); // IsTrue(condition_, message_);	
		}

		TEST_METHOD(OneCity)
		{
			vector<vector<int>> real_matrix = { {5} };
			vector<int> costs = { 20 };
			vector<vector<int>> expected_matrix = { {100} };
			multiplyCostsAndRoads(real_matrix, costs);
			Assert::IsTrue(checkVectors(expected_matrix, real_matrix));
		}

		TEST_METHOD(TwoCity)
		{
			vector<vector<int>> real_matrix = { {0,2},{4,0} };
			vector<int> costs = { 2,4 };
			vector<vector<int>> expected_matrix = { {0,4},{16,0} };
			multiplyCostsAndRoads(real_matrix, costs);
			Assert::IsTrue(checkVectors(expected_matrix, real_matrix));
		}

		TEST_METHOD(ThreeCity)
		{
			vector<vector<int>> real_matrix = { {0,1,2},{3,0,4},{5,6,0} };
			vector<int> costs = { 1,2,3 };
			vector<vector<int>> expected_matrix = { {0,1,2},{6,0,8},{15,18,0} };
			multiplyCostsAndRoads(real_matrix, costs);
			Assert::IsTrue(checkVectors(expected_matrix, real_matrix));
		}
	};
}
