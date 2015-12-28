#include "DialogovyStrom.h"

DialogPolozka::DialogPolozka(string paText) {
	text = paText;
}

DialogVolba::DialogVolba(string paText, int dalsia) {
	text = paText;
	this->dalsia = dalsia;
}

DialogovyStrom::DialogovyStrom()
{

	DialogPolozka *node0 = new DialogPolozka("Ahoj udatny bojovnik.");
	DialogPolozka *node1 = new DialogPolozka("Nechcem sa s tebou rozpravat");
	DialogPolozka *node2 = new DialogPolozka("Mam pre teba quest.");
	DialogPolozka *node3 = new DialogPolozka("Dostanes 5 goldov.");
	DialogPolozka *node4 = new DialogPolozka("Pozbieraj 10 konarov.");

	//node 0
	node0->dialogoveMoznosti.push_back(DialogVolba("Tin tang kungpao...", 1));
	node0->dialogoveMoznosti.push_back(DialogVolba("Ahoj.", 2));
	castiDialogu.push_back(node0);

	//node 1
	node1->dialogoveMoznosti.push_back(DialogVolba("Dobre :(", -1));
	castiDialogu.push_back(node1);

	//node2
	node2->dialogoveMoznosti.push_back(DialogVolba("Nechce sa mi.", -1));
	node2->dialogoveMoznosti.push_back(DialogVolba("Co treba spravit ?", 4));
	node2->dialogoveMoznosti.push_back(DialogVolba("Co za to ziskam? ", 3));
	castiDialogu.push_back(node2);

	//node3
	node3->dialogoveMoznosti.push_back(DialogVolba("Ok co teda treba spravit?", 4));
	node3->dialogoveMoznosti.push_back(DialogVolba("To sa mi nechce.", -1));
	castiDialogu.push_back(node3);

	//node4
	node4->dialogoveMoznosti.push_back(DialogVolba("Ok idem na to.", -1));
	node4->dialogoveMoznosti.push_back(DialogVolba("Nie.", -1));
	castiDialogu.push_back(node4);

	aktualnaPolozka = nullptr;
	stav = DialogStav::VYTVORENY;
}


DialogovyStrom::~DialogovyStrom()
{
	destroyTree();
}

DialogStav DialogovyStrom::Getstav() {
	return stav;
}


void DialogovyStrom::init() {
	//prva node ktoru vlozim do stromu bude prva
	aktualnaPolozka = castiDialogu[0];
	stav = DialogStav::INIT;
}

void DialogovyStrom::destroyTree() {
	for (int i = 0; i < castiDialogu.size(); i++) {
		delete castiDialogu[i];
	}
	castiDialogu.clear();
}

int DialogovyStrom::zmenPolozku(int moznost) {

	if (moznost >= 0 && aktualnaPolozka->dialogoveMoznosti.size()) {
		if (aktualnaPolozka->dialogoveMoznosti[moznost].dalsia == -1) {
			stav = DialogStav::SKONCIL;
			return 0;
		}

		aktualnaPolozka = castiDialogu[aktualnaPolozka->dialogoveMoznosti[moznost].dalsia];
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