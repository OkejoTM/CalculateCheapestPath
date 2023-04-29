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

bool checkStringIsDigit(const std::string s) {
	int i = 0; int k = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] < '0' || s[i] > '9') {
			return false;
		}
	}
	return true;
}

bool onlySpaces(const std::string str) {
	for (char ch : str) {
		if (ch != ' ') {
			return false;
		}
	}
	return true;
}

vector<string> readDataFromFile(const std::string& inputFilePath, vector<vector<int>>& roads, vector<int>& costs)
{
	std::ifstream file(inputFilePath);

	// Считать первую строку файла
	string line;
	std::getline(file, line);
	if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
	stringstream ss(line);
	string label;
	vector<string> citiesLabes;

	// Заполнить вектор названиями городов
	while (std::getline(ss, label, ';')) {
		if (label == "") {
			throw InvalidInputFileException("Неправильная запись городов. "
				"Убедитесь, что записаны все города, и отсутствуют пустые значения между городами.\n");
		}
		citiesLabes.push_back(label);			
	}	

	roads.resize(citiesLabes.size(), vector<int>(citiesLabes.size(), 0));
	costs.resize(citiesLabes.size(), 0);

	std::getline(file, line);
	if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
	ss.clear();
	ss.str(line);	
	int costValueCol = 0;
	string costVal;

	// Считывание стоимости дорог
	while (std::getline(ss, costVal, ';')) {
		
		bool containsDigits = checkStringIsDigit(costVal); // Проверка, что строка содержит только цифры.

		 if (costVal == "") {
			throw InvalidInputFileException("Неправильная запись стоимости бензина. "
				"Убедитесь, что записаны все стоимости за литр бензина в городах, и отсутствуют пустые значения между числами.\n");
		 }
		 if (costValueCol < costs.size()) {			 
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

	if (costValueCol < citiesLabes.size()) {
		throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
			"Убедитесь, что количество цен за стоимость бензина равно количеству городов\n");
	}

	//std::getline(file, line); // Считать пустую строку
	std::getline(file, line); // Считать названия городов
	if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");

	vector<string> matrixCitiesLabes;
	ss.clear();
	ss.str(line);
	bool firstComaAppeared = false;
	int t = 0;

	// Заполнить вектор названиями городов
	while (std::getline(ss, label, ';')) {
		if (label == "" && t == 0) {
			firstComaAppeared = true;
		}
		else if (label == "" && firstComaAppeared) {			
			throw InvalidInputFileException("Неправильная запись городов. "
				"Убедитесь, что записаны все города, и отсутствуют пустые значения между городами.\n");
		}
		else if (label != "" && t == 0) {
			throw InvalidInputFileException("Неправильная запись городов. "
				"Убедитесь, что первым значением является разделитель.\n");
		}
		if (t != 0) matrixCitiesLabes.push_back(label);
		t++;
	}

	if (matrixCitiesLabes.size() != citiesLabes.size()) {
		throw InvalidInputFileException("Неверное количество городов. "
				"Убедитесь, что количество городов в таблице дорог соответствует количеству городов в таблице стоимости бензина.\n");
	}

	//заполнение матрицы смежности из файла
	vector<string> verticalCitiesLabels;
	int row = 0;
	while (std::getline(file, line)) {
		if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
		if (row >= citiesLabes.size()) {
			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
				"Убедитесь, что количество городов равны.\n");
		}
		stringstream ss(line);
		string value;

		int col = 0;
		while (getline(ss, value, ';')) {
			bool valueContainsDigits = checkStringIsDigit(value); // Проверка, что строка содержит только цифры.
			
			if (col == 0 && citiesLabes[row] != value) {
				throw InvalidInputFileException("Названия города записаны неверно. "
						"Убедитесь, что названия городов в таблице дорог соответствуют названиям городов со стоимостью бензина.\n");
			}
			else if (col == 0 && matrixCitiesLabes[row] != value) {
				throw InvalidInputFileException("Названия города несимметричны. "
					"Убедитесь, что названия городов в таблице дорог записаны верно.\n");
			}
			else if (col == 0) {
				verticalCitiesLabels.push_back(value); // Записать название города в вектор с городами по Y
			}

			if (value != "" && col > 0) {
				if (valueContainsDigits && col < citiesLabes.size() + 1) {
					roads[row][col - 1] = stoi(value);
				}	
				else if (col >= citiesLabes.size() + 1) {
					throw InvalidInputFileException("Избыток количество параметров. "
						"Убедитесь, что нету количество значений литров для дорог равно количеству городов.\n");
				}
				else {
					throw InvalidInputFileException("Неправильная запись задаваемого количества литров между городами. "
						"Убедитесь, что количество литров для дороги является неотрицательным числом.\n");
				}
			}
			else if (value == "" && col < citiesLabes.size() + 1) {
				throw InvalidInputFileException("Недостаточное количество параметров. "
						"Убедитесь, что количество литров для дороги записаны для каждого города.\n");
			}
			
			col++;
			if (col > citiesLabes.size() + 1) {
				throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
					"Убедитесь, что количество цен за стоимость бензина равно количеству городов.\n");
			}
		}
		if (col < citiesLabes.size() + 1) {
			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
				"Убедитесь, что количество цен за стоимость бензина равно количеству городов.\n");
		}
		row++;
		
	}
	if (verticalCitiesLabels.size() < citiesLabes.size()) {
		throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
			"Убедитесь, что количество городов равны.\n");
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
//	if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
//	stringstream ss(line);
//	string label;
//	vector<string> citiesLabes;
//
//	// Заполнить вектор названиями городов
//	while (std::getline(ss, label, ';')) {
//		if (label == "") {
//			throw InvalidInputFileException("Неправильная запись городов. "
//				"Убедитесь, что записаны все города, и отсутствуют пустые значения между городами.\n");
//		}
//		citiesLabes.push_back(label);
//		
//		/*if (label != "") {
//			if (hasSpace) {
//				throw InvalidInputFileException("Неправильная запись городов. "
//					"Убедитесь, что записаны все города, и отсутствуют пустые значения между городами.\n");
//			}
//			citiesLabes.push_back(label);
//		}	
//		else {
//			hasSpace = true;
//		}*/
//	}	
//
//	roads.resize(citiesLabes.size(), vector<int>(citiesLabes.size(), 0));
//	costs.resize(citiesLabes.size(), 0);
//
//	std::getline(file, line);
//	if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
//	ss.clear();
//	ss.str(line);	
//	int costValueCol = 0;
//	string costVal;
//
//	// Считывание стоимости дорог
//	while (std::getline(ss, costVal, ';')) {
//		
//		bool containsDigits = checkStringIsDigit(costVal); // Проверка, что строка содержит только цифры.
//
//		 if (costVal == "") {
//			throw InvalidInputFileException("Неправильная запись стоимости бензина. "
//				"Убедитесь, что записаны все стоимости за литр бензина в городах, и отсутствуют пустые значения между числами.\n");
//		 }
//		 if (costValueCol < costs.size()) {			 
//			 if (containsDigits) {
//				 costs[costValueCol] = stoi(costVal);				 
//			 }			 
//			 else {
//				 throw InvalidInputFileException("Неправильная запись стоимости за литр. "
//							"Убедитесь, что стоимстость за литр является неотрицательным числом.\n");
//			 }
//		 }
//		 
//
//		costValueCol++;
//		if (costValueCol > citiesLabes.size()) {
//			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//						"Убедитесь, что количество цен за стоимость бензина равно количеству городов\n");
//		}		
//	}
//
//	if (costValueCol < citiesLabes.size()) {
//		throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//			"Убедитесь, что количество цен за стоимость бензина равно количеству городов\n");
//	}
//
//	//std::getline(file, line); // Считать пустую строку
//	std::getline(file, line); // Считать названия городов
//	if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
//
//	vector<string> matrixCitiesLabes;
//	ss.clear();
//	ss.str(line);
//	bool firstComaAppeared = false;
//	int t = 0;
//
//	// Заполнить вектор названиями городов
//	while (std::getline(ss, label, ';')) {
//		if (label == "" && t == 0) {
//			firstComaAppeared = true;
//		}
//		else if (label == "" && firstComaAppeared) {			
//			throw InvalidInputFileException("Неправильная запись городов. "
//				"Убедитесь, что записаны все города, и отсутствуют пустые значения между городами.\n");
//		}
//		else if (label != "" && t == 0) {
//			throw InvalidInputFileException("Неправильная запись городов. "
//				"Убедитесь, что первым значением является разделитель.\n");
//		}
//		if (t != 0) matrixCitiesLabes.push_back(label);
//		t++;
//	}
//
//	if (matrixCitiesLabes.size() != citiesLabes.size()) {
//		throw InvalidInputFileException("Неверное количество городов. "
//				"Убедитесь, что количество городов в таблице дорог соответствует количеству городов в таблице стоимости бензина.\n");
//	}
//
//	//заполнение матрицы смежности из файла
//	vector<string> verticalCitiesLabels;
//	int row = 0;
//	while (std::getline(file, line)) {
//		if (onlySpaces(line)) throw InvalidInputFileException("Неправильная запись данных. " "Проверьте, что строки записаны подряд без пустых строк.\n");
//		if (row >= citiesLabes.size()) {
//			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//				"Убедитесь, что количество городов равны.\n");
//		}
//		stringstream ss(line);
//		string value;
//
//		int col = 0;
//		while (getline(ss, value, ';')) {
//			bool valueContainsDigits = checkStringIsDigit(value); // Проверка, что строка содержит только цифры.
//			
//			if (col == 0 && citiesLabes[row] != value) {
//				throw InvalidInputFileException("Названия города записаны неверно. "
//						"Убедитесь, что названия городов в таблице дорог соответствуют названиям городов со стоимостью бензина.\n");
//			}
//			else if (col == 0 && matrixCitiesLabes[row] != value) {
//				throw InvalidInputFileException("Названия города несимметричны. "
//					"Убедитесь, что названия городов в таблице дорог записаны верно.\n");
//			}
//			else if (col == 0) {
//				verticalCitiesLabels.push_back(value); // Записать название города в вектор с городами по Y
//			}
//
//			if (value != "" && col > 0) {
//				if (valueContainsDigits && col < citiesLabes.size() + 1) {
//					roads[row][col - 1] = stoi(value);
//				}	
//				else if (col >= citiesLabes.size() + 1) {
//					throw InvalidInputFileException("Избыток количество параметров. "
//						"Убедитесь, что нету количество значений литров для дорог равно количеству городов.\n");
//				}
//				else {
//					throw InvalidInputFileException("Неправильная запись задаваемого количества литров между городами. "
//						"Убедитесь, что количество литров для дороги является неотрицательным числом.\n");
//				}
//			}
//			else if (value == "" && col < citiesLabes.size() + 1) {
//				throw InvalidInputFileException("Недостаточное количество параметров. "
//						"Убедитесь, что количество литров для дороги записаны для каждого города.\n");
//			}
//			
//			col++;
//			if (col > citiesLabes.size() + 1) {
//				throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//					"Убедитесь, что количество цен за стоимость бензина равно количеству городов.\n");
//			}
//		}
//		if (col < citiesLabes.size() + 1) {
//			throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//				"Убедитесь, что количество цен за стоимость бензина равно количеству городов.\n");
//		}
//		row++;
//		
//	}
//	if (verticalCitiesLabels.size() < citiesLabes.size()) {
//		throw InvalidInputFileException("Во входной строке неправильное количество параметров. "
//			"Убедитесь, что количество городов равны.\n");
//	}
//
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
//		multiplyCostsAndRoads(matrixRoads, costs);
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