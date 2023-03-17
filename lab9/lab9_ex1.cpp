// Kovari E. ex 1. (4.b modificat) cautarea unei persoane in functie de un criteriu si ordonarea descrescatoarea a persoanelor in functie de criterii. 

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
using namespace std;

const int maxi = 30;
const int dim = 5;

class Persoana {
	char* nume;
	double greutate;
	int varsta;
public:
	Persoana() {
		nume = new char[maxi];
		strcpy(nume, "Necunoscut");
		greutate = 0.0;
		varsta = 0;
	}
	Persoana(char* nume, double greutate, int varsta) {
		if (this->nume != NULL)
			delete[]this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->greutate = greutate;
		this->varsta = varsta;
	}

	Persoana(const Persoana& p) {	// copy constr.
		if (nume != NULL)
			delete[]nume;
		this->nume = new char[strlen(p.nume) + 1];
		strcpy(nume, p.nume);
		greutate = p.greutate;
		varsta = p.varsta;
	}

	Persoana& operator=(const Persoana& p) {
		if(this != &p) {
			if (nume != NULL)
				delete[]nume;
			nume = new char[strlen(p.nume) + 1];
			strcpy(nume, p.nume);
			greutate = p.greutate;
			varsta = p.varsta;
		}
		return *this;
	}

	char* getNume() {
		return nume;
	}

	double getGreutate() {
		return greutate;
	}
	int getVarsta() {
		return varsta;
	}
	void setNume(char *nume) {
		strcpy(this->nume, nume);
	}
	void setGreutate(double g) {
		greutate = g;
	}

	void setVarsta(int v) {
		varsta = v;
	}
	
	void display() {
		cout << "\n Nume: " << nume;
		cout << "\n Greutate: " << greutate;
		cout << "\n Varsta: " << varsta;
	}
	~Persoana() {
		delete[]nume;
	}
};


class Analize {
	Persoana* p;
	int n;
public:
	Analize() {
		p = new Persoana[dim];
		n = dim;
	}
	Analize(int j) {
		p = new Persoana[j];
		n = j;
	}
	void introdu() {
		int j;
		char nume[maxi];
		double greutate;
		int varsta;
		for (j = 0; j < n; j++) {
			cout << "\n Datele pentru persoana: " << j + 1; cout << "\n Nume: ";
			cin.get();
			cin.getline(nume, maxi);
			cout << " Greutate: ";
			cin >> greutate;
			cout << " Varsta: ";
			cin >> varsta;
			Persoana aux;
			aux.setNume(nume);
			aux.setGreutate(greutate);
			aux.setVarsta(varsta);
			p[j] = aux;
		}
	}
	void operator[ ](char* nume) {
		int j;
		bool gasit = false;
		for (j = 0; j < n; j++)
			if (strcmp(nume, p[j].getNume()) == 0) {
				p[j].display();
				gasit = true;
			}
		if (!gasit)
			cout << "\n Nu au fost gasite persoane care sa corespunda cu acest nume!\n";
	}
	void operator[ ](double greutate) {
		int j;
		bool gasit = false;
		for (j = 0; j < n; j++)
			if (greutate == p[j].getGreutate()) {
				p[j].display();
				gasit = true;
			}
		if (!gasit)
			cout << "\n Nu au fost gasite persoane care sa corespunda cu aceasta greutate!\n";
	}
	void operator[ ](int varsta) {
		int j;
		bool gasit = false;
		for (j = 0; j < n; j++)
			if (varsta == p[j].getVarsta()) {
				p[j].display();
				gasit = true;
			}
		if (!gasit)
			cout << "\n Nu au fost gasite persoane care sa corespunda cu aceasta varsta!\n";
	}
	void displayEverything() {
		for (int i = 0; i < n; i++) {
			cout << "\n";
			p[i].display();
		}
	}

	int sort(char c);

	~Analize() {
		delete[]p;
	}

};

int Analize::sort(char c) {
	switch (toupper(c)) {
	case 'V': {
		cout << "\n Persoane in functie de varsta (descrescator): ";
		for (int i = 0; i < n - 1; i++) {
			for (int j = i+1; j < n; j++) {
				if (p[i].getVarsta() < p[j].getVarsta()) {
					Persoana aux(p[i]);
					p[i] = p[j];
					p[j] = aux;
				}
			}
		}
		displayEverything();
		break; }
	case 'G': {
		cout << "\n Persoane in functie de greutate (descrescator): ";
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (p[i].getGreutate() < p[j].getGreutate()) {
					Persoana aux(p[i]);
					p[i] = p[j];
					p[j] = aux;
				}
			}
		}
		displayEverything();
		break; }
	case 'N': {
		cout << "\n Persoane in functie de nume (invers alfabetic): ";
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (strcmp(p[i].getNume(),p[j].getNume())<0) {
					Persoana aux(p[i]);
					p[i] = p[j];
					p[j] = aux;
				}
			}
		}
		displayEverything();
		break; }
	case 'E': return 0;
	default: {cout << "\n Comanda necunoscuta, introduceti din nou!"; break; }
	}
	
}

//main( )

int main() {
	int n;
	char c;
	char nume[maxi];
	double greutate;
	int varsta;
	cout << "\n Cate persoane? ";
	cin >> n;
	Analize a(n);
	a.introdu();
	cout << " Cautare dupa (v = varsta, g = greutate, n = nume, e=exit): ";
	bool flag = true;
	while (flag) {

		cout << "\n Optiunea (v = varsta, g = greutate, n = nume, e=exit): ";

		cin >> c;
		switch (toupper(c)) {
		case 'V': { cout << "\n Varsta: "; cin >> varsta; a[varsta]; break; }
		case 'G': { cout << "\n Greutate: "; cin >> greutate; a[greutate]; break; }
		case 'N': {cin.get(); cout << "\n Nume: "; cin.getline(nume, maxi); a[nume]; break; }
		case 'E': {flag = false; break; }
		default: {cout << "\n Comanda necunoscuta, introduceti din nou! "; break;
		}
		}
	}


	cin.get();
	cout << "\n Sortare si afisare in functie de (v = varsta, g = greutate, n = nume, e=exit): ";
	
	cin >> c;
	while (a.sort(c)) {
		cout << "\n Optiunea (v = varsta, g = greutate, n = nume, e=exit): ";
		cin >> c;
	}
}

