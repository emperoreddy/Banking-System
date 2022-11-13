#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Cont{
private:
	int numarCont;
	int valoareCont;
	int numarDeConturiRealizate;
	// char* numeClient;

public:
	// definire parametri default
	Cont() {
		this->numarDeConturiRealizate = 0;
		this->numarCont = 0;
		this->valoareCont = 0;
		//this->numeClient = new char[strlen(numeClient) + 1];
		//strcpy(this->numeClient, numeClient);
	}
	void preluareDateDinFisier(int numarCont);
	int preluareNumarDeConturiFisier();
	void creareCont();
	void setNumarDeConturiRealizate(int numarDeConturiRealizate);
};

void mesajCreare() {
	cout << "----------------------------------------------" << endl;
	cout << "1. Creare cont \n2. Inchidere cont" << endl;
	cout << "----------------------------------------------" << endl;
}

void mesajCont() {
	cout << "----------------------------------------------" << endl;
	cout << "1. Depunere bani \n2. Retragere bani \n3. Transfer in alt cont \n4. Suma totala detinuta de toate conturile" << endl;
	cout << "----------------------------------------------" << endl;
}

// optiuni creare
/*void optiuneCreare() {
	int optiune;
	mesajCreare();
	cout << "Introduceti optiunea: ";
	cin >> optiune;
	switch (optiune) {
	case 1:
		deschidereCont();
		cout << "Cont creat cu succes!" << endl;
		 
		break;
	case 2:
		cout << "Inchidere cont" << endl;
		break;
	default:
		cout << "Optiune invalida" << endl;
		break;
	}
}*/

// FIX: nu prelua prima linie din fisier
void Cont::preluareDateDinFisier(int numarCont) {
	ifstream fisierConturi;
	fisierConturi.open("conturi.txt");
	map<int, int> conturi;
	string line;
	int primaLinie = 0;

	while (getline(fisierConturi, line)) {
		if (line.empty()) {
			continue;
		}
		// daca linia contine numarul de conturi, se trece peste acea valoare
		//if (line.size() <= 2) continue;
		auto it = line.find(" ");

		if (it != string::npos) {
			// conversie din string in int
			// preluare prima valoare si a doua valoare de pe fiecare linie
			this->numarCont = stoi(line.substr(0, it));
			this->valoareCont = stoi(line.substr(it + 1, line.npos));
			conturi[this->numarCont] = this->valoareCont;
		}

		// daca gaseste cheia, afiseaza valoarea contului 
		if (conturi.find(numarCont) != conturi.end()) {
			cout << conturi[numarCont] << endl;
		}

	}
}



int Cont::preluareNumarDeConturiFisier() {
	ifstream fisierConturi;
	fisierConturi.open("conturi.txt");
	string line;
	// preluare prima linie din fisier - nr de conturi
	while (!fisierConturi.eof()) {
		getline(fisierConturi, line);
		this->numarDeConturiRealizate = stoi(line);
		break;
	}

	return this->numarDeConturiRealizate;
}




void Cont::creareCont() {

	// deschidere fisier
	ofstream fisierConturi;
	fisierConturi.open("conturi.txt", ios::app);
	cout << "Numar cont: " << endl;
	cin >> this->numarCont;
	// scrierea datelor in fisier
	// daca am deja deja nr conturi realizate pe prima linie, atunci o preiau si o incrementez
	fisierConturi << this->numarDeConturiRealizate << endl;
	fisierConturi << this->numarCont << " " << this->valoareCont << endl;
	}


int main() {
	Cont cont;
//	cont.creareCont();
	cont.preluareDateDinFisier(1);
//	cout << "Nr de conturi: "<< cont.preluareNumarContFisier();
}
