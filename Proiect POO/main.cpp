#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;



class Cont{
private:
	int numarCont;
	int valoareCont;
	int numarDeConturiRealizate;
	int* valori;
	int index;
	int sumaConturi;

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
		cout << endl << endl;
		cout << "CONT || VALOARE" << endl;
		for (int i = 1; i < index; i += 2)
		{
			if (this->valori[i] < 0 || this->valori[i] > 10000000) continue;
			cout << "|| " << this->valori[i] << " || " << this->valori[i + 1] << " ||" << endl;
		}
	}

	int gasireValoareCont(int numarCont);
	int preluareNumarDeConturiFisier();
	void creareCont();
	bool fisierGol();
	void incrementareNumarConturi();
	bool numarContEsteValid(int numarCont);
	void citireFisier();
	void inchidereCont(int cont);
	void depunereRetragereBani(int cont, int suma, bool depunere);
	void stergereFisiere();
	int sumaTotala();
	void transfer(int contExpeditor, int contDestinatar, int suma);

	int getSumaTotala() {
		return this->sumaConturi;
	}


	friend ostream& operator << (ostream& consola, Cont& cont) {

		cont.sumaTotala();
		consola << "Valoarea totala a conturilor detinute este: " << cont.getSumaTotala() << " lei";

		return consola;

	}


	~Cont() {
		if (this->valori != NULL) delete[] this->valori;
	}
};

void Cont::citireFisier() {
	// prelucreaza datele fisierului intr-un array

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
	fisierConturi.close();
}



void mesajCont() {
	cout << "----------------------------------------------" << endl;
	cout << "1. Depunere bani \n2. Retragere bani \n3. Transfer in alt cont \n4. Suma totala detinuta de toate conturile" << endl;
	cout << "----------------------------------------------" << endl;
}


bool Cont::fisierGol() {
	ifstream fisier("conturi.txt");
	return (fisier.peek() == ifstream::traits_type::eof());
	fisier.close();
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

int Cont::gasireValoareCont(int numarCont) {
	// cauta si gaseste valoarea unui cont (balanta)
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
	fisierConturi.close();
	}


bool Cont::numarContEsteValid(int numarCont) {
	// cauta existenta unui cont
	ifstream fisierConturi;
	//map<int, int> conturi; incercare cu map 
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
				int numarCautat = stoi(line.substr(0, it));
				// daca exista numarul de cont, se returneaza ca fiind invalid(fals)
				if (numarCautat == numarCont) {
					return false;
					break;
				}
			}


		}
	}
	fisierConturi.close();

}


int Cont::preluareNumarDeConturiFisier() {
	// preia prima valoare din fisier, fiind numarul de conturi
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
	fisierConturi.close();
}


void Cont::incrementareNumarConturi() {
	ifstream filein("conturi.txt");
	ofstream fileout("conturiNew.txt");
	int numarContInt = preluareNumarDeConturiFisier();
	// prima valoare este numarul de conturi, o incrementez 
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



	stergereFisiere();

}


void Cont::creareCont() {

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
		fisierConturi << endl;

	} else fisierConturi << 0 << endl;

	fisierConturi << numarCont << " " << 0 << endl;

	// citesc dupa ce creez contul si apoi scriu in conturiNew
	citireFisier();
	fisierConturi.close();
	incrementareNumarConturi();
	}


