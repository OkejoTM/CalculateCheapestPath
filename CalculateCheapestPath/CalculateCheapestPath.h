/*!
 * \file
 * \brief �������, ����������� ��� ������ � ����������� ���������
 *
 * ������ ���� �������� ������� ���������
*/

#pragma once
#include <string>
#include <vector>
using namespace std;


/*! 
* \brief ���������, ��� ������ ������� ������ �� ����.
* \param[in] str - ������
* \return � ��������� ��������
*/
bool checkStringIsDigit(const std::string str);

/*! 
* \brief ���������, ��� ������ ������� ������ �� ��������.
* \param[in] str - ������
* \return � ��������� ��������
*/
bool onlySpaces(const std::string str);

/*! 
* \brief ��������� ������ ������� �� ������
* \param[in] line - ������, ������ ������� �������� ����� �����������
* \param[in/out] filledVector - ����������� ������
* \param[in] delimeter - �����������
* \throw InvalidValueException - ������ ������
* \throw InvalidInputFileException - ��������� ������� �� �������� ��������������� ����� �����
*/
void fillLineInVector(const string line, vector<int>& filledVector, const char delimeter);

/*! 
* \brief ��������� ������
* \param[in] costs - ������ ���������� 1 ����� �������
* \param[in] roads - ������� �����
* \throw InvalidInputFileException - ���������� ������� � �������� �� ����������
* \throw InvalidInputFileException - ���������� ����� �� ������������� ���������� �������
* \throw InvalidValueException - ���������� �����
* \throw InvalidValueException - ���������� ������������� ������
*/
void tablesValidation(const vector<int>& costs, const vector<vector<int>>& roads);

/*! 
* \brief ������� ������� ���������� 1 ����� �������
* \param[in] inputFilePath - ������, ���������� ���� � �����
* \param[in/out] costs - ����������� ������ ���������� 1 ����� �������
* \throw InvalidInputFileException - ���������� ������ ������ � �����
*/
void readCostsTable(const string& inputFilePath, vector<int>& costs);

/*! 
* \brief ������� ������� �����
* \param[in] inputFilePath - ������, ���������� ���� � �����
* \param[in/out] roads - ����������� ��������� ������ �����
* \throw InvalidInputFileException - ���������� ������ ������ � �����
* \throw InvalidInputFileException - ���������� ������� � �������� �� ����������
*/
void readRoadsTable(const string& inputFilePath, vector<vector<int>>& roads);

/*! 
* \brief ����������� �������� ���������� ����� ������� � ���������������� ��������
* \param[in\out] roads - ������� �����.
* \param[in] costs - ������ ���������� ����� ������� � �������
*/
void multiplyCostsAndRoads(vector<vector<int>>& roads, const vector<int>& costs);

/*! 
* \brief ����� ����� ������� ���� �� ������� ������ � ���������
* \param[in] roads - ������� ���������.
* \param[in] source - �������������� �������.
* \throw InvalidValueException - ���������� ������� ������ 1
* \return - ����������� ��������� �� ������� ������ � ���������
*/
int calculateCheapestPath(const vector<vector<int>>& roads, int source);
