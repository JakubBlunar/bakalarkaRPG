#include "DialogovyStrom.h"

DialogPolozka::DialogPolozka(string paText) {
	text = paText;
}

DialogVolba::DialogVolba(string paText, int paNavratovaHodnota, DialogPolozka *padalsiaPolozka) {
	text = paText;
	navratovaHodnota = paNavratovaHodnota;
	dalsiaPolozka = padalsiaPolozka;
}


DialogovyStrom::DialogovyStrom()
{
}


DialogovyStrom::~DialogovyStrom()
{
	destroyTree();
}


void DialogovyStrom::init() {
	DialogPolozka *node0 = new DialogPolozka("Ahoj udatny bojovnik.");
	DialogPolozka *node1 = new DialogPolozka("Nechcem sa s tebou rozpravat");
	DialogPolozka *node2 = new DialogPolozka("Mam pre teba quest.");
	DialogPolozka *node3 = new DialogPolozka("Dostanes 5 goldov.");
	DialogPolozka *node4 = new DialogPolozka("Pozbieraj 10 konarov.");

	//node 0
	node0->dialogoveMoznosti.push_back(DialogVolba("Tin tang kungpao...", 0, node1));
	node0->dialogoveMoznosti.push_back(DialogVolba("Ahoj.", 0, node2));
	castiDialogu.push_back(node0);

	//node 1
	node1->dialogoveMoznosti.push_back(DialogVolba("Dobre :(", 0, nullptr));
	castiDialogu.push_back(node1);

	//node2
	node2->dialogoveMoznosti.push_back(DialogVolba("Nechce sa mi.", 0, nullptr));
	node2->dialogoveMoznosti.push_back(DialogVolba("Co treba spravit ?", 0, node4));
	node2->dialogoveMoznosti.push_back(DialogVolba("Co za to ziskam? ", 0, node3));
	castiDialogu.push_back(node2);

	//node3
	node3->dialogoveMoznosti.push_back(DialogVolba("Ok co teda treba spravit?", 0, node4));
	node3->dialogoveMoznosti.push_back(DialogVolba("To sa mi nechce.", 0, nullptr));
	castiDialogu.push_back(node3);

	//node4
	node4->dialogoveMoznosti.push_back(DialogVolba("Ok idem na to.", 1, nullptr));
	node4->dialogoveMoznosti.push_back(DialogVolba("Nie.", 0, nullptr));
	castiDialogu.push_back(node4);
}

void DialogovyStrom::destroyTree() {
	for (int i = 0; i < castiDialogu.size(); i++) {
		delete castiDialogu[i];
	}
	castiDialogu.clear();
}

int DialogovyStrom::zacniDialog() {
	if (castiDialogu.size() == 0) {
		return -1;
	}
	//prva node ktoru vlozim do stromu bude prva
	DialogPolozka *currentNode = castiDialogu[0];

	while (true) {

		cout << "Npc: " << currentNode->text << endl << endl;
		for (int i = 0; i < currentNode->dialogoveMoznosti.size(); i++) {
			cout << i + 1 << ":  " << currentNode->dialogoveMoznosti[i].text << endl;
		}
		cout << endl;
		int input;
		cin >> input;
		input--;
		cout << endl;

		if (input<0 || input >= currentNode->dialogoveMoznosti.size()) {
			cout << "Zla volba!" << endl;
		}
		else {
			//skontrolovanie konca konverzacie
			if (currentNode->dialogoveMoznosti[input].dalsiaPolozka == nullptr) {
				return currentNode->dialogoveMoznosti[input].navratovaHodnota;
			}

			currentNode = currentNode->dialogoveMoznosti[input].dalsiaPolozka;

		}
		cout << endl;
	}

	return -1;
}
