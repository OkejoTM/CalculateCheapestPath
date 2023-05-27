/*!
 * \file
 * \brief Функции, необходимые для работы с выражениями программы
 *
 * Данный файл содержит функции программы
*/

#pragma once
#include <string>
#include <vector>
using namespace std;
 

/*! 
* \brief Проверяет, что строка состоит только из цифр.
* \param[in] str - строка
* \return – результат проверки
*/
bool checkStringIsDigit(const std::string str);

/*! 
* \brief Проверяет, что строка состоит только из пробелов.
* \param[in] str - строка
* \return – результат проверки
*/
bool onlySpaces(const std::string str);

/*! 
* \brief Заполняет вектор данными из строки
* \param[in] line - строка, данные которой записаны через разделитель
* \param[in/out] filledVector - заполняемый вектор
* \param[in] delimeter - разделитель
* \throw InvalidValueException - пустая строка
* \throw InvalidInputFileException - значением таблицы не является неотрицательное целое число
*/
void fillLineInVector(const string line, vector<int>& filledVector, const char delimeter);

/*! 
* \brief Валидация таблиц
* \param[in] costs - вектор стоимостей 1 литра бензина
* \param[in] roads - таблица дорог
* \throw InvalidInputFileException - количество городов в таблицах не одинаковое
* \throw InvalidInputFileException - количество дорог не соответствует количеству городов
* \throw InvalidValueException - обнаружена петля
* \throw InvalidValueException - обнаружена односторонняя дорога
*/
void tablesValidation(const vector<int>& costs, const vector<vector<int>>& roads);

/*! 
* \brief Считать таблицу стоимостей 1 литра бензина
* \param[in] inputFilePath - строка, содержащая путь к файлу
* \param[in/out] costs - заполняемый вектор стоимостей 1 литра бензина
* \throw InvalidInputFileException - обнаружены пустые строки в файле
*/
void readCostsTable(const string& inputFilePath, vector<int>& costs);

/*! 
* \brief Считать таблицу дорог
* \param[in] inputFilePath - строка, содержащая путь к файлу
* \param[in/out] roads - заполняемый двумерный вектор дорог
* \throw InvalidInputFileException - обнаружены пустые строки в файле
* \throw InvalidInputFileException - количество городов в таблицах не одинаковое
*/
void readRoadsTable(const string& inputFilePath, vector<vector<int>>& roads);

/*! 
* \brief Перемножает значения стоимостей литра бензина с соответствующими дорогами
* \param[in\out] roads - матрица дорог.
* \param[in] costs - вектор стоимостей литра бензина в городах
*/
void multiplyCostsAndRoads(vector<vector<int>>& roads, const vector<int>& costs);

/*! 
* \brief Найти самый дешевый путь из первого города в последний
* \param[in] roads - матрица смежности.
* \param[in] source - первоначальная вершина.
* \throw InvalidValueException - количество городов меньше 1
* \return - Минимальная стоимость из первого города в последний
*/
int calculateCheapestPath(const vector<vector<int>>& roads, int source);
