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
	string text;
	vector<DialogVolba> dialogoveMoznosti;

};


class DialogovyStrom
{
public:
	DialogovyStrom();

	void init();
	void destroyTree();
	DialogStav Getstav();
	DialogPolozka* Getaktualnapolozka();
	int zacniDialog();
	int zmenPolozku(int moznost);
	~DialogovyStrom();
private:
	DialogStav stav;
	DialogPolozka *aktualnaPolozka;
	vector<DialogPolozka *> castiDialogu;
};
