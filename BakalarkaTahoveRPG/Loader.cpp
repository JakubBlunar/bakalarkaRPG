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
#include "VolbaPridanieQuestu.h"
#include "Npc.h"
#include "PolickoBoj.h"

#include "Statistika.h"
#include "Akcia.h"
#include "Nepriatel.h"
#include "AkciaDmg.h"
#include "Efekt.h"
#include "EfektUpravStat.h"
#include "AkciaPridanieEfektu.h"

#include <random>

Loader* Loader::instancia = NULL;

Loader* Loader::Instance()
{
	if (!instancia) {
		srand((unsigned int)time(NULL));
		instancia = new Loader();
	}
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
	std::string cestaDialogy = "./Data/Npc/Dialogy/";

	Json::Value root;
	Json::Reader reader;
	std::ifstream json(cestaDialogy + "" + paMeno + ".json", std::ifstream::binary);
	//std::cout << cestaKMapam + "" + menoMapy + "npc.json" << std::endl;

	bool parsingSuccessful = reader.parse(json, root, false);

	if (!parsingSuccessful)
	{
		DialogovyStrom* dialog;
		dialog = new DialogovyStrom();
		DialogPolozka *node0 = new DialogPolozka("Ahoj udatny bojovnik.");
		node0->pridajMoznost(new DialogVolba("Ahoj.", -1));
		dialog->vlozPolozku(node0);
		return dialog;
	}

	Json::Value objekt(Json::objectValue);
	objekt = root["polozky"];

	DialogovyStrom* dialog = new DialogovyStrom();

	for (Json::Value::iterator it = objekt.begin(); it != objekt.end(); ++it){
		Json::Value key = it.key();
		Json::Value value = (*it);

		std::string textPolozky = value["text"].asCString();
		DialogPolozka* polozka = new DialogPolozka(textPolozky);

		Json::Value volby(Json::objectValue);
		volby = value["volby"];

		for (Json::Value::iterator it = volby.begin(); it != volby.end(); ++it) {
			Json::Value volbaID = it.key();
			Json::Value volbaData = (*it);
			int dalsia = volbaData["kam"].asInt();
			std::string volbaText = volbaData["text"].asCString();
			std::string typ = volbaData["typ"].asCString();
			if (typ == "") {
				polozka->pridajMoznost(new DialogVolba(volbaText, dalsia));
			}
			else if(typ == "pridanieQuestu") {
				polozka->pridajMoznost(new VolbaPridanieQuestu(volbaText, dalsia));
			}


		}

		dialog->vlozPolozku(polozka);

	}
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
	
	Mapa* novaMapa;
	
	std::string cestaKMapam = "./Data/Mapy/";
	std::string cestakTexturam = "./Data/Grafika/Textury/";

	PolickoDvere*** polickoDvere;

	bool alive = true;
	while (alive) {

		Json::Value mapaData;
		Json::Value root;
		Json::Reader reader;
		std::ifstream test(cestaKMapam + "" + paMeno + ".json", std::ifstream::binary);
		std::ifstream data(cestaKMapam + "" + paMeno + "data.json", std::ifstream::binary);
		bool parsingSuccessful = reader.parse(test, root, false);
		parsingSuccessful = reader.parse(data, mapaData, false);
		if (!parsingSuccessful)
		{
			std::cout << "chyba pri parsovani Jsonu mapy" << "\n";
		}

		int vyska = root["height"].asInt();
		int sirka = root["width"].asInt();
		novaMapa = new Mapa(paMeno, this->hra->GetHrac(), this->hra,sirka,vyska);

		Json::Value nepriatelia(Json::arrayValue);
		nepriatelia = mapaData["nepriatelia"];

		for (int i = 0; i < nepriatelia.size(); i++) {
			novaMapa->pridajNepriatela(nepriatelia[i].asCString());
		}


		// inicializacia mapy dveri
		polickoDvere = new PolickoDvere**[sirka];
		for (int i = 0; i < sirka; i++) {
			polickoDvere[i] = new PolickoDvere*[vyska];
		}

		for (int i = 0; i < sirka; ++i) {
			for (int j = 0; j < vyska; ++j) {
				polickoDvere[i][j] = nullptr;
			}
		}


		Json::Value dvere(Json::objectValue);
		dvere = mapaData["dvere"];
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
		}

		for (int i = 0; i < vyska; i++) {
			for (int j = 0; j < sirka; j++) {

				int idTextury1 = root["Vrstva1"][i*vyska + j].asInt();
				int idTextury2 = root["Vrstva2"][i*vyska + j].asInt();
				int idTextury3 = root["Vrstva3"][i*vyska + j].asInt();
				int idTextury4 = root["boj"][i*vyska + j].asInt();

				Policko* policko = nullptr;

				if (polickoDvere[j][i] != nullptr) {
					policko = polickoDvere[j][i];

				}
				else {
					if (idTextury2 != 0) {
						policko = new Policko(false);
					}
					else {
						if (idTextury4 == 0) {
							policko = new Policko(true);
						}
						else {
							policko = new PolickoBoj(true);
						}
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

	nacitajNpc(paMeno, novaMapa);

	if (nacitaneMapy.size() > 10) {
		for (std::map<std::string, Mapa*>::iterator it = nacitaneMapy.begin(); it != nacitaneMapy.end(); ++it)
		{
			delete it->second;
		}
		nacitaneMapy.clear();
	}

	nacitaneMapy.insert(std::pair<std::string, Mapa*>(paMeno, novaMapa));

	hra->GetHrac()->setMapa(novaMapa);
	novaMapa->setHrac(hra->GetHrac());

	StavHranieHry* stav = (StavHranieHry*)hra->dajStav("hranieHry");
	stav->Setmapa(novaMapa);

	if (posX == -1 || posY == -1 || smer == -1) {
		novaMapa->posunHracaNaPolicko(0, 0, 0);
	}
	else {
		novaMapa->posunHracaNaPolicko(posX, posY, smer);
	}

	// zmazanie policiek dveri ktor� boli ako pomocn� premenn�
	for (int i = 0; i < novaMapa->Getsirka(); ++i) {
		delete[] polickoDvere[i];
	}

	delete[] polickoDvere;

}


void Loader::nacitajNpc(std::string menoMapy, Mapa* mapa) {
	std::string cestaKNpc= "./Data/Npc/";
	std::string cestaNpcAnimacie = "./Data/Grafika/Npc/";
	

	bool alive = true;
	while (alive) {

		Json::Value root;
		Json::Reader reader;
		std::ifstream json(cestaKNpc + "" + menoMapy + "npc.json", std::ifstream::binary);
		//std::cout << cestaKMapam + "" + menoMapy + "npc.json" << std::endl;
		
		bool parsingSuccessful = reader.parse(json, root, false);

		if (!parsingSuccessful)
		{
			std::cout << "chyba pri parsovani Jsonu npc " << "\n";
		}

		Json::Value objekt(Json::objectValue);
		objekt = root["npc"];
		
		for (Json::Value::iterator it = objekt.begin(); it != objekt.end(); ++it)

		{
			Json::Value key = it.key();

			Json::Value value = (*it);

			std::string meno = value["meno"].asCString();
			int posX = value["posX"].asInt();
			int posY = value["posY"].asInt();
			std::string nazovDialogu = value["dialog"].asCString();
			
			Json::Value animacia(Json::objectValue);
			animacia = value["animacia"];
			std::string animaciaMeno = animacia["nazov"].asCString();
			int animaciaX = animacia["aniX"].asInt();
			int animaciaY = animacia["aniY"].asInt();
			int pocetSnimkov = animacia["pocet"].asInt();
			int trvanieAnimacie = animacia["trvanie"].asInt();

			
			
			DialogovyStrom* dialog;
			
			if (nazovDialogu == "null") {
				dialog = new DialogovyStrom();
				DialogPolozka *node0 = new DialogPolozka("Ahoj udatny bojovnik.");
				node0->pridajMoznost(new DialogVolba("Ahoj.", -1));
				dialog->vlozPolozku(node0);
				
			}
			else {
				dialog = nacitajDialog(nazovDialogu);
			}


			Npc* npc = new Npc(meno,dialog);

			Animacia* npcAnimacia = new Animacia(cestaNpcAnimacie + "" + animaciaMeno + ".png", pocetSnimkov, trvanieAnimacie, animaciaX, animaciaY);
			npc->Setanimacia(npcAnimacia);

			mapa->GetPolicko(posX, posY)->Setnpc(npc);


		}
		alive = false;
	}


}

sf::Font* Loader::nacitajFont(std::string menoFontu) {
	
	if (nacitaneFonty.find(menoFontu) == nacitaneFonty.end()) {

		sf::Font* font = new sf::Font();
		if (!font->loadFromFile("./Data/Grafika/"+menoFontu)) {
			exit(1);
		};

		nacitaneFonty.insert(std::pair<std::string, sf::Font*>(menoFontu,font));
		return font;
	}
	else {
		return nacitaneFonty.at(menoFontu);
	}

}

Nepriatel* Loader::nacitajNepriatela(std::string paMeno) {
	std::string cestaKNepriatelom = "./Data/Nepriatelia/";

	Nepriatel* novyNepriatel;

		Json::Value nepriatel;
		Json::Reader reader;
		std::ifstream json(cestaKNepriatelom + "" + paMeno + ".json", std::ifstream::binary);
		bool parsingSuccessful = reader.parse(json, nepriatel, false);

		if (!parsingSuccessful)
		{
			std::cout << "chyba pri parsovani Jsonu nepriatela " << "\n";
		}

		std::string meno = nepriatel["meno"].asCString();
		std::string obrazok = nepriatel["obrazok"].asCString();

		int levelOd = nepriatel["levelOd"].asInt();
		int levelDo = nepriatel["levelDo"].asInt();
		int minHp = nepriatel["hpOd"].asInt();
		int maxHp = nepriatel["hpDo"].asInt();
		int minMp = nepriatel["mpOd"].asInt();
		int maxMp = nepriatel["mpDo"].asInt();
		int silaOd = nepriatel["silaOd"].asInt();
		int silaDo = nepriatel["silaDo"].asInt();
		int intelentOd = nepriatel["intelektOd"].asInt();
		int intelektDo = nepriatel["intelektDo"].asInt();
		int redukciaMin = nepriatel["redukciaMin"].asInt();
		int redukciaMax = nepriatel["redukciaMax"].asInt();
		int uhybMin = nepriatel["uhybMin"].asInt();
		int uhybMax = nepriatel["uhybMax"].asInt();

		int level = nahodneCislo(levelOd, levelDo);
		int hp = nahodneCislo(minHp,maxHp);
		int mp = nahodneCislo(minMp, maxMp);
		int sila = nahodneCislo(silaOd,silaDo);
		int intelekt = nahodneCislo(intelentOd, intelektDo);

		int rychlostMin = (int) ceil( ( (double) uhybMin / 100) * 6 * level );
		int rychlostMax = (int) ceil( ( (double)uhybMax / 100) * 6 * level );
		int rychlost = nahodneCislo(rychlostMin, rychlostMax);

		int obranaMin = (int)ceil(( (double)redukciaMin/100) * 25 * level);
		int obranaMax = (int)ceil(( (double)redukciaMax/100 ) * 25 * level);
		int obrana = nahodneCislo(obranaMin, obranaMax);

		Statistika* statistika = new Statistika(level,hp,hp,mp,mp,sila,intelekt,rychlost,obrana);

		Json::Value akcie(Json::objectValue);
		akcie = nepriatel["akcie"];
		
		for (Json::Value::iterator it = akcie.begin(); it != akcie.end(); ++it){
			Json::Value key = it.key();
			Json::Value akcia = (*it);

			std::string typAkcie = akcia["typ"].asCString();
			std::string menoAkcie = akcia["meno"].asCString();
			std::string obrazokAkcie = akcia["obrazok"].asCString();
			int rychlostCasteniaAkcie = akcia["rychlostCastenia"].asInt();
			int cooldownAkcie = akcia["cooldown"].asInt();
			int trvanieAkcie = akcia["trvanie"].asInt();
			std::string popisAkcie = akcia["popis"].asCString();

			AkciaTyp enumTypAkcie;
			std::string statAkcie = akcia["stat"].asCString();
			if (statAkcie == "fyzicka") {
				enumTypAkcie = AkciaTyp::FYZICKA;
			}
			else {
				enumTypAkcie = AkciaTyp::MAGICKA;
			}

			int manaAkcie = akcia["mana"].asInt();
			double zakladnaHodnotaAkcie = akcia["zakladnaHodnota"].asDouble();
			
			if (typAkcie == "AkciaDmg") {
				statistika->vlozAkciu(new AkciaDmg(menoAkcie, obrazokAkcie, rychlostCasteniaAkcie, cooldownAkcie, trvanieAkcie, popisAkcie, manaAkcie, enumTypAkcie, zakladnaHodnotaAkcie));
			}
			else if(typAkcie == "AkciaPridanieEfektu") {
				Json::Value efekt(Json::objectValue);
				efekt = akcia["efekt"];
				std::string druh = efekt["druh"].asCString();
				std::string obrazokEfektu = efekt["obrazok"].asCString();
				std::string statEfektu = efekt["stat"].asCString();
				int oKolko = efekt["hodnota"].asInt();
				bool naNpc = efekt["naSeba"].asBool();

				if (druh == "upravStat") {
					Efekt* novyEfekt = new EfektUpravStat(obrazokEfektu, statEfektu,oKolko);
					statistika->vlozAkciu(new AkciaPridanieEfektu(menoAkcie, obrazokAkcie, rychlostCasteniaAkcie, cooldownAkcie, trvanieAkcie, popisAkcie, manaAkcie, novyEfekt, naNpc));
				}
			}
			else if (typAkcie == "AkciaLiecenie") {
				statistika->vlozAkciu(new AkciaDmg(menoAkcie, obrazokAkcie, rychlostCasteniaAkcie, cooldownAkcie, trvanieAkcie, popisAkcie, manaAkcie, enumTypAkcie, zakladnaHodnotaAkcie));
			}


		}
		statistika->prepocitajPoskodenia();
		novyNepriatel = new Nepriatel(meno, obrazok, nullptr, statistika);


		
		
		return novyNepriatel;
}

int Loader::nahodneCislo(int min, int max) {
	if (min == max) return min;
	return min + rand() % (max - min);
}