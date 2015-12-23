#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class DialogPolozka;

class DialogVolba {
public:

	DialogVolba(string paText, int paNavratovaHodnota, DialogPolozka *paNextNode);
	string text;
	int navratovaHodnota;
	DialogPolozka *dalsiaPolozka;
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

	int zacniDialog();

	~DialogovyStrom();
private:
	vector<DialogPolozka *> castiDialogu;
};
