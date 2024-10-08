#include <iostream>

using namespace std;

struct CoordonateGPS
{
	int latitudine;
	int longitudine;
	float altitudine; //folosim float pt ca are mai multa exactitate in date (ex: 35.6)
	string locatie; //sir de caractere, "a" - sir de caractere; 'a' - char caracter, un singur caracter (un octet)
};

//tip returnat, numele fc, ([parametrul]), {} - corpul functiei
void afisareCoordonateGPS(CoordonateGPS l) //void nu returneaza nimic in schimb
{
	cout << "Latitudine: " << l.latitudine << endl;
	cout << "Longitudine: " << l.longitudine << endl;
	cout << "Altitudine: " << l.altitudine << endl;
	cout << "Locatie: " << l.locatie << endl;
}
/* cout = ne permite sa afisam ceva pe ecran
   << = pt a insera valori in fluxul de iesire; cuvantul "Latitudine" apare pe ecran
   l.latitudine = este valoarea, numarul
   endl = e ca si cum ai da enter pe tastatura
*/

//modul 1
void modificaAltitudine(CoordonateGPS* l, float nouaAltitudine)
{
	l->altitudine = nouaAltitudine;
}
//CoordonateGPS* = este un POINTER catre o structura de tip CoordonateGPS
//un POINTER (l) este o variabila care stocheaza adresa de memorie a unei alte variabile 
// -> este folosit pentru a accesa membrii unei structuri printr un pointer

//modul 2
void modificaAltitudineRef(CoordonateGPS& l, float nouaAltitudine)
{
	l.altitudine = nouaAltitudine;
}
//CoordonateGPS& = o REFERINTA la o structura de tip CoordonateGPS
//cand se modifica o referinta (l), se modifica direct variabila la care se refera

CoordonateGPS initializareCoordonate(int latitudine, int longitudine, float altitudine, string locatie)
{
	CoordonateGPS l;
	l.latitudine = latitudine;
	l.longitudine = longitudine;
	l.altitudine = altitudine;
	l.locatie = locatie;
	return l;
}

int main()
{
	CoordonateGPS l;
	l.latitudine = 46;
	l.longitudine = 22;
	l.altitudine = 1010;
	l.locatie = "Predeal";

	afisareCoordonateGPS(l);

	CoordonateGPS l2;
	cout << "Introduceti latitudinea: ";
	cin >> l2.latitudine;
	// cin = (input) folosim pt a citi date de la tastatura
	// >> = operator de extragere date din fluxul de intare
	cout << "Introduceti longitudine: ";
	cin >> l2.longitudine;
	cout << "Introduceti altitudine: ";
	cin >> l2.altitudine;
	cout << "Introduceti locatia: ";
	cin >> l2.locatie;

	afisareCoordonateGPS(l2);
	modificaAltitudine(&l2, -2000);
	modificaAltitudineRef(l2, 3000);
	afisareCoordonateGPS(l2);

	int a = 20;
	int* pa = &a;
	int* p = new int(40);

	return 0;
}