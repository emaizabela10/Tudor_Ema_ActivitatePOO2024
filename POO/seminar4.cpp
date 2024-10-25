#include <iostream>

using namespace std;

class Masina {
private:
	int nrRoti;
	string* producatori;
	string marca;
	float pret;
	static int TVA; //apartin clasei
	const int anFabricatie; //nu se poate schimba, deci il facem const; apartin obiectelor

public:
	//constructor; initializam toate atributele
	Masina() :anFabricatie(2024), nrRoti(4) //dupa : este lista de initializare; anFabricatie il punem pt ca e constant
	{
		this->marca = "Dacia";
		this->pret = 5000;
		this->producatori = NULL;
	}

	Masina(int _nrRoti, string marca, float pret, int an) :anFabricatie(an) {
		this->nrRoti = _nrRoti;
		this->marca = marca; //atributul e in stanga this->marca = marca (parametrul)
		this->pret = pret;
		this->producatori = new string[this->nrRoti];
		for (int i = 0; i < this->nrRoti; i++)
		{
			this->producatori[i] = "Michelin";
		}
	}

	Masina(const Masina& m) :anFabricatie(m.anFabricatie)
	{
		this->nrRoti = m.nrRoti;
		this->marca = m.marca;
		this->pret = m.pret;
		this->producatori = new string[m.nrRoti];
		for (int i = 0; i < m.nrRoti; i++)
		{
			this->producatori[i] = m.producatori[i];
		}
	}

	~Masina() // cand avem ~ nu scriem cout niciodata
	{
		if (this->producatori != NULL)
		{
			delete[]this->producatori;
		}
	}

	string getMarca()
	{
		return this->marca;
	}

	void setMarca(string marca)
	{
		if (marca.length() > 2)
		{
			this->marca = marca;
		}
	}

	float getPret()
	{
		return this->pret;
	}

	void setPret(float pret)
	{
		if (pret > 0)
		{
			this->pret = pret;
		}
	}
	string* getProducatori()
	{
		return this->producatori;
	}

	string getProducator(int index)
	{
		if (index >= 0 && index < this->nrRoti)
		{
			return this->producatori[index];
		}
		else
		{
			return "NU a fost gasit.";
		}

	}

	void setNrRoti(int nrRoti, string* producatori)
	{
		if (nrRoti > 0)
		{
			this->nrRoti = nrRoti;
			if (this->producatori != NULL)
			{
				delete[]this->producatori;
			}
			this->producatori = new string[nrRoti];
			for (int i = 0; i < nrRoti; i++)
			{
				this->producatori[i] = producatori[i];
			}

		}
	}

	void afisare() {
		cout << "Marca:" << this->marca << endl;
		cout << "Nr. roti:" << this->nrRoti << ":";
		if (this->producatori != NULL)
		{
			for (int i = 0; i < this->nrRoti; i++)
			{
				cout << this->producatori[i] << ",";
			}
		}
		cout << endl;
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

int main()
{
	Masina m;
	cout << m.getMarca() << endl;
	m.setMarca("Audi");
	cout << m.getMarca() << endl;
	m.afisare();

	Masina m2(4, "BMW", 45000, 2021);
	m2.afisare();
	cout << endl << endl;

	cout << m2.getProducatori()[1] << endl;
	cout << m2.getProducator(1) << endl;

	m2.setNrRoti(6, new string[6]{ "Michelin","Continental","Bridgestone", "Pirelli","Hankoover", "POO" });
	cout << m2.getProducator(3);

	Masina m3(m2);
	Masina m4 = m2;
	cout << m4.getProducator(2);

	return 0;

}