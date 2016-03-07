#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Hrac;
enum DialogStav { VYTVORENY, INIT, BEZI, SKONCIL };

class DialogPolozka;

class DialogVolba {
public:
	DialogVolba(string paText, int dalsia);
	virtual string Gettext();
	int dalsia;
	virtual void akcia(Hrac* hrac);
private:
	string text;

};


class DialogPolozka {
public:
	DialogPolozka(string paText);
	~DialogPolozka();
	virtual int pocetMoznosti();
	void pridajMoznost(DialogVolba* paVolba);
	virtual string Gettext();
	virtual DialogVolba* Getvolba(int paIndex);
protected:
	string text;
	vector<DialogVolba*> dialogoveMoznosti;

};


class DialogovyStrom
{
public:
	DialogovyStrom();

	void init();
	DialogStav Getstav();
	DialogPolozka* Getaktualnapolozka();
	void vlozPolozku(DialogPolozka* paPolozka);
	int zacniDialog();
	int zmenPolozku(int moznost);
	~DialogovyStrom();
private:
	DialogStav stav;
	DialogPolozka *aktualnaPolozka;
	vector<DialogPolozka *> castiDialogu;
};
