#include <stddef.h>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <map>
#include <thread>

#include "Loader.h"
#include "Hra.h"
#include "json.h"
#include "Mapa.h"
#include "Policko.h"
#include "PolickoDvere.h"
#include "StavHranieHry.h"
#include "Hrac.h"
#include "Vrstva.h"
#include "Npc.h"
#include "Animacia.h"
#include "DialogovyStrom.h"


Loader* Loader::instancia = NULL;

Loader* Loader::Instance()
{
	if (!instancia)
		instancia = new Loader();
	return instancia;
}

void Loader::setHra(Hra* paHra) {
	this->hra = paHra;
}

bool Loader::Getnacitava() {
	return nacitava;
}

Hra* Loader::Gethra() {
	return hra;
}

DialogovyStrom* Loader::nacitajDialog(std::string paMeno) {
	DialogovyStrom* dialog = new DialogovyStrom();

	DialogPolozka *node0 = new DialogPolozka("Ahoj udatny bojovnik.");
	DialogPolozka *node1 = new DialogPolozka("Nechcem sa s tebou rozpravat");
	DialogPolozka *node2 = new DialogPolozka("Mam pre teba quest.");
	DialogPolozka *node3 = new DialogPolozka("Dostanes 5 goldov.");
	DialogPolozka *node4 = new DialogPolozka("Pozbieraj 10 konarov.");

	//node 0
	node0->pridajMoznost(new DialogVolba("Tin tang kungpao...", 1));
	node0->pridajMoznost(new DialogVolba("Ahoj.", 2));
	dialog->vlozPolozku(node0);

	//node 1
	node1->pridajMoznost(new DialogVolba("Dobre :(", -1));
	dialog->vlozPolozku(node1);

	//node2
	node2->pridajMoznost(new DialogVolba("Nechce sa mi.", -1));
	node2->pridajMoznost(new DialogVolba("Co treba spravit ?", 4));
	node2->pridajMoznost(new DialogVolba("Co za to ziskam? ", 3));
	dialog->vlozPolozku(node2);

	//node3
	node3->pridajMoznost(new DialogVolba("Ok co teda treba spravit?", 4));
	node3->pridajMoznost(new DialogVolba("To sa mi nechce.", -1));
	dialog->vlozPolozku(node3);

	//node4
	node4->pridajMoznost(new DialogVolba("Ok idem na to.", -1));
	node4->pridajMoznost(new DialogVolba("Nie.", -1));
	dialog->vlozPolozku(node4);



	return dialog;
}


