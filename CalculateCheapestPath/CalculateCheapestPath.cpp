#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <queue>
#include "CalculateCheapestPath.h"
#include "Exceptions.h" 
 
using namespace std;

bool checkStringIsDigit(const std::string& str)
{
	if (str.empty())
		return false;
	
	if (str[0] == '0') {
		// Если строка состоит только из цифр
		if (str.find_first_of('0') == str.size() - 1) {
			return true;
		}
		else {
			return false;
		}
	}

	for (char symbol : str) {
		if (symbol < '0' ||  symbol> '9') {
			return false;
		}
	}

	return true;
}

bool onlySpaces(const std::string str) {
	// Для каждого элемента стрроки
	for (char ch : str) {
		if (ch != ' ') { // Если элемент не является пробелом
			return false; // Вернуть false
		}
	}
	return true; // Вернуть true
}

void fillLineInVector(const string line, vector<int>& filledVector, const char delimeter) 
{
	// Если размер строки меньше 1 - выдать исключение
	if (line.size() < 1) {
		throw InvalidValueException("Неверная запись строки. "
			"Убедитесь, что строка не пустая.\n");
	}
	stringstream ss(line); // Загрузить строку в поток
	string costVal;
	int col = 0;
	// Пока в строке есть разделители
	while (std::getline(ss, costVal, delimeter)) {
		bool isDigit = checkStringIsDigit(costVal); // Проверка, что строкой является неотрицательное число.		
		col++;
		// Если элементом является число
		if (isDigit) {
			filledVector.push_back(stoi(costVal)); // добавить элемент в вектор
		}
		else {
			string exceptionString = "Неверная запись входных данных. Убедитесь, что значением колонки " + to_string(col) + " является неотрицательное число.\n";
			throw InvalidInputFileException(exceptionString);
		}
	}
}

void tablesValidation(const vector<int>& costs, const vector<vector<int>>& roads) 
{
	// Проверить размерности таблиц
	if (roads.size() != costs.size()) {
		throw InvalidInputFileException("Неверная запись входных данных. "
			"Убедитесь, что количество городов в таблицах одинаково.\n");
	}
	for (int i = 0; i < roads.size(); i++) {
		if (roads[i].size() != costs.size()) {
			throw InvalidInputFileException("Неверная запись входных данных. "
				"Убедитесь, что количество дорог равно количеству городов..\n");
		}
	}

	// Проверить значения таблицы
	for (int i = 0; i < roads.size(); i++){
		for (int j = i; j < roads.size(); j++) {
			int first = roads[i][j];
			int second = roads[j][i];
			// Выдать ошбику, если обнаружена петля
			if (i == j && first != 0)
			{
				throw InvalidValueException("Не может быть петли. "
					"Убедитесь, что схема дорог города не содержит дорог, которые соединяют один и тот же город.\n");
			}
			// Выдать ошбику, если обнаружена односторонняя дорога.
			if ((first == 0 && second != 0) || (first != 0 && second == 0)) {
				throw InvalidValueException("Дороги могут быть только двусторонними. "
					"Убедитесь, что существуют оба пути между городами.\n");
			}
		}
	}
}

void readCostsTable(const string& inputFilePath, vector<int>& costs)
{
	ifstream file(inputFilePath); // Открыть файл с таблицей стоимостей 1 литра бензина

	// Считать строку файла
	string line;
	std::getline(file, line);
	if (onlySpaces(line)) throw InvalidInputFileException("Неверная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");

	// Спарсить стоимости дорог в вектор
	fillLineInVector(line, costs, ';');
}

