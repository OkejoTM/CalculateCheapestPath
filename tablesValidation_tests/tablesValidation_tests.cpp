#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculateCheapestPath/CalculateCheapestPath.h"
#include "../CalculateCheapestPath/Exceptions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tablesValidationtests
{
	TEST_CLASS(tablesValidationtests)
	{
	public:
		
		TEST_METHOD(MatrixContainsLoop)
		{
			vector<int> costs = {1,2,3};
			vector<vector<int>> roads = { {0,1,2,},{3,10,4},{5,6,0} };
			try {
				tablesValidation(costs, roads);
				Assert::Fail(L"Expected exception not thrown.");
			}			
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(MatrixContainsOneWayPath)
		{
			vector<int> costs = { 1,2,3 };
			vector<vector<int>> roads = { {0,1,2,},{0,0,4},{5,6,0} };
			try {
				tablesValidation(costs, roads);
				Assert::Fail(L"Expected exception not thrown.");
			}			
			catch (const InvalidValueException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(RoadsContainsMoreCitiesThanCosts)
		{
			vector<int> costs = { 1,2,3 };
			vector<vector<int>> roads = { {0,1,2,3},{3,0,1,2},{3,2,0,1},{3,2,1,0} };
			try {
				tablesValidation(costs, roads);
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

		TEST_METHOD(RoadsContainsLessCitiesThanCosts)
		{
			vector<int> costs = { 1,2,3,4,5 };
			vector<vector<int>> roads = { {0,1,2,3},{3,0,1,2},{3,2,0,1},{3,2,1,0} };
			try {
				tablesValidation(costs, roads);
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

		TEST_METHOD(CountPathesInRoadsMoreThanCities)
		{
			vector<int> costs = { 1,2,3 };
			vector<vector<int>> roads = { {0,3,1,5},{3,0,1},{3,2,0}};
			try {
				tablesValidation(costs, roads);
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

		TEST_METHOD(CountPathesInRoadsLessThanCities)
		{
			vector<int> costs = { 1,2,3 };
			vector<vector<int>> roads = { {0,3},{3,0,1},{3,2,0} };
			try {
				tablesValidation(costs, roads);
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