void Cont::inchidereCont(int cont) {
	int* temp = new int[this->index - 2]; 
	temp[0] = this->valori[0];
	bool gasit = false;
	
	// copiere valori bune in temp
	for (int i = 1; i < this->index; i += 2) {

		if (this->valori[i] != cont) {
			temp[i] = this->valori[i];
			temp[i + 1] = this->valori[i + 1];
		}
		else gasit = true;
	}

	// daca nu exista, iesim din functie
	if (!gasit) return;

	this->valori = temp;


	// MODIFICARE FISIER

	ifstream filein("conturi.txt");
	ofstream fileout("conturiNew.txt");
	int numarContInt = preluareNumarDeConturiFisier();
	// prima valoare este numarul de conturi, o incrementez 
	this->valori[0] = numarContInt - 1;

	if (!filein || !fileout) {
		cout << "Eroare deschidere" << endl;
		return;
	}
	else {
		fileout << this->valori[0] << endl << endl;
		for (int i = 1; i < index; i++)
		{
			if (this->valori[i] < 0 || this->valori[i] > 100000000) continue;
			fileout << this->valori[i];
			fileout << " ";
			if (i % 2 == 0) fileout << endl << endl;
		}
	}

	filein.close();
	fileout.close();



	stergereFisiere();
}


void Cont::depunereRetragereBani(int cont, int suma, bool depunere) {

	int* temp = new int[this->index];
	temp[0] = this->valori[0];
	bool gasit = false;

	if (depunere == true) {

	// copiere valori bune in temp
	for (int i = 1; i < this->index; i += 2) {

		if (this->valori[i] != cont) {
			temp[i] = this->valori[i];
			temp[i + 1] = this->valori[i + 1];
		}
		else { 
			gasit = true; 
			temp[i] = this->valori[i];
			temp[i + 1] = this->valori[i + 1] + suma;
		}
	}

		// daca nu exista, iesim din functie
		if (!gasit) return;

	}
	else {

	// copiere valori bune in temp
	for (int i = 1; i < this->index; i += 2) {

		if (this->valori[i] != cont) {
			temp[i] = this->valori[i];
			temp[i + 1] = this->valori[i + 1];
		}
		else { 
			while (suma > this->valori[i + 1]) {
				cout << "Nu aveti destui bani in cont, incercati din nou: " << endl;
				cin >> suma;
			}
			gasit = true; 
			temp[i] = this->valori[i];
			temp[i + 1] = this->valori[i + 1] - suma;
		}
	}

		// daca nu exista, iesim din functie
		if (!gasit) return;
	}

	this->valori = temp;


	// MODIFICARE FISIER

	ifstream filein("conturi.txt");
	ofstream fileout("conturiNew.txt");

	if (!filein || !fileout) {
		cout << "Eroare deschidere" << endl;
		return;
	}
	else {
		fileout << this->valori[0] << endl << endl;
		for (int i = 1; i < index; i++)
		{
			if (this->valori[i] < 0 || this->valori[i] > 100000000) continue;
			fileout << this->valori[i];
			fileout << " ";
			if (i % 2 == 0) fileout << endl << endl;
		}
	}

	filein.close();
	fileout.close();



	stergereFisiere();
}


void Cont::stergereFisiere() {

	//stergere si redenumire fisier nou cu cel vechi
	int remove_result = remove("conturi.txt");
	if (remove_result != 0) {
		// An error occurred
		char* error_message = strerror(errno);
		//printf("Error deleting file: %s\n", error_message);
	}
	//else {
	//	printf("File deleted succesfully");
	//}




	int rename_result = rename("conturiNew.txt", "conturi.txt");
	if (rename_result != 0) {
		char* error_message = strerror(errno);
		//printf("Error renaming file: %s\n", error_message);
	}
	//else {
	//	printf("File renamed succesfully");
	//}
}


int Cont::sumaTotala() {

	this->sumaConturi = 0;
	
	for (int i = 2; i < index; i += 2)
	{
		this->sumaConturi += this->valori[i];
	}

	return this->sumaConturi;

}


