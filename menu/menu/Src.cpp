#include "Src.h"
#include <iostream>
#include <Windows.h>

using namespace std;

//==============================================================================================================

HANDLE grip = GetStdHandle(STD_OUTPUT_HANDLE);	//uchwyt do zmiany koloru tekstu w konsoli
int color = 10;									//definiuje kolor tekstu w konsoli
int def = 1;									//domyslny koloc tekstu w konsoli
using namespace std;


void Display(Row** tab, int nr, string state[], Cursor* ptr)
{
	system("cls");

	for (int i = 0; i < nr; i++)
	{
		if (i == ptr->getCursor())
		{
			SetConsoleTextAttribute(grip, color);
		}
		tab[i]->display();

		if (i == ptr->getCursor())
		{
			SetConsoleTextAttribute(grip, def);
		}
	}
}
void Display(Row* tab, int nr, string state[], Cursor* ptr)
{
	system("cls");

	for (int i = 0; i < nr; i++)
	{
		if (i == ptr->getCursor())
		{
			SetConsoleTextAttribute(grip, color);
		}
		tab[i].display();

		if (i == ptr->getCursor())
		{
			SetConsoleTextAttribute(grip, def);
		}
	}
}

/* ====================== */
/*|			Cursor		 |*/
/* ====================== */

void Cursor::CursorUp(int n)
{
	if (this->val == 0)
	{
		this->val = n - 1;
	}
	else
	{
		this->val--;
	}
}

void Cursor::CursorDown(int n)
{
	if (this->val == n - 1)
	{
		this->val = 0;
	}
	else
	{
		this->val++;
	}
}

int Cursor::getCursor()
{
	return this->val;
}
Cursor::Cursor()
{
	val = 0;
}

//==================================================================================



int idx = 0;
string state1[2] = { "off", "on" };

void Row::setText(string text)
{
	this->text = text;
}
void Row::setid(int n)
{
	this->id = id;
}
Row::Row()
{
	this->id = idx;
	this->value = 0;
	this->text = "";
	idx++;
}
Row::Row(string txt)
{
	this->id = idx;
	this->value = 0;
	this->text = txt;
	idx++;
}
Row::~Row()
{

}
string Row::getText()
{
	return this->text;
}
int Row::getId()
{
	return this->id;
}
int Row::getValue()
{
	return this->value;
}
void Row::right()
{
	if (this->value == 0)
	{
		this->value++;
	}
	else
	{
		this->value--;
	}
}
void Row::left()
{
	if (this->value == 0)
	{
		this->value++;
	}
	else
	{
		this->value--;
	}
}
void Row::display()
{
	cout << this->text << " " << this->value << endl;
}

/* ====================== */
/*|			OPT			 |*/
/* ====================== */
Opt::Opt()
	:Row()
{
}
Opt::Opt(string txt)
	: Row(txt)
{
}
Opt::~Opt()
{

}
void Opt::right()
{
	if (this->value == 10)
	{
		this->value = -10;
	}
	else
	{
		this->value++;
	}
}
void Opt::left()
{
	if (this->value == -10)
	{
		this->value = 10;
	}
	else
	{
		this->value--;
	}
}
void Opt::display()
{
	cout << this->text << "\t" << "<" << this->value << ">" << endl;
}

/* ====================== */
/*|			SubOpt		 |*/
/* ====================== */

SubOpt::SubOpt(string txt, int n, int sw)
	:Row(txt)
{
	switch (sw)
	{

	case 1:
	{
		this->sPtr = new Cursor;
		this->optNr = n;
		this->subOpt = new Row[this->optNr];
		break;
	}
	case 2:
	{
		this->sPtr = new Cursor;
		this->optNr = n;
		this->subOpt = new Opt[this->optNr];
		break;
	}
	case 3:
	{
		this->sPtr = new Cursor;
		this->optNr = n;
		this->subOpt = new BarOpt[this->optNr];
		break;
	}
	}
}

void SubOpt::right()
{
	this->warunek = true;
	system("cls");

	Display(this->subOpt, this->optNr, state1, this->sPtr);

	while (this->warunek)
	{
		if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0))
		{
			this->warunek = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & (0x8000 != 0))
		{
			this->subOpt[this->sPtr->getCursor()].right();
			Display(this->subOpt, this->optNr, state1, this->sPtr);
		}
		if (GetAsyncKeyState(VK_UP) & (0x8000 != 0))
		{
			this->sPtr->CursorUp(this->getoptNr());						//Wybiera opcje zaleznie od ilosci wierszy dostepnych w danym menu
			Display(this->subOpt, this->optNr, state1, this->sPtr);
		}
		if (GetAsyncKeyState(VK_DOWN) & (0x8000 != 0))
		{
			this->sPtr->CursorDown(this->getoptNr());						//Wybiera opcje zaleznie od ilosci wierszy dostepnych w danym menu
			Display(this->subOpt, this->optNr, state1, this->sPtr);
		}
	}

}
void SubOpt::left()
{

}
void SubOpt::display()
{
	cout << this->text << " >>>" << endl;
}
int SubOpt::getoptNr()
{
	return this->optNr;
}

/* ====================== */
/*|			BarOpt		 |*/
/* ====================== */
void BarOpt::left()
{
	if (this->value >= 1)
	{
		this->value--;
	}
}
void BarOpt::right()
{
	if (this->value < 10)
	{
		this->value++;
	}
}
void BarOpt::display()
{
	cout << this->text << " ";
	for (int i = 0; i < 10; i++)
	{
		if (i < this->value)
		{
			cout << "*";
		}
		else
		{
			cout << ".";
		}
	}
	cout << endl;
}
BarOpt::BarOpt()
	:Row()
{

}
BarOpt::BarOpt(string txt)
	: Row(txt)
{
	this->value = 0;
}