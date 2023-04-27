#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;


vector<string> readDataFromFile(vector<vector<int>>& roads, vector<int>& costs)
{
	// Открыть файл
	ifstream file;
	file.open("input.csv");

	// Считать первую строку файла
	string line;
	getline(file, line);
	stringstream ss(line);

	string label;
	vector<string> citiesLabes;


	// Заполнить вектор названиями городов
	while (getline(ss, label, ';')) {
		if (label != "") {
			citiesLabes.push_back(label);
		}
	}
	roads.resize(citiesLabes.size(), vector<int>(citiesLabes.size(), 0));
	costs.resize(citiesLabes.size(), 0);

	getline(file, line);
	stringstream ssCost(line);
	int costValueCol = 0;
	string costVal;

	// Считывание стоимости дорог
	while (getline(ssCost, costVal, ';')) {
		if (costVal != "") {
			costs[costValueCol] = stoi(costVal);
		}
		costValueCol++;
	}

	getline(file, line); // Считать пустую строку
	getline(file, line); // Считать названия город

	//заполнение матрицы смежности из файла
	int row = 0;
	while (getline(file, line)) {
		stringstream ss(line);
		string value;
		int col = 0;
		while (getline(ss, value, ';')) {
			if (value != "" && col > 0) {
				roads[row][col - 1] = stoi(value);
			}
			col++;
		}
		row++;
	}

	file.close();

	// Вернуть вектор названий городов
	return citiesLabes;
}

void multiplieCostsAndRoads(vector<vector<int>>& roads, vector<int>& costs, int amountCities) {

	for (int i = 0; i < amountCities - 1; i++) {
		for (int j = i; j < amountCities; j++) {
			roads[i][j] = roads[i][j] * costs[i];
			roads[j][i] = roads[j][i] * costs[j];
		}
	}

}



int main() {

	//Считать данные из файла

	// Преобразовать дороги и стоимости в матрицу смежности

	// Вывести решение в файл

	return 0;
}