/******************************************
Algoritmus radkoveho seminkoveho vyplnovani
Input: cesta k souboru s hranici

Output: Vyplnena oblast zadana hranici
        Plocha oblasti
******************************************/

#include "fill.h"

/*****************************************************************************/

int main(int argc, char *argv[])
{
	EdgeMap edgeMap;
	ushort area = 0;
	Error ok;

	// Nacitani a kontrola argumentu z prikazove radky
	if(argc != 2)
	{
		ok.setError(Error::E_USAGE);
		cout << ok << endl;
		return ok.getError();
	}

	// Nacteni hranice ze souboru argv[1]
	ok = edgeMap.Load(argv[1]);
	if(!ok)
	{
		cout << ok << endl;
		return ok.getError();
	}

	// Vypsani pred vyplnenim
	cout << "Zadana mapa hran:" << endl;
	edgeMap.Print();
	cout << endl;

	// Vyplneni oblasti zadane hranici
	ok = edgeMap.Fill(area);
	if(!ok)
	{
		cout << ok << endl;
		return ok.getError();
	}

	// Vypsani spocitanych udaju
	cout << "Vyplnena mapa hran:" << endl;
	ok = edgeMap.Print();
	if(!ok)
	{
		cout << ok << endl;
		return ok.getError();
	}
	cout << "\nVyplnena plocha je " << area << " znaku." << endl;

	return 0;
}

/*****************************************************************************/
