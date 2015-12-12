#include <stddef.h>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <map>
#include "Loader.h"
#include "Hra.h"
#include "json.h"
#include "Mapa.h"
#include "Policko.h"
#include "PolickoDvere.h"
#include "StavHranieHry.h"
#include "Hrac.h"
#include "Vrstva.h"


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

void Loader::nacitajMapu(std::string paMeno , int posX, int posY,int smer) {
	nacitava = true;

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
			for (int j = 0; j < sirka; j++){

				int idTextury1 = root["Vrstva1"][i*vyska + j].asInt();
				int idTextury2 = root["Vrstva2"][i*vyska + j].asInt();
				int idTextury3 = root["Vrstva3"][i*vyska + j].asInt();

				Policko* policko = nullptr;

				if (polickoDvere[j][i] != nullptr) {
					policko = polickoDvere[i][j];
					
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
	
	
	hra->GetHrac()->setMapa(novaMapa);
	novaMapa->setHrac(hra->GetHrac());

	StavHranieHry* stav = (StavHranieHry*)hra->dajStav("hranieHry");
	Mapa* staraMapa = stav->getMapa();
	stav->Setmapa(novaMapa);


	if (posX == -1 || posY == -1 || smer ==-1) {
		novaMapa->posunHracaNaPolicko(0, 0, 0);
	}
	else {
		novaMapa->posunHracaNaPolicko(posX, posY, smer);
	}
	
	if (staraMapa != nullptr) {
		delete staraMapa;
	}

	nacitava = false;
	
}
