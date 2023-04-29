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

vector<string> readDataFromFile(const std::string& inputFilePath, vector<vector<int>>& roads, vector<int>& costs)
{
	std::ifstream file(inputFilePath);

	// Считать первую строку файла
	string line;
	std::getline(file, line);
	stringstream ss(line);

	string label;
	vector<string> citiesLabes;


	// Заполнить вектор названиями городов
	while (std::getline(ss, label, ';')) {
		if (label != "") {
			citiesLabes.push_back(label);
		}
	}
	roads.resize(citiesLabes.size(), vector<int>(citiesLabes.size(), 0));
	costs.resize(citiesLabes.size(), 0);

	std::getline(file, line);
	ss.clear();
	ss.str(line);
	int costValueCol = 0;
	string costVal;

	// Считывание стоимости дорог
	while (std::getline(ss, costVal, ';')) {

		bool containsDigits = all_of(begin(costVal), end(costVal), isdigit); // Проверка, что строка содержит только цифры.
		if (costVal != "") {
			if (containsDigits) {
				costs[costValueCol] = stoi(costVal);
			}
			else {
				throw InvalidInputFileException("Неправильная запись стоимости за литр. "
					"Убедитесь, что стоимстость за литр является неотрицательным числом.\n");
			}
		}
		costValueCol++;
		if (costValueCol > citiesLabes.size()) {
			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
				"Убедитесь, что количество цен за стоимость бензина равно количеству городов\n");
		}
	}

	std::getline(file, line); // Считать пустую строку
	std::getline(file, line); // Считать названия город

	vector<string> matrixCitiesLabes;
	ss.clear();
	ss.str(line);
	// Заполнить вектор названиями городов
	while (std::getline(ss, label, ';')) {
		if (label != "") {
			matrixCitiesLabes.push_back(label);
		}
	}

	//заполнение матрицы смежности из файла
	int row = 0;
	while (std::getline(file, line)) {
		stringstream ss(line);
		string value;

		int col = 0;
		while (getline(ss, value, ';')) {
			bool valueContainsDigits = all_of(begin(value), end(value), isdigit); // Проверка, что строка содержит только цифры.

			if (col == 0 && citiesLabes[row] != value) {
				throw InvalidInputFileException("Названия города записаны неверно."
					"Убедитесь, что названия городов в таблице дорог соответствуют названиям городов со стоимостью бензина.\n");
			}
			else if (col == 0 && matrixCitiesLabes[row] != value) {
				throw InvalidInputFileException("Названия города несимметричны."
					"Убедитесь, что названия городов в таблице дорог записаны верно.\n");
			}

			if (value != "" && col > 0) {
				if (valueContainsDigits) {
					roads[row][col - 1] = stoi(value);
				}
				else {
					throw InvalidInputFileException("Неправильная запись задаваемого количества литров между городами. "
						"Убедитесь, что количество литров для дороги является неотрицательным числом.\n");
				}
			}

			col++;
			if (col > citiesLabes.size() + 1) {
				throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
					"Убедитесь, что количество цен за стоимость бензина равно количеству городов.\n");
			}
		}
		row++;
		if (row > citiesLabes.size()) {
			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
				"Убедитесь, что количество городов равны.\n");
		}
	}

	file.close();

	// Вернуть вектор названий городов
	return citiesLabes;
}
//vector<string> readDataFromFile(vector<vector<int>>& roads, vector<int>& costs)
//{	
//	// Открыть файл
//	ifstream file;
//	//std::ifstream file(inputFilePath);
//	file.open("input.csv");
//
//	// Считать первую строку файла
//	string line;
//	std::getline(file, line);
//	stringstream ss(line);
//
//	string label;
//	vector<string> citiesLabes;
//
//
//	// Заполнить вектор названиями городов
//	while (std::getline(ss, label, ';')) {
//		if (label != "") {
//			citiesLabes.push_back(label);
//		}
//	}
//	roads.resize(citiesLabes.size(), vector<int>(citiesLabes.size(), 0));
//	costs.resize(citiesLabes.size(), 0);
//
//	std::getline(file, line);
//	ss.clear();
//	ss.str(line);	
//	int costValueCol = 0;
//	string costVal;
//
//	// Считывание стоимости дорог
//	while (std::getline(ss, costVal, ';')) {
//		
//		 bool containsDigits = all_of(begin(costVal), end(costVal), isdigit); // Проверка, что строка содержит только цифры.
//		 if (costVal != "") {
//			 if (containsDigits) {
//				 costs[costValueCol] = stoi(costVal);				 
//			 }			 
//			 else {
//				 throw InvalidInputFileException("Неправильная запись стоимости за литр. "
//							"Убедитесь, что стоимстость за литр является неотрицательным числом.\n");
//			 }
//		}
//		costValueCol++;
//		if (costValueCol > citiesLabes.size()) {
//			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//						"Убедитесь, что количество цен за стоимость бензина равно количеству городов\n");
//		}
//	}
//
//	std::getline(file, line); // Считать пустую строку
//	std::getline(file, line); // Считать названия город
//	
//	vector<string> matrixCitiesLabes;
//	ss.clear();
//	ss.str(line);
//	// Заполнить вектор названиями городов
//	while (std::getline(ss, label, ';')) {
//		if (label != "") {
//			matrixCitiesLabes.push_back(label);
//		}
//	}
//
//	//заполнение матрицы смежности из файла
//	int row = 0;
//	while (std::getline(file, line)) {
//		stringstream ss(line);
//		string value;
//
//		int col = 0;
//		while (getline(ss, value, ';')) {
//			bool valueContainsDigits = all_of(begin(value), end(value), isdigit); // Проверка, что строка содержит только цифры.
//			
//			if (col == 0 && citiesLabes[row] != value) {
//				throw InvalidInputFileException("Названия города записаны неверно."
//						"Убедитесь, что названия городов в таблице дорог соответствуют названиям городов со стоимостью бензина.\n");
//			}
//			else if (col == 0 && matrixCitiesLabes[row] != value) {
//				throw InvalidInputFileException("Названия города несимметричны."
//					"Убедитесь, что названия городов в таблице дорог записаны верно.\n");
//			}
//
//			if (value != "" && col > 0) {
//				if (valueContainsDigits) {
//					roads[row][col - 1] = stoi(value);
//				}				
//				else {
//					throw InvalidInputFileException("Неправильная запись задаваемого количества литров между городами. "
//						"Убедитесь, что количество литров для дороги является неотрицательным числом.\n");
//				}
//			}
//			
//			col++;
//			if (col > citiesLabes.size() + 1) {
//				throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//					"Убедитесь, что количество цен за стоимость бензина равно количеству городов.\n");
//			}
//		}
//		row++;
//		if (row > citiesLabes.size()) {
//			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//				"Убедитесь, что количество городов равны.\n");
//		}
//	}
//
//	file.close();
//
//	// Вернуть вектор названий городов
//	return citiesLabes;
//}