void Cont::transfer(int contExpeditor, int contDestinatar, int suma) {

	int pozitieExpeditor = 0;
	int pozitieDestinatar = 0;

	for (int i = 1; i < this->index; i += 2) {
		if (this->valori[i] == contExpeditor) {
			pozitieExpeditor = i;
		}
		else if (this->valori[i] == contDestinatar) {
			pozitieDestinatar = i;
		}
	}

	if (pozitieDestinatar == 0 || pozitieExpeditor == 0) {
		cout << "NU EXISTA CONTURILE SPECIFICATE!!" << endl;
		return;
	}

	// daca val exp e mai mare decat suma, avem cont suficient 
	if (this->valori[pozitieExpeditor + 1] >= suma) {
		this->valori[pozitieDestinatar + 1] += suma;
		this->valori[pozitieExpeditor + 1] -= suma;
	}
	else {
		cout << "FONDURI INSUFICIENTE!" << endl;
		return;
	}

	// MODIFICARE FISIER

	ifstream filein("conturi.txt");
	ofstream fileout("conturiNew.txt");

	if (!filein || !fileout) {
		cout << "Eroare deschidere" << endl;
		return;
	}
	else {
		fileout << this->valori[0] << endl << endl;
		for (int i = 1; i < index; i++)
		{
			if (this->valori[i] < 0 || this->valori[i] > 100000000) continue;
			fileout << this->valori[i];
			fileout << " ";
			if (i % 2 == 0) fileout << endl << endl;
		}
	}

	filein.close();
	fileout.close();


	stergereFisiere();

}


int main() {
	Cont cont;
	cont.citireFisier();

	while (true) {
		cout << endl << endl;
		cout << "Ce doriti sa faceti: " << endl;
		cout << "1. Deschidere cont" << endl;
		cout << "2. Inchidere cont" << endl;
		cout << "3. Consolidare sold cont specificat" << endl;
		cout << "4. Consolidare sold total" << endl;
		cout << "5. Transfer catre alt cont" << endl;
		cout << "6. Depunere" << endl;
		cout << "7. Retragere" << endl;
		cout << "8. Vizualizarea tuturor conturilor" << endl;
		cout << "9. Iesire din aplicatie" << endl;
		cout << endl << endl;

		int optiune;
		cin >> optiune;

		switch (optiune) {
		case 1: {
			cont.creareCont();
			break;
		}
		case 2: {
			int nrCont;
			cout << "Introduceti numarul contului pe care doriti sa il inchideti: " << endl;
			cin >> nrCont;
			cont.inchidereCont(nrCont);
			break;
		}
		case 3: {
			int nrCont;
			cout << "Introduceti numarul contului pe care doriti sa il consolidati: " << endl;
			cin >> nrCont;
			cout << "Valoarea contului " << nrCont << " este " << cont.gasireValoareCont(nrCont) << " lei" << endl;
			break;
		}
		case 4: {
			cout << "Suma totala a conturilor este de " << 	cont.sumaTotala() << " lei" << endl;
			break;
		}
		case 5: {
			int contExpeditor;
			int contDestinatar;
			int suma;
			cout << "Introduceti numarul contului curent: " << endl;
			cin >> contExpeditor;
			cout << "Introduceti numarul contului catre care doriti transferul: " << endl;
			cin >> contDestinatar;
			cout << "Introduceti suma pe care doriti sa o transferati: " << endl;
			cin >> suma;
			cont.transfer(contExpeditor, contDestinatar, suma);
			break;
		}
		case 6: {
			int nrCont;
			int suma;
			cout << "Introduceti numarul contului pe care doriti sa depuneti: " << endl;
			cin >> nrCont;
			cout << "Introduceti suma pe care doriti sa o depuneti: " << endl;
			cin >> suma;
			cont.depunereRetragereBani(nrCont, suma, true);
			break;
		}
		case 7: {
			int nrCont;
			int suma;
			cout << "Introduceti numarul contului de pe care doriti sa retrageti: " << endl;
			cin >> nrCont;
			cout << "Introduceti suma pe care doriti sa o retrageti: " << endl;
			cin >> suma;
			cont.depunereRetragereBani(nrCont, suma, false);
			break;
		}

		case 8: {
			cont.getValori();
			break;
		}
			  
		case 9: {
			return 0;
		}
		default: {
			cout << "Optiune invalida!" << endl;
			break;
		}

		}
	}
}
