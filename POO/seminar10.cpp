#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Masina {
private:
	int nrRoti;
	string* producatori;
	string marca;
	float pret;
	static int TVA;
	const int anFabricatie;
public:
	Masina() :anFabricatie(2024), nrRoti(4) {
		this->marca = "Dacia";
		this->pret = 5000;
		this->producatori = NULL;
	}
	Masina(int _nrRoti, string marca, float pret, int an) :anFabricatie(an) {
		this->nrRoti = _nrRoti;
		this->marca = marca;
		this->pret = pret;
		this->producatori = new string[this->nrRoti];
		for (int i = 0; i < this->nrRoti; i++) {
			this->producatori[i] = "Michelin";
		}
	}
	Masina(const Masina& m) :anFabricatie(m.anFabricatie) {
		this->nrRoti = m.nrRoti;
		this->marca = m.marca;
		this->pret = m.pret;
		this->producatori = new string[m.nrRoti];
		for (int i = 0; i < m.nrRoti; i++) {
			this->producatori[i] = m.producatori[i];
		}
	}
	Masina operator=(const Masina& m) {
		if (this != &m) {
			this->nrRoti = m.nrRoti;
			this->marca = m.marca;
			this->pret = m.pret;
			if (this->producatori != NULL) {
				delete[]this->producatori;
			}
			this->producatori = new string[m.nrRoti];
			for (int i = 0; i < m.nrRoti; i++) {
				this->producatori[i] = m.producatori[i];
			}
		}
		return *this;
	}


	~Masina() {
		if (this->producatori != NULL) {
			delete[]this->producatori;
		}
	}

	Masina operator+(const Masina& m) const {
		Masina temp = *this;
		temp.pret = this->pret + m.pret;
		return temp;
	}

	Masina operator+=(Masina m) {
		this->pret = this->pret + m.pret;
		return *this;
	}

	Masina operator+=(float adaosPret) {
		this->pret += adaosPret;
		return *this;
	}

	Masina operator+(float adaosPret)const {
		Masina temp = *this;
		temp.pret += adaosPret;
		return temp;
	}

	friend Masina operator+(float adaosPret, Masina m) {
		Masina temp = m;
		temp.pret += adaosPret;
		return temp;
	}
	explicit operator float()
	{
		return calculeazaPretTotal();
	}

	string& operator[](int index) {
		if (index >= 0 && index < this->nrRoti) {
			return this->producatori[index];
		}
		else {
			throw "Indexul este in afara limitelor.";
		}
	}
	explicit operator int()
	{
		return this->nrRoti;
	}
	string getMarca() {
		return this->marca;
	}
	void setMarca(string marca) {
		if (marca.length() > 2) {
			this->marca = marca;
		}
	}
	float getPret() {
		return this->pret;
	}
	void setPret(float pret) {
		if (pret > 0) {
			this->pret = pret;
		}
	}
	string* getProducatori() {
		return this->producatori;
	}

	string getProducator(int index) {
		if (index >= 0 && index < this->nrRoti) {
			return this->producatori[index];
		}
		else {
			return "NU a fost gasit.";
		}
	}

	int getNrRoti() {
		return this->nrRoti;
	}
	void setNrRoti(int nrRoti, string* producatori) {
		if (nrRoti > 0) {
			this->nrRoti = nrRoti;
			if (this->producatori != NULL) {
				delete[]this->producatori;
			}
			this->producatori = new string[nrRoti];
			for (int i = 0; i < nrRoti; i++) {
				this->producatori[i] = producatori[i];
			}
		}
	}

	void afisare() {
		cout << "Marca:" << this->marca << endl;
		cout << "Nr roti:" << this->nrRoti << ": ";
		if (this->producatori != NULL) {
			for (int i = 0; i < this->nrRoti; i++) {
				cout << this->producatori[i] << ", ";
			}
		}
		cout << endl;
		cout << "Pret:" << this->pret << endl;
		cout << "TVA:" << this->TVA << endl;
		cout << "An fabricatie:" << this->anFabricatie << endl;
	}

	float calculeazaPretTotal() {
		return this->pret + (this->pret * (Masina::TVA / 100.0f));
	}

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

	void scriereFisierBinar(fstream& fisier) {
		fisier.write((char*)&nrRoti, sizeof(int));
		for (int i = 0; i < nrRoti; i++) {
			int lungime = producatori[i].length();
			fisier.write((char*)&lungime, sizeof(int));
			fisier.write((char*)(producatori[i].c_str()), lungime * sizeof(char));
		}
		int lungime = marca.length();
		fisier.write((char*)&lungime, sizeof(int));
		fisier.write((char*)(marca.c_str()), lungime * sizeof(char));
		fisier.write((char*)&pret, sizeof(float));
	}

	void citesteFisierBinar(fstream& fisier) {
		fisier.read((char*)&nrRoti, sizeof(int));
		if (this->producatori) {
			delete[]this->producatori;
		}
		this->producatori = new string[nrRoti];
		for (int i = 0; i < nrRoti; i++) {
			int lungime = 0;
			fisier.read((char*)&lungime, sizeof(int));
			char buffer[50];
			fisier.read((char*)(&buffer), lungime * sizeof(char));
			buffer[lungime] = '\0';
			this->producatori[i] = buffer;
		}
		int lungime = 0;
		fisier.read((char*)&lungime, sizeof(int));
		fisier.read((char*)(marca.c_str()), lungime * sizeof(char));
		fisier.read((char*)&pret, sizeof(float));
	}

	bool operator<(Masina m) {
		return this->pret < m.pret;
	}
	friend istream& operator>>(istream& input, Masina& m) {
		cout << "Introduceti marca:";
		input >> m.marca;
		cout << "Nr roti:";
		input >> m.nrRoti;
		if (m.producatori != NULL) {
			delete[]m.producatori;
		}
		if (m.nrRoti > 0) {
			m.producatori = new string[m.nrRoti];
			cout << "Producatori:";
			for (int i = 0; i < m.nrRoti; i++) {
				input >> m.producatori[i];
			}
		}
		else {
			m.producatori = NULL;
		}
		cout << "Pret:";
		input >> m.pret;
		return input;
	}
	friend ifstream& operator>>(ifstream& input, Masina& m) {
		input >> m.marca;
		input >> m.nrRoti;
		if (m.producatori != NULL) {
			delete[]m.producatori;
		}
		if (m.nrRoti > 0) {
			m.producatori = new string[m.nrRoti];
			for (int i = 0; i < m.nrRoti; i++) {
				input >> m.producatori[i];
			}
		}
		else {
			m.producatori = NULL;
		}
		input >> m.pret;
		int an;
		input >> an;
		return input;
	}
	friend ostream& operator<<(ostream& output, Masina m);
	friend ofstream& operator<<(ofstream& output, Masina m) {
		output << m.marca << endl;
		output << m.nrRoti << endl;
		if (m.producatori != NULL) {
			for (int i = 0; i < m.nrRoti; i++) {
				output << m.producatori[i] << " ";
			}
		}
		output << endl;
		output << m.pret << endl;
		output << m.anFabricatie << endl;
		return output;
	}
};

