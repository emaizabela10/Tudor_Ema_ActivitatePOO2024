#include <iostream>

using namespace std;

class Masina {
public:
	int nrRoti;
	string marca;
	float pret;
	static int TVA; //apartin clasei
	const int anFabricatie; //nu se poate schimba, deci il facem const; apartin obiectelor

	//constructor; initializam toate atributele
	Masina() :anFabricatie(2024), nrRoti(4) //dupa : este lista de initializare; anFabricatie il punem pt ca e constant
	{
		this->marca = "Dacia";
		this->pret = 5000;
	}

	Masina(int _nrRoti, string marca, float pret, int an) :anFabricatie(an) {
		this->nrRoti = _nrRoti;
		this->marca = marca; //atributul e in stanga this->marca = marca (parametrul)
		this->pret = pret;
	}

	void afisare() {
		cout << "Marca:" << this->marca << endl;
		cout << "Nr. roti:" << this->nrRoti << endl;
		cout << "Pret:" << this->pret << endl;
		cout << "TVA:" << this->TVA << endl;
		cout << "An fabricatie:" << this->anFabricatie << endl;
	}

	float calculeazaPretTotal() {
		return this->pret + (this->pret * ((float)Masina::TVA / 100)); //this->TVA;(float) ca sa transformam din int in float sau 100.0f
	}

	//metoda se afla in interiorul clasei si primeste this, iar in functie statica nu merge this?
	static void modificaTVA(int noulTVA) {
		if (noulTVA > 0) {
			Masina::TVA = noulTVA;
		}
	}

	static float calculeazaPretTotalVector(int nrMasini, Masina* vector) {
		float pretTotal = 0;
		for (int i = 0; i < nrMasini; i++) {
			pretTotal += vector[i].calculeazaPretTotal();
		}
		return pretTotal;
	}


};

int Masina::TVA = 19; //asa initializam atributele statice

int main() {
	Masina m1; //am creat masina
	m1.afisare(); //am afisat masina

	Masina m2(4, "Audi", 7000, 2020);
	m2.afisare();

	Masina::modificaTVA(21);

	Masina* pointer = new Masina(6, "Volvo", 20000, 2022); //punem cu new sa accesam din zona de stack?/ & accesam zona din heap?
	pointer->afisare(); //asa afisam pointerul de mai sus?

	cout << "Pret total:" << pointer->calculeazaPretTotal();

	int nrMasini = 3;
	Masina* vector;
	vector = new Masina[nrMasini];

	for (int i = 0; i < nrMasini; i++) {
		vector[i].afisare();
	}
	//-> dereferentiere+accesare; [] deplasare+dereferentiere; . accesare?

	cout << "Pret total flota:" << Masina::calculeazaPretTotalVector(nrMasini, vector) << endl;

	return 0;
}