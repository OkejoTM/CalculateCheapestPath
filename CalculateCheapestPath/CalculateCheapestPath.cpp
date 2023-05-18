#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <exception>

using namespace std;

class InvalidInputFileException : public std::exception {
public:
	InvalidInputFileException(const std::string& message) : m_message(message) {}

	const char* what() const noexcept override {
		return m_message.c_str();
	}
private:
	std::string m_message;
};

class InvalidValueException : public std::exception {
public:
	InvalidValueException(const std::string& message) : m_message(message) {}

	const char* what() const noexcept override {
		return m_message.c_str();
	}
private:
	std::string m_message;
};

/*! Проверяет, что строка состоит только из цифр.
* \param[in] str - строка
* \return – результат проверки
*/
bool checkStringIsDigit(const std::string str) {
	int i = 0; int c = 0;
	for (; i < str.size(); i++) {
		// Если текущим значением не является цифра - вернуть false
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
		// Если текущим значением является 0 и это первое значение строки
		if (str[i] == '0' && i == 0) {
			c++; // Увеличить количество 0
		}
	}
	if (c == 1 && i == c) return true; // Если значение является цифрой 0 - вернуть true;
	else if (c == 1) return false; // Если значение начинается с 0, но не является цифрой 0 - вернуть false
	if (i == 0) return false; // Если значение пустое - вернуть false
	return true;
}

/*! Проверяет, что строка состоит только из пробелов.
* \param[in] str - строка
* \return – результат проверки
*/
bool onlySpaces(const std::string str) {
	// Для каждого элемента стрроки
	for (char ch : str) {
		if (ch != ' ') { // Если элемент не является пробелом
			return false; // Вернуть false
		}
	}
	return true; // Вернуть true
}

/*! Заполнить вектор данными из строки
* param[in] line - строка
* param[in/out] filledVector - заполняемый вектор
*/
void fillLineInVector(const string line, vector<int>& filledVector) 
{
	stringstream ss(line); // Загрузить строку в поток
	string costVal;

	// Спарсить стоимости дорог в вектор
	while (std::getline(ss, costVal, ';')) {
		bool isDigit = checkStringIsDigit(costVal); // Проверка, что строка содержит только цифры.		

		if (isDigit) {
			filledVector.push_back(stoi(costVal));
		}
		else {
			throw InvalidInputFileException("Неправильная запись входных данных. " "Убедитесь, что значением таблицы является неотрицательное число.\n");
		}
	}
}

/*! Валидация таблиц
* param[in] costs - вектор стоимостей 1 литра бензина
* param[in] roads - таблица дорог
*/
void tablesValidation(const vector<int> costs, const vector<vector<int>> roads) 
{
	// Проверить размерности таблиц
	if (roads.size() != costs.size()) {
		throw InvalidInputFileException("Неправильная запись входных данных. "
			"Убедитесь, что количество городов в таблицах одинаково.\n");
	}
	for (int i = 0; i < roads.size(); i++) {
		if (roads[i].size() != costs.size()) {
			throw InvalidInputFileException("Неправильная запись входных данных. "
				"Убедитесь, что количество городов в таблицах одинаково.\n");
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

/*! Считать таблицу стоимостей 1 литра бензина
* param[in] inputFilePath - строка, содержащая путь к файлу
* param[in/out] costs - заполняемый вектор стоимостей 1 литра бензина
*/
void readCostsTable(const string& inputFilePath, vector<int>& costs)
{
	ifstream file(inputFilePath); // Открыть файл с таблицей стоимостей 1 литра бензина

	// Считать строку файла
	string line;
	std::getline(file, line);
	if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");

	// Спарсить стоимости дорог в вектор
	fillLineInVector(line, costs);	
}

/*! Считать таблицу дорог
* param[in] inputFilePath - строка, содержащая путь к файлу
* param[in/out] roads - заполняемый двумерный вектор дорог
*/
void readRoadsTable(const string& inputFilePath, vector<vector<int>>& roads) 
{	
	ifstream file(inputFilePath); // Открыть файл с таблицей городов

	int i = 0;
	// Пока есть строки в файле
	string line;
	while (std::getline(file, line))
	{
		// Если строка пустая - выдать исключение
		if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
		//
		if (i == roads.size()) {
			throw InvalidInputFileException("Неправильная запись входных данных. "
				"Убедитесь, что количество городов в таблицах одинаково.\n");
		}

		fillLineInVector(line, roads[i]);
		i++;
	}
}


/*! Перемножает значения стоимостей литра бензина с соответствующими дорогами
* \param[in\out] roads - матрица дорог.
* \param[in] costs - вектор стоимостей литра бензина в городах
*/
void multiplyCostsAndRoads(vector<vector<int>>& roads, vector<int>& costs) 
{
	// Для каждого элемента i до последнего
	for (int i = 0; i < costs.size(); i++) {
		// Для каждого элемента j начиная с i до последнего
		for (int j = i; j < costs.size(); j++) {
			// Перемножить симметричные значения матрицы дорог с соответствующими значениями стоимости бензина в городах, относительно главной диагонали
			roads[i][j] = roads[i][j] * costs[i]; 
			roads[j][i] = roads[j][i] * costs[j];												
		}
	}
}

/*! Найти самый дешевый путь из первого города в последний
* \param[in] roads - матрица смежности.
* \param[in] source - первоначальная вершина.
* \return - Минимальная стоимость из первого города в последний
*/
int findCheapestPath(vector<vector<int>> roads, int source) 
{
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
		std::cerr << "Неправильно указаны параметры запуска. "
			"Убедитесь, что параметры соотвествуют шаблону: \n"
			<< argv[0] << " <path/to/input_file1> <path/to/input_file2> <path/to/save_file>\n";
		return 1;
	}
	
	std::ifstream costsInputFile(argv[1]);

	if (!costsInputFile.is_open()) {
		std::cerr << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[1] << '\n';
		return 1;
	}

	std::ifstream roadsInputFile(argv[2]);

	if (!roadsInputFile.is_open()) {
		std::cerr << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[2] << '\n';
		return 1;
	}
	
	filesystem::path outputPath = filesystem::path(argv[3]);

	if (!(filesystem::exists(outputPath.parent_path()) &&
		filesystem::is_directory(outputPath.parent_path()) &&
		outputPath.has_filename()))
	{
		std::cerr << "Неверно указан файл для выходных данных. "
			"Возможно указанного расположения не существует или нет прав на запись." << '\n';
		return 1;
	}

	std::ofstream outputFile(outputPath);

	if (!outputFile.is_open()) {
		std::cerr << "Неверно указан файл для выходных данных. "
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
		std::cerr << e.what();
		return 1;
	}
	catch (const InvalidValueException& e) {
		std::cerr << e.what();
		return 1;
	}
	
	outputFile << findCheapestPath(matrixRoads, 0);

	costsInputFile.close();
	roadsInputFile.close();
	outputFile.close();

	return 0;
}