int Masina::TVA = 19;

ostream& operator<<(ostream& output, Masina m) {
	output << "Marca:" << m.marca << endl;
	output << "Nr roti:" << m.nrRoti << ": ";
	if (m.producatori != NULL) {
		for (int i = 0; i < m.nrRoti; i++) {
			output << m.producatori[i] << ", ";
		}
	}
	output << endl;
	output << "Pret:" << m.pret << endl;
	output << "TVA:" << m.TVA << endl;
	output << "An fabricatie:" << m.anFabricatie << endl;
	return output;
}


class Tir :public Masina {

	float tonaj;
	char* tara;


public:

	Tir() : Masina(10, "Volvo", 100000, 2020) {
		this->tonaj = 20;
		this->tara = new char[strlen("Romania") + 1];
		strcpy_s(tara, strlen("Romania") + 1, "Romania");
	}

	Tir(const char* tara, float tonaj = 15) :Masina(10, "Volvo", 100000, 2020) {
		this->tara = new char[strlen(tara) + 1];
		strcpy_s(this->tara, strlen(tara) + 1, tara);
		this->tonaj = tonaj;
	}

	Tir(const char* tara, float tonaj, string marca, int nrRoti, float pret, string* producatori, int anFabricatie) :Masina(nrRoti, marca, pret, anFabricatie) {
		this->tara = new char[strlen(tara) + 1];
		strcpy_s(this->tara, strlen(tara) + 1, tara);
		this->tonaj = tonaj;
		setNrRoti(nrRoti, producatori);
	}
	Tir(const Tir& tir) :Masina(tir)
	{
		this->tara = new char[strlen(tir.tara) + 1];
		strcpy_s(this->tara, strlen(tir.tara) + 1, tir.tara);
		this->tonaj = tir.tonaj;
	}
	Tir& operator=(const Tir& tir)
	{
		if (&tir != this)
		{
			Masina::operator=(tir);
			if (this->tara != NULL) {
				delete[]this->tara;
			}
			this->tara = new char[strlen(tir.tara) + 1];
			strcpy_s(this->tara, strlen(tir.tara) + 1, tir.tara);
			this->tonaj = tir.tonaj;
		}
		return *this;
	}
	~Tir() {
		if (this->tara != NULL) {
			delete[]this->tara;
		}
	}
	float calculeazaMedieTonaj() {
		float medie = this->tonaj / this->getNrRoti();
		return medie;
	}