void readRoadsTable(const string& inputFilePath, vector<vector<int>>& roads) 
{	
	ifstream file(inputFilePath); // Открыть файл с таблицей городов

	// Считать количество строк файла = 0
	int i = 0;
	// Пока есть строки в файле
	string line;
	while (std::getline(file, line))
	{
		// Если строка пустая - выдать исключение
		if (onlySpaces(line)) throw InvalidInputFileException("Неверная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
		// Если количество строк
		if (i == roads.size()) {
			throw InvalidInputFileException("Неверная запись входных данных. "
				"Убедитесь, что количество городов в таблицах одинаково.\n");
		}

		// Заполнить вектор значениями из строки
		fillLineInVector(line, roads[i], ';');
		// Увеличить индекс текущей строки
		i++;
	}
}

void multiplyCostsAndRoads(vector<vector<int>>& roads, const vector<int>& costs) 
{
	// Для каждого элемента i до последнего
	for (int i = 0; i < costs.size(); i++) {
		// Для каждого элемента j начиная с i до последнего
		for (int j = i; j < costs.size(); j++) {
			// Если перемножается диагональные значения
			if (i == j) 
			{
				roads[i][j] = roads[i][j] * costs[i]; // Перемножить 1 раз;
			}
			else // Иначе
			{
				// Перемножить симметричные значения матрицы дорог с соответствующими значениями стоимости бензина в городах, относительно главной диагонали
				roads[i][j] = roads[i][j] * costs[i]; 
				roads[j][i] = roads[j][i] * costs[j];												
			}
		}
	}
}

int calculateCheapestPath(const vector<vector<int>>& roads, int source) 
{
	// Если количество городов меньше единицы - выдать исключение
	if (roads.size() < 1) {
		throw InvalidValueException("Неверная запись входных данных. "
			"Убедитесь, что количество городов больше 0.\n");
	}
	// Инициализировать все растояния как бесконечные, кроме исходной
	vector<int> distances(roads[0].size(), INT_MAX);
	distances[source] = 0;

	// Поместить исходную вершину в приоитетную очередь
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQueue;
	pQueue.push(make_pair(0, source));

	// Пока остались вершины, расстояние до которых можно уменьшить
	while (!pQueue.empty()) {
		
		// Получить вершину с наименьшим расстоянием и удалить ее с очереди
		int u = pQueue.top().second;
		pQueue.pop();

		// Для каждой вершины 
		for (int v = 0; v < roads[0].size(); v++) {
			// Если можно произвести уменьшение расстояния до вершины
			if (roads[u][v] != 0 && distances[v] > distances[u] + roads[u][v]) {
				distances[v] = distances[u] + roads[u][v]; // Вычислить минимальное растояние до вершины
				pQueue.push(make_pair(distances[v], v)); // Добавить в очередь растояние до вершины и саму вершину
			}
		}
	}
	// Вернуть растояние до последней вершины
	return distances.back();
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");	

	vector<vector<int>> matrixRoads;
	vector<int> costs;

	if (argc != 4)
	{
		std::cout << "Неправильно указаны параметры запуска. "
			"Убедитесь, что параметры соотвествуют шаблону: \n"
			<< argv[0] << " <path/to/input_file1> <path/to/input_file2> <path/to/save_file>\n";
		return 1;
	}
	
	std::ifstream costsInputFile(argv[1]);

	if (!costsInputFile.is_open()) {
		std::cout << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[1] << '\n';
		return 1;
	}

	std::ifstream roadsInputFile(argv[2]);

	if (!roadsInputFile.is_open()) {
		std::cout << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[2] << '\n';
		return 1;
	}
	
	filesystem::path outputPath = filesystem::path(argv[3]);

	if (!(filesystem::exists(outputPath.parent_path()) &&
		filesystem::is_directory(outputPath.parent_path()) &&
		outputPath.has_filename()))
	{
		std::cout << "Неверно указан файл для выходных данных. "
			"Возможно указанного расположения не существует или нет прав на запись." << '\n';
		return 1;
	}

	std::ofstream outputFile(outputPath);

	if (!outputFile.is_open()) {
		std::cout << "Неверно указан файл для выходных данных. "
			"Возможно указанного расположения не существует или нет прав на запись." << '\n';
		return 1;
	}
	
	try
	{			
		// Считать входные данные
		readCostsTable(argv[1], costs);
		matrixRoads.resize(costs.size());
		readRoadsTable(argv[2], matrixRoads);
		tablesValidation(costs, matrixRoads);

		// Преобразовать дороги и стоимости в матрицу смежности
		multiplyCostsAndRoads(matrixRoads, costs);
				
	}
	catch (const InvalidInputFileException& e)
	{
		std::cout << e.what();
		return 1;
	}
	catch (const InvalidValueException& e) {
		std::cout << e.what();
		return 1;
	}
	
	outputFile << calculateCheapestPath(matrixRoads, 0);

	costsInputFile.close();
	roadsInputFile.close();
	outputFile.close();

	return 0;
}