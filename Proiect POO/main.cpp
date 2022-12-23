#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;


/*TODO: 
x citesc datele din fisier
x prelucrez datele intr o lista [2,5,100,3,200] sau [[2], [5,100], [3, 200]]
- modific ce am de modificat
- rescriu datele in fisier
	- scriu prima valoare, endl => scriu a doua valoare, spatiu, a treia valoare, endl .. */


class Cont{
private:
	int numarCont;
	int valoareCont;
	int numarDeConturiRealizate;
	int* valori;
	int index;

public:
	Cont() {
		this->index = 0;
		this->numarDeConturiRealizate = 0;
		this->numarCont = 0;
		this->valoareCont = 0;
		this->valori = new int[100];
		this->valori[0] = preluareNumarDeConturiFisier();
	}


	void getValori() {
		for (int i = 0; i < index; i++)
		{
			cout << this->valori[i] << endl;
		}
	}


	int preluareDateDinFisier(int numarCont);
	int preluareNumarDeConturiFisier();
	void creareCont();
	bool fisierGol();
	void incrementareNumarConturi();
	bool numarContEsteValid(int numarCont);
	void citireFisier();


	~Cont() {
		if (this->valori != NULL) delete[] this->valori;
	}
};

void Cont::citireFisier() {
	ifstream fisierConturi;
	string line;
	this->index = 1;
	fisierConturi.open("conturi.txt");
	if (!fisierGol()) {
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
				this->valori[this->index] = this->numarCont;
				this->valori[this->index + 1] = this->valoareCont;
				this->index += 2;
			}


		}

	}
}


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
	return (fisier.peek() == ifstream::traits_type::eof());
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


void Cont::incrementareNumarConturi() {
	ifstream filein("conturi.txt");
	ofstream fileout("conturiNew.txt");
	int numarContInt = preluareNumarDeConturiFisier();
	// prima valoare este numarul de conturi, o modific
	this->valori[0] = numarContInt + 1;

	if (!filein || !fileout) {
		cout << "Eroare deschidere" << endl;
		return;
	}
	else {
		fileout << this->valori[0] << endl << endl;
		for (int i = 1; i < index; i++)
		{
			fileout << this->valori[i];
			fileout << " ";
			if (i % 2 == 0) fileout << endl << endl;
		}
	}

	filein.close();
	fileout.close();

	if (filein.is_open()) {
		printf("File is open");
	}

	 //stergere si redenumire fisier nou cu cel vechi
	int remove_result = remove("conturi.txt");	 
	if (remove_result != 0) {
    // An error occurred
    char* error_message = strerror(errno);
    printf("Error deleting file: %s\n", error_message);
	}
	else {
		printf("File deleted succesfully");
	}
	
	
	/*int rename_result = rename("conturiNew.txt", "test.txt");
	if (rename_result != 0) {
		char* error_message = strerror(errno);
		printf("Error deleting file: %s\n", error_message);
	}*/
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
		// INCERCARE
		fisierConturi.close();


		incrementareNumarConturi();
		fisierConturi << endl;

	}
	else fisierConturi << 0 << endl;
	fisierConturi << numarCont << " " << 0 << endl;
	}


int main() {
	Cont cont;
	 cont.citireFisier();
	cont.creareCont();
}
