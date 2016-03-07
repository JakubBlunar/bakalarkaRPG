#include "DialogovyStrom.h"

#include <iostream>
#include "Loader.h"
#include "Hra.h"

DialogPolozka::DialogPolozka(string paText) {
	text = paText;
}

string DialogPolozka::Gettext() {
	return text;
}

DialogPolozka::~DialogPolozka() {
	for (unsigned int i = 0; i < dialogoveMoznosti.size(); i++)
	{
		delete dialogoveMoznosti[i];
	}
}

void DialogPolozka::pridajMoznost(DialogVolba* paVolba) {
	dialogoveMoznosti.push_back(paVolba);
}


int DialogPolozka::pocetMoznosti() {
	return dialogoveMoznosti.size();
}

DialogVolba* DialogPolozka::Getvolba(int paIndex) {
	if (paIndex >= 0 && (unsigned int)paIndex< (unsigned int)dialogoveMoznosti.size()) {
		return dialogoveMoznosti[paIndex];
	}
	return nullptr;
}

string DialogVolba::Gettext() {
	return text;
}


void DialogVolba::akcia(Hrac* hrac) {
	
}

DialogVolba::DialogVolba(string paText, int dalsia) {
	text = paText;
	this->dalsia = dalsia;
}

DialogovyStrom::DialogovyStrom()
{
	aktualnaPolozka = nullptr;
	stav = DialogStav::VYTVORENY;
}


DialogovyStrom::~DialogovyStrom()
{
	for (unsigned int i = 0; i < castiDialogu.size(); i++) {
		delete castiDialogu[i];
	}
	castiDialogu.clear();
}

DialogStav DialogovyStrom::Getstav() {
	return stav;
}


void DialogovyStrom::init() {
	//prva node ktoru vlozim do stromu bude prva
	aktualnaPolozka = castiDialogu[0];
	stav = DialogStav::INIT;
}

int DialogovyStrom::zmenPolozku(int moznost) {

	if (moznost >= 0 && moznost< aktualnaPolozka->pocetMoznosti()) {
		Loader* loader = Loader::Instance();
		aktualnaPolozka->Getvolba(moznost)->akcia(loader->Gethra()->GetHrac());
		if (aktualnaPolozka->Getvolba(moznost)->dalsia == -1) {
			stav = DialogStav::SKONCIL;
			return 0;
		}

		aktualnaPolozka = castiDialogu[aktualnaPolozka->Getvolba(moznost)->dalsia];
		return 0;
	}
	else return -1;
}

DialogPolozka* DialogovyStrom::Getaktualnapolozka() {
	return aktualnaPolozka;
}

int DialogovyStrom::zacniDialog() {
	if (castiDialogu.size() == 0) {
		stav = DialogStav::SKONCIL;
		return -1;
	}
	else {
		stav = DialogStav::BEZI;
		return -1;
	}
}

void DialogovyStrom::vlozPolozku(DialogPolozka* paPolozka) {
	castiDialogu.push_back(paPolozka);
}