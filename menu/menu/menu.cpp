#include <iostream>
#include<Windows.h>
#include "Src.h"

using namespace std;

bool warunek = true;
string state[2] = { "off", "on" };
const int n = 7;

int main()
{
	Cursor* ptr = new Cursor;

	Row** tab = new Row * [n];				// tablica wskaznikow przechowuje wskazniki na obiekty danego typu
	tab[0] = new Row("OPTION ");				//nadawanie poprzez konstruktor nazw poszegolnym opcja
	tab[1] = new Row("OPTION ");
	tab[2] = new SubOpt("Subopcja", 3, 1);
	tab[2]->subOpt[0].setText("podopcja 1");	// nadawanie nazwy podopcji przez funkcje
	tab[2]->subOpt[1].setText("podopcja 2");
	tab[2]->subOpt[2].setText("podopcja 3");
	tab[3] = new SubOpt("Subopcja", 3, 2);
	tab[3]->subOpt[0].setText("podopcja 1");	// nadawanie nazwy podopcji przez funkcje
	tab[3]->subOpt[1].setText("podopcja 2");
	tab[3]->subOpt[2].setText("podopcja 3");
	tab[4] = new SubOpt("Subopcja", 3, 3);
	tab[4]->subOpt[0].setText("podopcja 1");	// nadawanie nazwy podopcji przez funkcje
	tab[4]->subOpt[1].setText("podopcja 2");
	tab[4]->subOpt[2].setText("podopcja 3");
	tab[5] = new Opt("OPTION ");
	tab[6] = new BarOpt("OPTION ");


	cout << "strzalka w lewo zmniejsza wartosc lub cofa do poprzedniego menu" << endl;
	cout << "sztrzalki gora/dol sluza do wybrania opcji" << endl;
	cout << "strzalka w prawo zwiekrza wartosc aktualnej opcji lub przechodzi do podmenu danej opcji" << endl;
	cout << "zielony kolor tekstu sybmbolizuje aktualnie wybrana opcje" << endl;
	cout << "nacisnij enter aby kontynuowac...";

	getchar();

	Display(tab, n, state, ptr);

	while (warunek)
	{
		if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0))
		{
			tab[ptr->getCursor()]->left();			//wykonuje akcje dla aktualnie wybranej opcji
			Display(tab, n, state, ptr);
		}
		if (GetAsyncKeyState(VK_RIGHT) & (0x8000 != 0))
		{
			tab[ptr->getCursor()]->right();			//wykonuje akcje dla aktualnie wybranej opcji
			Display(tab, n, state, ptr);
		}
		if (GetAsyncKeyState(VK_UP) & (0x8000 != 0))
		{
			ptr->CursorUp(n);
			Display(tab, n, state, ptr);				//Wybiera opcje zaleznie od ilosci wierszy dostepnych w danym menu
		}
		if (GetAsyncKeyState(VK_DOWN) & (0x8000 != 0))
		{
			ptr->CursorDown(n);						//Wybiera opcje zaleznie od ilosci wierszy dostepnych w danym menu
			Display(tab, n, state, ptr);
		}
		if (GetAsyncKeyState(VK_RCONTROL))
		{
			break;
		}
	}

	delete tab[0];
	delete tab[1];
	delete tab[2];
	delete tab[3];
	delete tab[4];
	delete[]tab;
	delete ptr;
}