	explicit operator float() {
		return this->tonaj;
	}
	friend ostream& operator<<(ostream& consola, const Tir& tir) {
		consola << (Masina)tir;
		if (tir.tara) {
			consola << "Tara:" << tir.tara << endl;
		}
		consola << "Tonaj:" << tir.tonaj;
		return consola;
	}

	friend istream& operator>>(istream& input, Tir& tir) {
		//operator>>(input, (Masina&)tir);
		input >> (Masina&)tir;//de ce?
		char buffer[50];
		input >> buffer;
		if (tir.tara) {
			delete[]tir.tara;
		}
		tir.tara = new char[strlen(buffer) + 1];
		strcpy_s(tir.tara, strlen(buffer) + 1, buffer);
		cout << "Tonaj:";
		input >> tir.tonaj;
		return input;
	}
};



int main() {

	//ofstream fisier("fisier.txt", ios::app);
	//int nr_Roti = 4;
	///*string* prod = new string[nr_Roti];
	//prod[0] = "Michelin";
	//prod[1] = "Pirelli";
	//prod[2] = "Hankook";
	//prod[3] = "Bridgestone";
	//Masina m(nr_Roti, "Dacia", 5000.0f, 2020);
	//m.setNrRoti(nr_Roti, prod);
	//fisier << m;*/
	//Masina m2(4, "Ford", 200000.0f, 2021);
	//fisier << m2;
	//fisier.close();
	///*ifstream fisier2("fisier.txt", ios::in);
	//Masina m;
	//Masina m2;
	//fisier2 >> m;
	//fisier2 >> m2;
	//cout << m << endl;
	//cout << m2 << endl;
	//fisier2.close();*/

	int nr_Roti = 4;
	string* prod = new string[nr_Roti];
	prod[0] = "Michelin";
	prod[1] = "Pirelli";
	prod[2] = "Hankook";
	prod[3] = "Bridgestone";
	Masina masina(nr_Roti, "Dacia", 5000.0f, 2020);
	masina.setNrRoti(nr_Roti, prod);

	fstream fisierBinar("fisierBinar.txt", ios::binary | ios::out);
	masina.scriereFisierBinar(fisierBinar);
	fisierBinar.close();

	fstream fisierBinar1("fisierBinar.txt", ios::binary | ios::in);
	Masina masina1;
	masina1.citesteFisierBinar(fisierBinar1);
	cout << masina1;
	fisierBinar1.close();
}