void multiplyCostsAndRoads(vector<vector<int>>& roads, vector<int>& costs) {

	for (int i = 0; i < costs.size() - 1; i++) {
		for (int j = i; j < costs.size(); j++) {
			roads[i][j] = roads[i][j] * costs[i];
			roads[j][i] = roads[j][i] * costs[j];
			
			int first = roads[i][j];
			int second = roads[j][i];
			// Обработать петлю
			if (i == j && first != 0)
			{
				throw InvalidValueException("Не может быть петли. "
						"Убедитесь, что схема дорог города не содержит дорог, которые соединяют один и тот же город.\n");
			}
			// обработать двусторонние дороги
			if ( (first == 0 && second != 0) || (first != 0 && second == 0)) {
				throw InvalidValueException("Дороги могут быть только двусторонними. "
						"Убедитесь, что существуют оба пути между городами.\n");
			}
						
		}
	}

}

int findCheapestPath(vector<vector<int>> roads, int amountRoads, int source) {

	// Инициализировать все растояния 
	vector<int> distances(amountRoads, INT_MAX);
	distances[source] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQueue;
	pQueue.push(make_pair(0, source));

	while (!pQueue.empty()) {
		int u = pQueue.top().second;
		pQueue.pop();

		for (int v = 0; v < amountRoads; v++) {
			if (roads[u][v] != 0 && distances[v] > distances[u] + roads[u][v]) {
				distances[v] = distances[u] + roads[u][v];
				pQueue.push(make_pair(distances[v], v));
			}
		}
	}
	return distances.back();

}

//void outputResultToFile(vector<vector<int>> roads, vector<string> citiesLabels)
//{
//	//вывод в файл
//	ofstream fout;
//	fout.open("output.txt");
//	fout << findCheapestPath(roads, citiesLabels.size(), 0);
//	fout.close();
//}

void validateInputData(vector<vector<int>> roads, vector<int> costs) {



}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	vector<vector<int>> matrixRoads;
	vector<int> costs;

	if (argc != 3)
	{
		std::cerr << "Неправильно указаны параметры запуска. "
			"Убедитесь, что параметры соотвествуют шаблону: \n"
			<< argv[0] << " <path/to/input_file> <path/to/save_file>\n";
		return 1;
	}
	
	std::ifstream inputFile(argv[1]);

	if (!inputFile.is_open()) {
		std::cerr << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[1] << '\n';
		return 1;
	}
	
	filesystem::path outputPath = filesystem::path(argv[2]);

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
	

	//Считать данные из файла
	try
	{
		auto citiesLabels = readDataFromFile(argv[1], matrixRoads, costs);		 

		//auto citiesLabels = readDataFromFile(matrixRoads, costs);

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
	
	outputFile << findCheapestPath(matrixRoads, costs.size(), 0);

	// Закрыть файлы
	inputFile.close();
	outputFile.close();

	return 0;
}

//int main() {
//	setlocale(LC_ALL, "Russian");
//
//	vector<vector<int>> matrixRoads;
//	vector<int> costs;
//
//	//Считать данные из файла
//	try
//	{
//		//auto citiesLabels = readDataFromFile(argv[1], matrixRoads, costs);		 
//
//		auto citiesLabels = readDataFromFile(matrixRoads, costs);
//
//		// Преобразовать дороги и стоимости в матрицу смежности
//		multiplyCostsAndRoads(matrixRoads, costs, costs.size());
//
//		// Вывести решение в файл
//		outputResultToFile(matrixRoads, citiesLabels);
//
//	}
//	catch (const InvalidInputFileException& e)
//	{
//		std::cerr << e.what();
//		return 1;
//	}
//	catch (const InvalidValueException& e) {
//		std::cerr << e.what();
//		return 1;
//	}
//
//	return 0;
//}