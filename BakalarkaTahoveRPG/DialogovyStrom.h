#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Quest;
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
	void zmazMoznost(DialogVolba* paVolba);
protected:
	string text;
	vector<DialogVolba*> dialogoveMoznosti;

};


class DialogovyStrom
{
public:
	DialogovyStrom();


	void DialogovyStrom::pridajMoznost(DialogVolba* paVolba, DialogPolozka* paPolozka);
	void DialogovyStrom::zmazMoznost(DialogVolba* paVolba, DialogPolozka* paPolozka);
	void Setdialogquest(Quest* paQuest);

	void init();
	DialogStav Getstav();
	DialogPolozka* Getaktualnapolozka();
	void vlozPolozku(DialogPolozka* paPolozka);
	int zacniDialog();
	int zmenPolozku(int moznost);
	~DialogovyStrom();
private:
	Quest* dialogQuest;
	DialogStav stav;
	DialogPolozka *aktualnaPolozka;
	vector<DialogPolozka *> castiDialogu;
};
