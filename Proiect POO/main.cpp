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
	int preluareDateDinFisier(int numarCont);
	int preluareNumarDeConturiFisier();
	void creareCont();
	bool fisierGol();
	void modificareNumarConturi();
	bool numarContEsteValid(int numarCont);
	void setNumarDeConturiRealizate() {
		//TODO: plasare in fisier
		/*this->numarDeConturiRealizate = preluareNumarDeConturiFisier();
		this->numarDeConturiRealizate += 1;*/
		modificareNumarConturi();

	}
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

bool Cont::fisierGol() {
	ifstream fisier("conturi.txt");
	if (fisier.peek() == ifstream::traits_type::eof()) {
		return true;
	}
	else {
		return false;
	}
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

int Cont::preluareDateDinFisier(int numarCont) {
	ifstream fisierConturi;
	map<int, int> conturi;
	string line;
	int primaLinie = 0;
	fisierConturi.open("conturi.txt");
	if (fisierGol()) {
		return 0;
	}
	else {
		while (getline(fisierConturi, line)) {
			if (line.empty()) {
				continue;
			}
			// daca linia contine numarul de conturi, se trece peste acea valoare
			if (line.size() <= 2) continue;
			auto it = line.find(" ");

			if (it != string::npos) {
				// stoi = conversie din string in int
				// preluare prima valoare si a doua valoare de pe fiecare linie
				this->numarCont = stoi(line.substr(0, it));
				this->valoareCont = stoi(line.substr(it + 1, line.npos));
				conturi[this->numarCont] = this->valoareCont;
			}


		}

		// daca gaseste cheia, afiseaza valoarea contului 
		if (conturi.find(numarCont) != conturi.end()) {
			// cout << conturi[numarCont] << endl;
			return (int)conturi[numarCont];
		}
	}
	}

bool Cont::numarContEsteValid(int numarCont) {
	ifstream fisierConturi;
	map<int, int> conturi;
	string line;
	fisierConturi.open("conturi.txt");
	if (fisierGol()) {
		return true;
	}
	else {
		while (getline(fisierConturi, line)) {
			if (line.empty()) {
				continue;
			}
			// daca linia contine numarul de conturi care va fi <= 99, se trece peste acea valoare
			if (line.size() <= 2) continue;
			auto it = line.find(" ");

			if (it != string::npos) {
				// stoi = conversie din string in int
				// preluare prima valoare si a doua valoare de pe fiecare linie
				this->numarCont = stoi(line.substr(0, it));
				// daca exista numarul de cont, se returneaza ca fiind invalid(fals)
				if (this->numarCont == numarCont) {
					return false;
					break;
				}
			}


		}
	}

}

int Cont::preluareNumarDeConturiFisier() {
	ifstream fisierConturi;
	fisierConturi.open("conturi.txt");
	string line;

	if (fisierGol()) {
		return 0;
	}
	else {
		// preluare prima linie din fisier - nr de conturi
		while (!fisierConturi.eof()) {
			getline(fisierConturi, line);
			this->numarDeConturiRealizate = stoi(line);
			break;
		}

		return this->numarDeConturiRealizate;
	}
}

// FIX: linia nu se schimba
// FIX: se adauga un enter in plus dupa inserarea in fisier

//void Cont::modificareNumarConturi() {
//	ifstream fisierConturi;
//	fisierConturi.open("conturi.txt");
//	string line;
//	int numarConturi;
//	numarConturi = preluareNumarDeConturiFisier();
//			// preluare prima linie din fisier - nr de conturi
//		while (!fisierConturi.eof()) {
//			getline(fisierConturi, line);
//			size_t pozitie = line.find(numarConturi);
//			//int pozitie = 0;
//			string valoareModificata = to_string(numarConturi);
//			//int lungime = line.size();
//			int lungime = line.length();
//			//line.replace(pozitie, lungime, valoareModificata);
//			line.replace(pozitie, lungime, "2");
//			break;
//		}
//
//}

void Cont::modificareNumarConturi() {
	ifstream filein("conturi.txt");
	ofstream fileout("conturiNew.txt");
	int numarContInt = preluareNumarDeConturiFisier();
	int numarContIntNou = numarContInt + 1;
	// conversie in string
	string numarConturiNou = to_string(numarContIntNou);
	string numarConturi = to_string(numarContInt);
	if (!filein || !fileout) {
		cout << "Eroare deschidere" << endl;
	}
	string line;
	string strTemp;
	//bool found = false;
	while (getline(filein, line)) {
		
	
	}

}


void Cont::creareCont() {

	// deschidere fisier
	ofstream fisierConturi;
	fisierConturi.open("conturi.txt", ios::app);
	int numarCont = 0;
	cout << "Numar cont: " << endl;
	cin >> numarCont;
	while (!numarContEsteValid(numarCont)) {
		cout << "Acest cont deja exista, alege alt numar de cont!" << endl;
		cout << "Numar cont: " << endl;
		cin >> numarCont;
	}
	// scrierea datelor in fisier
	// daca am deja deja nr conturi realizate pe prima linie, atunci o preiau si o incrementez
	if (!fisierGol()) {
		setNumarDeConturiRealizate();
		fisierConturi << endl;
	}
	else fisierConturi << 0 << endl;
	fisierConturi << numarCont << " " << 0 << endl;
	}


int main() {
	Cont cont;
	//cont.creareCont();



	/*int numarCont;
	while (true) {
		cin >> numarCont;
	cout << cont.preluareDateDinFisier(numarCont);
	}*/
}
