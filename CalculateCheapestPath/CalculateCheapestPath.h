/*!
 * \file
 * \brief ‘ункции, необходимые дл€ работы с выражени€ми программы
 *
 * ƒанный файл содержит функции программы
*/

#pragma once
#include <string>
#include <vector>
using namespace std;


/*! 
* \brief ѕровер€ет, что строка состоит только из цифр.
* \param[in] str - строка
* \return Ц результат проверки
*/
bool checkStringIsDigit(const std::string str);

/*! 
* \brief ѕровер€ет, что строка состоит только из пробелов.
* \param[in] str - строка
* \return Ц результат проверки
*/
bool onlySpaces(const std::string str);

/*! 
* \brief «аполн€ет вектор данными из строки
* \param[in] line - строка, данные которой записаны через разделитель
* \param[in/out] filledVector - заполн€емый вектор
* \param[in] delimeter - разделитель
* \throw InvalidValueException - пуста€ строка
* \throw InvalidInputFileException - значением таблицы не €вл€етс€ неотрицательное целое число
*/
void fillLineInVector(const string line, vector<int>& filledVector, const char delimeter);

/*! 
* \brief ¬алидаци€ таблиц
* \param[in] costs - вектор стоимостей 1 литра бензина
* \param[in] roads - таблица дорог
* \throw InvalidInputFileException - количество городов в таблицах не одинаковое
* \throw InvalidInputFileException - количество дорог не соответствует количеству городов
* \throw InvalidValueException - обнаружена петл€
* \throw InvalidValueException - обнаружена односторонн€€ дорога
*/
void tablesValidation(const vector<int>& costs, const vector<vector<int>>& roads);

/*! 
* \brief —читать таблицу стоимостей 1 литра бензина
* \param[in] inputFilePath - строка, содержаща€ путь к файлу
* \param[in/out] costs - заполн€емый вектор стоимостей 1 литра бензина
* \throw InvalidInputFileException - обнаружены пустые строки в файле
*/
void readCostsTable(const string& inputFilePath, vector<int>& costs);

/*! 
* \brief —читать таблицу дорог
* \param[in] inputFilePath - строка, содержаща€ путь к файлу
* \param[in/out] roads - заполн€емый двумерный вектор дорог
* \throw InvalidInputFileException - обнаружены пустые строки в файле
* \throw InvalidInputFileException - количество городов в таблицах не одинаковое
*/
void readRoadsTable(const string& inputFilePath, vector<vector<int>>& roads);

/*! 
* \brief ѕеремножает значени€ стоимостей литра бензина с соответствующими дорогами
* \param[in\out] roads - матрица дорог.
* \param[in] costs - вектор стоимостей литра бензина в городах
*/
void multiplyCostsAndRoads(vector<vector<int>>& roads, const vector<int>& costs);

/*! 
* \brief Ќайти самый дешевый путь из первого города в последний
* \param[in] roads - матрица смежности.
* \param[in] source - первоначальна€ вершина.
* \throw InvalidValueException - количество городов меньше 1
* \return - ћинимальна€ стоимость из первого города в последний
*/
int calculateCheapestPath(const vector<vector<int>>& roads, int source);
