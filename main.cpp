#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

#include "RegTree.h"

using namespace std;

/// funções de utilidade para dividir os dados da string
void split(const string &s, char delimiter, vector<string>& data) {
	stringstream ss, dss;
	ss.str(s);
	string item, d;
	dss << delimiter;
	dss >> d;
	while (getline(ss, item, delimiter)) {
		if (item != d) // não considera o delimiter se ele for o primeiro caractere da string
			data.push_back(item);
	}
}

vector<string> split(const string &s, char delimiter) {
	vector<string> data;
	split(s, delimiter, data);
	return data;
}

int main() {
	/// manipulação do arquivo
	ifstream file;
	string filename, lineFromFile;
	vector<string> aux, time, type;
	vector<pair<int, int>> products;
	int versionCount = 0;
	cout << "Arquivo do registro: ";
	cin >> filename;
	if (file.is_open())
		cout << "Arquivo já aberto!" << endl;
	else {
		file.open(filename);
		if (!file.is_open()) {
			cout << "Erro ao abrir arquivo ou arquivo inexistente!" << endl;
			return 0;
		} else {
			while (!file.eof()) {
				getline(file, lineFromFile);
				if (!lineFromFile.empty() && lineFromFile.back() == '\r')// identifica caractere de quebra de linha '\r' adicionado pelo Windows
					lineFromFile.erase(remove(lineFromFile.begin(), lineFromFile.end(), '\r'), lineFromFile.end());
				if (lineFromFile.length() > 0)
					aux.push_back(lineFromFile);
			}
			file.close();
		}
	}
	// construindo definições dos históricos
	for (int i = 0; i < static_cast<int>(aux.size()); i++) {
		vector<string> temp = split(aux[i], ' ');
		time.push_back(temp[0] + " " + temp[1]);
		products.push_back(make_pair(stoi(temp[3]), stoi(temp[4])));
		if (temp[2] == "V") // marca como negativo em caso de venda
			products[i].second *= -1;
	}
	versionCount = static_cast<int>(time.size());
	/// MÉTODO DA CÓPIA COMPLETA
	BinaryRegTree noobHistory[versionCount];
	for (int i = 0; i < versionCount; i++) {
		if (i == 0) {
			BinaryRegTree aux;
			aux.Update(products[i]);
			noobHistory[i] = aux;
		} else {
			BinaryRegTree temp = noobHistory[i - 1];
			temp.Update(products[i]);
			noobHistory[i] = temp;
		}
	}
	/// MÉTODO DA CÓPIA APENAS DOS NÓS MODIFICADOS
	BinaryRegTree persistentHistory[versionCount];
	for (int i = 0; i < versionCount; i++) {
		if (i == 0) {
			BinaryRegTree aux;
			aux.Update(products[i]);
			persistentHistory[i] = aux;
		} else {
			BinaryRegTree aux;
			aux.Upgrade(products[i], persistentHistory[i - 1]);
			persistentHistory[i] = aux;
		}
	}
	/// BUSCA POR VERSÕES E ARQUIVO DE SAÍDA
	ifstream testfile;
	string testfilename;
	aux.clear();
	cout << "Arquivo de consulta: ";
	cin >> testfilename;
	if (testfile.is_open())
		cout << "Arquivo já aberto!" << endl;
	else {
		testfile.open(testfilename);
		if (!testfile.is_open()) {
			cout << "Erro ao abrir arquivo ou arquivo inexistente!" << endl;
			return 0;
		} else {
			while (!testfile.eof()) {
				getline(testfile, lineFromFile);
				if (!lineFromFile.empty() && lineFromFile.back() == '\r')// identifica caractere de quebra de linha '\r' adicionado pelo Windows
					lineFromFile.erase(remove(lineFromFile.begin(), lineFromFile.end(), '\r'), lineFromFile.end());
				if (lineFromFile.length() > 0)
					aux.push_back(lineFromFile);
			}
			testfile.close();
		}
	}
	// realizando as buscas
	for (int i = 0; i < static_cast<int>(aux.size()); i++) {
		int k = -1;
		for (int j = 0; j < static_cast<int>(time.size()); j++) {
			if (aux[i] == time[j]) {
				k = j;
				break;
			}
		}
		if (k != -1) {
			persistentHistory[k].Print();
		}
	}
	return 0;
}
