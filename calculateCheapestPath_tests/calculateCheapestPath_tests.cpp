#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace calculateCheapestPathtests
{
	TEST_CLASS(calculateCheapestPathtests)
	{
	public:
		
		TEST_METHOD(Typical)
		{
			vector<vector<int>> roads = { {0,4,5,4,10},{2,0,4,3,2},{1,4,0,0,4},{2,4,0,0,8},{1,1,3,5,0} };
			int source = 0;
			int expected_output = 6;
			int real_output;
			real_output = calculateCheapestPath(roads, source);
			Assert::AreEqual(expected_output, real_output);
		}

		TEST_METHOD(EmptyVector)
		{
			vector<vector<int>> roads = {};
			int source = 0;
			int expected_output = 0;
			int real_output;
			try {
				real_output = calculateCheapestPath(roads, source);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputFileException & ex) {
				
			}
			catch (const InvalidValueException& ex) {
				
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(OneElementInVector)
		{
			vector<vector<int>> roads = { {2} };
			int source = 0;
			int expected_output = 0;
			int real_output;
			real_output = calculateCheapestPath(roads, source);
			Assert::AreEqual(expected_output, real_output);
		}

		TEST_METHOD(FromFirstToLast)
		{
			vector<vector<int>> roads = { {0,1,2},{2,0,3},{4,5,0} };
			int source = 0;
			int expected_output = 2;
			int real_output;
			real_output = calculateCheapestPath(roads, source);
			Assert::AreEqual(expected_output, real_output);
		}

		TEST_METHOD(FromMiddleToLast)
		{
			vector<vector<int>> roads = { {0,1,2},{2,0,3},{4,5,0} };
			int source = 1;
			int expected_output = 3;
			int real_output;
			real_output = calculateCheapestPath(roads, source);
			Assert::AreEqual(expected_output, real_output);
		}		

		TEST_METHOD(FromLastToLast)
		{
			vector<vector<int>> roads = { {0,1,2},{2,0,3},{4,5,0} };
			int source = 2;
			int expected_output = 0;
			int real_output;
			real_output = calculateCheapestPath(roads, source);
			Assert::AreEqual(expected_output, real_output);
		}

		TEST_METHOD(AllPathsEqual)
		{
			vector<vector<int>> roads = { {0,2,5},{1,0,3},{1,1,0} };
			int source = 0;
			int expected_output = 5;
			int real_output;
			real_output = calculateCheapestPath(roads, source);
			Assert::AreEqual(expected_output, real_output);
		}

	};
}
