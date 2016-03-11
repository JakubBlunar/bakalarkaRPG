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
#include "VolbaObchodovanie.h"
#include "VolbaVyliecenie.h"
#include "Npc.h"
#include "PolickoBoj.h"
#include "VolbaUpravaQuestu.h"
#include "VolbaPredQpolozkou.h"

#include "Statistika.h"
#include "Akcia.h"
#include "Nepriatel.h"
#include "AkciaDmg.h"
#include "Efekt.h"
#include "EfektUpravStat.h"
#include "AkciaPridanieEfektu.h"
#include "AkciaLiecenie.h"

#include "Elixir.h"
#include "Pouzitelny.h"
#include "Oblecenie.h"
#include "Zbran.h"

#include "Quest.h"
#include "QuestPolozka.h"
#include "Poziadavka.h"
#include "QuestManager.h"
#include <random>

Loader* Loader::instancia = NULL;

Loader* Loader::Instance()
{
	if (!instancia) {
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

	bool parsingSuccessful = reader.parse(json, root, false);

	if (!parsingSuccessful)
	{
		std::cout << "Dialog " << paMeno << ".json neexistuje alebo chyba v parsovani" << std::endl;
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

	for (Json::Value::iterator it = objekt.begin(); it != objekt.end(); ++it) {
		Json::Value key = it.key();
		Json::Value polozkaData = (*it);

		std::string typPolozky = polozkaData["typ"].asCString();

		DialogPolozka* polozka;
		if (typPolozky == "normalVolba") {
			std::string textPolozky = polozkaData["text"].asCString();
			polozka = new DialogPolozka(textPolozky);
		}

		Json::Value volby(Json::objectValue);
		volby = polozkaData["volby"];

		for (Json::Value::iterator it = volby.begin(); it != volby.end(); ++it) {
			Json::Value volbaID = it.key();
			Json::Value volbaData = (*it);
			int dalsia = volbaData["kam"].asInt();
			std::string volbaText = volbaData["text"].asCString();
			std::string typ = volbaData["typ"].asCString();
			if (typ == "") {
				polozka->pridajMoznost(new DialogVolba(volbaText, dalsia));
			}
			else if (typ == "obchod") {
				std::string aky = volbaData["aky"].asCString();
				polozka->pridajMoznost(new VolbaObchodovanie(volbaText, dalsia, aky));
			}
			else if (typ == "liecenie") {
				polozka->pridajMoznost(new VolbaVyliecenie(volbaText, dalsia));
			}
		}

		dialog->vlozPolozku(polozka);

	}
	return dialog;
}


void Loader::nacitajMapu(std::string paMeno, int posX, int posY, int smer) {
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
		novaMapa = new Mapa(paMeno, this->hra->GetHrac(), this->hra, sirka, vyska);

		novaMapa->setHrobSuradnice(sf::Vector2i(mapaData["hrobX"].asInt(), mapaData["hrobY"].asInt()));

		Json::Value nepriatelia(Json::arrayValue);
		nepriatelia = mapaData["nepriatelia"];

		for (unsigned int i = 0; i < nepriatelia.size(); i++) {
			novaMapa->pridajNepriatela(nepriatelia[i].asCString());
		}

		Json::Value questy(Json::arrayValue);
		questy = mapaData["questy"];

		for (unsigned int i = 0; i < questy.size(); i++) {
			nacitajQuest(questy[i].asCString());
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

	if (nacitaneMapy.size() > 15) {
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

	// zmazanie policiek dveri ktoré boli ako pomocná premenná
	for (int i = 0; i < novaMapa->Getsirka(); ++i) {
		delete[] polickoDvere[i];
	}

	delete[] polickoDvere;

}


void Loader::nacitajNpc(std::string menoMapy, Mapa* mapa) {
	std::string cestaKNpc = "./Data/Npc/";
	std::string cestaNpcAnimacie = "./Data/Grafika/Npc/";


	bool alive = true;
	while (alive) {

		Json::Value root;
		Json::Reader reader;
		std::ifstream json(cestaKNpc + "" + menoMapy + "npc.json", std::ifstream::binary);

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


			Npc* npc = new Npc(meno, dialog);

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
		if (!font->loadFromFile("./Data/Grafika/" + menoFontu)) {
			exit(1);
		};

		nacitaneFonty.insert(std::pair<std::string, sf::Font*>(menoFontu, font));
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
	int hp = nahodneCislo(minHp, maxHp);
	int mp = nahodneCislo(minMp, maxMp);
	int sila = nahodneCislo(silaOd, silaDo);
	int intelekt = nahodneCislo(intelentOd, intelektDo);

	int rychlostMin = (int)ceil(((double)uhybMin / 100) * 6 * level);
	int rychlostMax = (int)ceil(((double)uhybMax / 100) * 6 * level);
	int rychlost = nahodneCislo(rychlostMin, rychlostMax);

	int obranaMin = (int)ceil(((double)redukciaMin / 100) * 25 * level);
	int obranaMax = (int)ceil(((double)redukciaMax / 100) * 25 * level);
	int obrana = nahodneCislo(obranaMin, obranaMax);

	Statistika* statistika = new Statistika(level, hp, hp, mp, mp, sila, intelekt, rychlost, obrana);

	Json::Value akcie(Json::objectValue);
	akcie = nepriatel["akcie"];

	for (Json::Value::iterator it = akcie.begin(); it != akcie.end(); ++it) {
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
		else if (typAkcie == "AkciaPridanieEfektu") {
			Json::Value efekt(Json::objectValue);
			efekt = akcia["efekt"];
			std::string druh = efekt["druh"].asCString();
			std::string obrazokEfektu = efekt["obrazok"].asCString();
			std::string statEfektu = efekt["stat"].asCString();
			int oKolko = efekt["hodnota"].asInt();
			bool naNpc = efekt["naSeba"].asBool();

			if (druh == "upravStat") {
				Efekt* novyEfekt = new EfektUpravStat(obrazokEfektu, statEfektu, oKolko);
				statistika->vlozAkciu(new AkciaPridanieEfektu(menoAkcie, obrazokAkcie, rychlostCasteniaAkcie, cooldownAkcie, trvanieAkcie, popisAkcie, manaAkcie, novyEfekt, naNpc));
			}
		}
		else if (typAkcie == "AkciaLiecenie") {
			statistika->vlozAkciu(new AkciaLiecenie(menoAkcie, obrazokAkcie, rychlostCasteniaAkcie, cooldownAkcie, trvanieAkcie, popisAkcie, manaAkcie, enumTypAkcie, zakladnaHodnotaAkcie));
		}


	}

	statistika->prepocitajPoskodenia();
	novyNepriatel = new Nepriatel(meno, obrazok, nullptr, statistika);



	Json::Value dropy(Json::objectValue);
	dropy = nepriatel["questDrop"];

	for (Json::Value::iterator it = dropy.begin(); it != dropy.end(); ++it) {
		Json::Value key = it.key();
		Json::Value predmet = (*it);

		std::string meno = predmet["meno"].asCString();
		std::string obrazok = predmet["obrazok"].asCString();
		int typ = predmet["typ"].asInt();
		int cena = predmet["cena"].asInt();
		int uroven = predmet["uroven"].asInt();

		novyNepriatel->pridajDropItem(key.asCString(), new Predmet(meno, typ, obrazok, cena, uroven));

	}


	return novyNepriatel;
}

int Loader::nahodneCislo(int min, int max) {
	if (min == max) return min;
	return min + rand() % (max - min);
}

std::vector<Predmet*>* Loader::nacitajObchod(std::string paMeno) {
	std::string cestaKObchodom = "./Data/Obchody/";

	std::vector<Predmet*>* obchod = new std::vector<Predmet*>();

	Json::Value jObchod;
	Json::Reader reader;
	std::ifstream json(cestaKObchodom + "" + paMeno + ".json", std::ifstream::binary);
	bool parsingSuccessful = reader.parse(json, jObchod, false);

	if (!parsingSuccessful)
	{
		std::cout << "chyba pri parsovani Jsonu obchodu " << "\n";
	}

	Json::Value polozky(Json::objectValue);
	polozky = jObchod["polozky"];

	for (Json::Value::iterator it = polozky.begin(); it != polozky.end(); ++it) {
		Json::Value key = it.key();
		Json::Value polozka = (*it);

		Predmet* p = parsujPredmet(polozka);
		obchod->push_back(p);

	}




	return obchod;
}

Predmet* Loader::parsujPredmet(Json::Value jPredmet) {
	Predmet* predmet = nullptr;

	std::string typTriedy = jPredmet["typTriedy"].asCString();

	std::string meno = jPredmet["meno"].asCString();
	std::string obrazok = jPredmet["obrazok"].asCString();
	int typ = jPredmet["typ"].asInt();
	int cena = jPredmet["cena"].asInt();
	int uroven = jPredmet["uroven"].asInt();

	if (typTriedy == "elixir") {
		std::string co = jPredmet["stat"].asCString();
		int oKolko = jPredmet["oKolko"].asInt();
		predmet = new Elixir(meno, typ, obrazok, cena, uroven, co, oKolko);
	}
	else {


		if (typTriedy == "zbran") {

			int minDmg = jPredmet["minDmg"].asInt();
			int maxDmg = jPredmet["maxDmg"].asInt();
			int rychlostUtoku = jPredmet["rychlostUtoku"].asInt();

			predmet = new Zbran(meno, typ, obrazok, cena, uroven, minDmg, maxDmg, rychlostUtoku);
		}
		else {
			predmet = new Oblecenie(meno, typ, obrazok, cena, uroven);
		}

		Pouzitelny* ppredmet = (Pouzitelny*)predmet;
		int hp = jPredmet["hp"].asInt();
		double hpMult = jPredmet["hpMult"].asDouble();
		int mp = jPredmet["mp"].asInt();
		double mpMult = jPredmet["mpMult"].asDouble();
		int sila = jPredmet["sila"].asInt();
		double silaMult = jPredmet["silaMult"].asDouble();
		int intelekt = jPredmet["intelekt"].asInt();
		double intelektMult = jPredmet["intelektMult"].asDouble();
		int rychlost = jPredmet["rychlost"].asInt();
		double rychlostMult = jPredmet["rychlostMult"].asDouble();
		int obrana = jPredmet["obrana"].asInt();
		double obranaMult = jPredmet["obranaMult"].asDouble();

		ppredmet->Sethp(hp);
		ppredmet->SethpMult(hpMult);
		ppredmet->Setmp(mp);
		ppredmet->SetmpMult(mpMult);
		ppredmet->Setsila(sila);
		ppredmet->SetsilaMult(silaMult);
		ppredmet->Setinteligencia(intelekt);
		ppredmet->SetinteligenciaMult(intelektMult);
		ppredmet->Setrychlost(rychlost);
		ppredmet->SetrychlostMult(rychlostMult);
		ppredmet->Setarmor(obrana);
		ppredmet->SetarmorMult(obranaMult);
	}
	return predmet;
}

Quest* Loader::nacitajQuest(string paMeno) {

	Quest* quest;
	std::string cestaKuQuestom = "./Data/Questy/";

	Json::Value jQuest;
	Json::Reader reader;
	std::ifstream json(cestaKuQuestom + "" + paMeno + ".json", std::ifstream::binary);
	bool parsingSuccessful = reader.parse(json, jQuest, false);

	if (!parsingSuccessful)
	{
		std::cout << "chyba pri parsovani Jsonu questu " << paMeno << "\n";
	}

	std::string questNazov = jQuest["nazov"].asCString();
	quest = hra->GetHrac()->Getmanazerquestov()->GetNacitanyQuest(questNazov);

	if (quest == nullptr) {

		std::string questPopis = jQuest["popis"].asCString();
		int odmenaXp = jQuest["xp"].asInt();
		int odmenaZlato = jQuest["zlato"].asInt();
		std::string startNpc = jQuest["startNpc"].asCString();
		std::string endNpc = jQuest["endNpc"].asCString();

		quest = new Quest(questNazov, questPopis, odmenaXp, odmenaZlato, startNpc, endNpc);

		//nacitanie polozky ktorá bude predstavova to èo bude rozprava npc o queste
		QuestPolozka* polozka = new QuestPolozka(quest->Getnazov());
		Json::Value polozkaTexty(Json::arrayValue);
		polozkaTexty = jQuest["polozkaTexty"];
		QuestPolozka* qp = (QuestPolozka*)polozka;
		for (unsigned int i = 0; i < polozkaTexty.size(); i++) {
			if (i == 0) {
				qp->vlozText(StavQuestu::NEPRIJATY, polozkaTexty[i].asCString());
			}

			if (i == 1) {
				qp->vlozText(StavQuestu::ROZROBENY, polozkaTexty[i].asCString());
			}

			if (i == 2) {
				qp->vlozText(StavQuestu::SPLNENIE_POZIADAVIEK, polozkaTexty[i].asCString());
			}

			if (i == 3) {
				qp->vlozText(StavQuestu::DOKONCENY, polozkaTexty[i].asCString());
			}

		}

		// nacitanie volieb ked sa hráè dostane na quest polozku 
		Json::Value volby(Json::objectValue);
		volby = jQuest["volby"];

		for (Json::Value::iterator it = volby.begin(); it != volby.end(); ++it) {
			Json::Value volbaID = it.key();
			Json::Value volbaData = (*it);


			int dalsia = volbaData["kam"].asInt();
			std::string volbaText = volbaData["text"].asCString();
			std::string typ = volbaData["typ"].asCString();
			if (typ == "") {
				polozka->pridajMoznost(new DialogVolba(volbaText, dalsia));
			}
			else if (typ == "upravaQuestu") {

				VolbaUpravaQuestu* volba = new VolbaUpravaQuestu(-1, quest);

				Json::Value volbaTexty(Json::arrayValue);
				volbaTexty = volbaData["volbaTexty"];

				for (unsigned int i = 0; i < volbaTexty.size(); i++) {
					if (i == 0) {
						volba->vlozText(StavQuestu::NEPRIJATY, volbaTexty[i].asCString());
					}

					if (i == 1) {
						volba->vlozText(StavQuestu::ROZROBENY, volbaTexty[i].asCString());
					}

					if (i == 2) {
						volba->vlozText(StavQuestu::SPLNENIE_POZIADAVIEK, volbaTexty[i].asCString());
					}

					if (i == 3) {
						volba->vlozText(StavQuestu::DOKONCENY, volbaTexty[i].asCString());
					}

				}

				polozka->pridajMoznost(volba);
			}
			else if (typ == "obchod") {
				std::string aky = volbaData["aky"].asCString();
				polozka->pridajMoznost(new VolbaObchodovanie(volbaText, dalsia, aky));
			}
			else if (typ == "liecenie") {
				polozka->pridajMoznost(new VolbaVyliecenie(volbaText, dalsia));
			}

		}
		quest->SetdialogPolozka(polozka);

		// nacitanie volby ktorá sa zobrazi na zaciatku dialogu, a uvedie hraca na polozku z questom
		Json::Value volbaKuQuestu(Json::objectValue);
		volbaKuQuestu = jQuest["volbaKuQuestu"];

		Json::Value volbaTexty(Json::arrayValue);
		volbaTexty = volbaKuQuestu["volbaTexty"];

		VolbaPredQpolozkou* volba = new VolbaPredQpolozkou(0, quest);

		for (unsigned int i = 0; i < volbaTexty.size(); i++) {
			if (i == 0) {
				volba->vlozText(StavQuestu::NEPRIJATY, volbaTexty[i].asCString());
			}

			if (i == 1) {
				volba->vlozText(StavQuestu::ROZROBENY, volbaTexty[i].asCString());
			}

			if (i == 2) {
				volba->vlozText(StavQuestu::SPLNENIE_POZIADAVIEK, volbaTexty[i].asCString());
			}

			if (i == 3) {
				volba->vlozText(StavQuestu::DOKONCENY, volbaTexty[i].asCString());
			}

		}

		quest->SetvolbaKuQuestu(volba);

		// nacitanie nasledujuceho questu
		std::string dalsi = jQuest["nasledujuci"].asCString();
		if (dalsi != "") {
			Quest* dalsiQ = nacitajQuest(dalsi);
			dalsiQ->Setpredchadzajuci(quest);
			quest->Setnasledujuci(dalsiQ);
		}

		// poziadavky na splnenie questu
		Json::Value questPoziadavky(Json::arrayValue);
		questPoziadavky = jQuest["poziadavky"];
		for (unsigned int i = 0; i < questPoziadavky.size(); i++) {
			Json::Value poziadavka(Json::objectValue);
			poziadavka = questPoziadavky[i];

			string pTyp = poziadavka["typ"].asCString();
			if (pTyp == "kill") {
				std::string pKoho = poziadavka["co"].asCString();
				int pKolko = poziadavka["kolko"].asInt();
				std::string pKde = poziadavka["kde"].asCString();
				quest->pridajPoziadavku(new PoziadavkaZabi(pKoho, pKolko, pKde));
			}
			else if (pTyp == "loot") {
				std::string pCo = poziadavka["co"].asCString();
				int pKolko = poziadavka["kolko"].asInt();
				quest->pridajPoziadavku(new PoziadavkaLoot(pCo, pKolko));
			}
		}

		// nacitanie predmetov ktoré su ako odmena za quest
		Json::Value odmenaVeci(Json::arrayValue);
		odmenaVeci = jQuest["predmety"];
		for (unsigned int i = 0; i < odmenaVeci.size(); i++) {
			Json::Value jPredmet(Json::objectValue);
			jPredmet = odmenaVeci[i];
			quest->pridajOdmenu(parsujPredmet(jPredmet));
		}
		hra->GetHrac()->Getmanazerquestov()->nacitanyQuest(quest);
	}
	
	
	return quest;
}