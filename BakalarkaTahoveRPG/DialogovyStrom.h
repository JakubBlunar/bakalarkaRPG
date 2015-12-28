#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum DialogStav {VYTVORENY,INIT, BEZI, SKONCIL };

class DialogPolozka;

class DialogVolba {
public:
	DialogVolba(string paText, int dalsia);
	string text;
	int dalsia;
};


class DialogPolozka {
public:
	DialogPolozka(string paText);
	~DialogPolozka();
	int pocetMoznosti();
	void pridajMoznost(DialogVolba* paVolba);
	string Gettext();
	DialogVolba* Getvolba(int paIndex);
private:
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