void Loader::nacitajMapu(std::string paMeno , int posX, int posY,int smer) {
	//nacitava = true;
	hra->zmenStavRozhrania("stavLoading");
	if (nacitaneMapy.find(paMeno) != nacitaneMapy.end()) {

		Mapa* novaMapa = nacitaneMapy.at(paMeno);
		hra->GetHrac()->setMapa(novaMapa);
		novaMapa->setHrac(hra->GetHrac());

		StavHranieHry* stav = (StavHranieHry*)hra->dajStav("hranieHry");
		//Mapa* staraMapa = stav->getMapa();
		stav->Setmapa(novaMapa);

		if (posX == -1 || posY == -1 || smer == -1) {
			novaMapa->posunHracaNaPolicko(0, 0, 0);
		}
		else {
			novaMapa->posunHracaNaPolicko(posX, posY, smer);
		}
		return;
	}
	
	Mapa* novaMapa = new Mapa(paMeno, this->hra->GetHrac(), this->hra);
	
	std::string cestaKMapam = "Data/Mapy/";
	std::string cestakTexturam = "Data/Grafika/Textury/";

	PolickoDvere* polickoDvere[100][100];
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			polickoDvere[i][j] = nullptr;
		}
	}

	bool alive = true;
	while (alive) {

		Json::Value root;
		Json::Reader reader;
		std::ifstream test(cestaKMapam + "" + paMeno + ".json", std::ifstream::binary);
		std::cout << cestaKMapam + "" + paMeno + ".json" << std::endl;
		bool parsingSuccessful = reader.parse(test, root, false);

		if (!parsingSuccessful)
		{
			std::cout << "chyba pri parsovani Jsonu" << "\n";
		}

		int vyska = root["height"].asInt();
		int sirka = root["width"].asInt();
		novaMapa->setSirkaVyska(sirka, vyska);

		Json::Value dvere(Json::objectValue);
		dvere = root["dvere"];
		int i = 0;
		for (Json::Value::iterator it = dvere.begin(); it != dvere.end(); ++it) {
			Json::Value value = (*it);
			int x = value["x"].asInt();
			int y = value["y"].asInt();
			int posX = value["poziciaX"].asInt();
			int posY = value["poziciaY"].asInt();
			int smerPohladu = value["smerPohladu"].asInt();
			std::string kam = value["kam"].asCString();

			polickoDvere[x][y] = new PolickoDvere(true, kam, posX, posY, smerPohladu);
		}

		Json::Value objekt(Json::objectValue);
		objekt = root["tiles"];

		for (Json::Value::iterator it = objekt.begin(); it != objekt.end(); ++it)

		{

			Json::Value key = it.key();

			Json::Value value = (*it);

			std::string menoTextury = value["image"].asCString();
			int id = atoi(key.asCString());
			textury[id + 1] = new sf::Texture();
			if (!textury[id + 1]->loadFromFile(cestakTexturam + "" + menoTextury, sf::IntRect(0, 0, 32, 32))) {
				std::cout << "Chyba nahravania textury policka" << std::endl;
			}
			else {
				//std::cout << "textura " + menoTextury + " nacitana" << std::endl;
			}


		}

		for (int i = 0; i < vyska; i++) {
			for (int j = 0; j < sirka; j++) {

				int idTextury1 = root["Vrstva1"][i*vyska + j].asInt();
				int idTextury2 = root["Vrstva2"][i*vyska + j].asInt();
				int idTextury3 = root["Vrstva3"][i*vyska + j].asInt();

				Policko* policko = nullptr;

				if (polickoDvere[j][i] != nullptr) {
					policko = polickoDvere[j][i];

				}
				else {
					if (idTextury2 != 0) {
						policko = new Policko(false);
					}
					else {
						policko = new Policko(true);
					}
				}

				if (idTextury1 != 0) {
					policko->nastavTexturu(textury[idTextury1], 0);
				}
				if (idTextury2 != 0) {
					policko->nastavTexturu(textury[idTextury2], 1);
				}
				if (idTextury3 != 0) {
					policko->nastavTexturu(textury[idTextury3], 2);
				}

				novaMapa->nastavPolicko(j, i, policko);

			}

		}

		alive = false;
	}

	if (nacitaneMapy.size() > 10) {
		for (std::map<std::string, Mapa*>::iterator it = nacitaneMapy.begin(); it != nacitaneMapy.end(); ++it)
		{
			delete it->second;
		}
		nacitaneMapy.clear();
		//std::cout <<"Mapy zmazane" << nacitaneMapy.size() << std::endl;
	}

	nacitaneMapy.insert(std::pair<std::string, Mapa*>(paMeno, novaMapa));
	//std::cout << "Mapa nacitana" << nacitaneMapy.size() << std::endl;

	hra->GetHrac()->setMapa(novaMapa);
	novaMapa->setHrac(hra->GetHrac());

	StavHranieHry* stav = (StavHranieHry*)hra->dajStav("hranieHry");
	//Mapa* staraMapa = stav->getMapa();
	stav->Setmapa(novaMapa);

	Npc* npc = new Npc("Kubo");
	Animacia* animacia = new Animacia("Data/Grafika/Npc/npc1_dole.png", 4, 10, 32, 48);
	npc->Setanimacia(animacia);
	novaMapa->GetPolicko(0, 1)->Setnpc(npc);
	
	if (posX == -1 || posY == -1 || smer == -1) {
		novaMapa->posunHracaNaPolicko(0, 0, 0);
	}
	else {
		novaMapa->posunHracaNaPolicko(posX, posY, smer);
	}



	/*
	if (staraMapa != nullptr) {
		//delete staraMapa;
	}
	*/
	
	//nacitava = false;
	//hra->zmenStavRozhrania("hranieHry");
}