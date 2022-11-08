#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Persoana{
private:
	char* numeCont;
public:
	Persoana(const char* numeCont) {
		this->numeCont = new char[strlen(numeCont) + 1];
		strcpy(this->numeCont, numeCont);
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

// creare conturi multiple pentru o persoana
void deschidereCont() {
	char* numeCont = new char[30];
	cout << "Numele contului:" << endl;
	cin >> numeCont;
	Persoana user(numeCont);
	cout << user.numeCont;
}


void optiuneCreare() {
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
}






int main() {
	
	deschidereCont();
//	optiuneCreare();
}
