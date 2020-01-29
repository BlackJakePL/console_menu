#pragma once
#ifndef _Src_h
#define _Src_h
#include <string>
#include <iostream>


using namespace std;


class Cursor					//definicja klasy Cursor musi sie znajdowac w pliku Row.h poniewaz w pliku Navi.h generowalo bledy
{
	int val;
public:
	void CursorUp(int n);		//Wybiera opcje zaleznie od ilosci wierszy dostepnych w danym menu
	void CursorDown(int n);		//Wybiera opcje zaleznie od ilosci wierszy dostepnych w danym menu
	int getCursor();
	Cursor();

};

class Row						//klasa pocji ktora moze przybrac tylko stan on/off
{
protected:
	int id;
	int value;
	string text;
public:
	Row* subOpt;
	virtual void right();
	virtual void left();
	virtual void display();
	void setText(string text);
	void setid(int text);
	string getText();
	int getId();
	int getValue();
	Row();
	Row(string txt);
	~Row();
};


class Opt :public Row	//klasa opcji ktora moze przybierac wartosci od -10 do 10
{

public:
	Opt();
	Opt(string txt);
	~Opt();
	virtual void right()override;
	virtual void left()override;
	virtual void display()override;
};
//=================================================================================
void Display(Row** tab, int nr, string state[], Cursor* ptr);
void Display(Row* tab, int nr, string state[], Cursor* ptr);	//tablica		ilosc elementow w tablicy	rodzaj stanow	wskaznik na aktualnie wybrany element 
//=================================================================================

class SubOpt : public Row							// klasa ktora zaweira dowolna ilosc podopcji
{
	bool warunek = true;
	Cursor* sPtr;
	int optNr;
public:
	virtual void right()override;
	virtual void left()override;
	virtual void display()override;
	SubOpt(string txt, int n, int sw);
	~SubOpt();
	int getoptNr();

};
class BarOpt :public Row
{
public:
	BarOpt();
	BarOpt(string txt);						//opcja z paskiem 
	virtual void right()override;
	virtual void left()override;
	virtual void display()override;
};



#endif // !_Row_h
