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
#include "AkciaPoskodenieZbranou.h"

#include "Elixir.h"
#include "Pouzitelny.h"
#include "Oblecenie.h"
#include "Zbran.h"

#include "Quest.h"
#include "QuestPolozka.h"
#include "Poziadavka.h"
#include "QuestManager.h"
#include <random>

#include "Inventar.h"
#include "Zameranie.h"
#include <deque>

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

DialogovyStrom* Loader::nacitajDialog(string paMeno) {
	string cestaDialogy = "./Data/Npc/Dialogy/";

	Json::Value root;
	Json::Reader reader;
	ifstream json(cestaDialogy + "" + paMeno + ".json", ifstream::binary);

	bool parsingSuccessful = reader.parse(json, root, false);

	if (!parsingSuccessful)
	{
		cout << "Dialog " << paMeno << ".json neexistuje alebo chyba v parsovani" << endl;
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

		string typPolozky = polozkaData["typ"].asString();

		DialogPolozka* polozka;
		if (typPolozky == "normalVolba") {
			string textPolozky = polozkaData["text"].asString();
			polozka = new DialogPolozka(textPolozky);
		}

		Json::Value volby(Json::objectValue);
		volby = polozkaData["volby"];

		for (Json::Value::iterator it = volby.begin(); it != volby.end(); ++it) {
			Json::Value volbaID = it.key();
			Json::Value volbaData = (*it);
			int dalsia = volbaData["kam"].asInt();
			string volbaText = volbaData["text"].asString();
			string typ = volbaData["typ"].asString();
			if (typ == "") {
				polozka->pridajMoznost(new DialogVolba(volbaText, dalsia));
			}
			else if (typ == "obchod") {
				string aky = volbaData["aky"].asString();
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


void Loader::nacitajMapu(string paMeno, int posX, int posY, int smer) {
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

	string cestaKMapam = "./Data/Mapy/";
	string cestakTexturam = "./Data/Grafika/Textury/";

	PolickoDvere*** polickoDvere;

	bool alive = true;
	while (alive) {

		Json::Value mapaData;
		Json::Value root;
		Json::Reader reader;
		ifstream test(cestaKMapam + "" + paMeno + ".json", ifstream::binary);
		ifstream data(cestaKMapam + "" + paMeno + "data.json", ifstream::binary);
		bool parsingSuccessful = reader.parse(test, root, false);
		parsingSuccessful = reader.parse(data, mapaData, false);
		if (!parsingSuccessful)
		{
			cout << "chyba pri parsovani Jsonu mapy" << "\n";
		}

		int vyska = root["height"].asInt();
		int sirka = root["width"].asInt();
		novaMapa = new Mapa(paMeno, this->hra->GetHrac(), this->hra, sirka, vyska);

		novaMapa->setHrobSuradnice(sf::Vector2i(mapaData["hrobX"].asInt(), mapaData["hrobY"].asInt()));

		Json::Value nepriatelia(Json::arrayValue);
		nepriatelia = mapaData["nepriatelia"];

		for (unsigned int i = 0; i < nepriatelia.size(); i++) {
			novaMapa->pridajNepriatela(nepriatelia[i].asString());
		}

		Json::Value questy(Json::arrayValue);
		questy = mapaData["questy"];

		for (unsigned int i = 0; i < questy.size(); i++) {
			nacitajQuest(questy[i].asString());
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
			string kam = value["kam"].asString();

			polickoDvere[x][y] = new PolickoDvere(true, kam, posX, posY, smerPohladu);
		}

		Json::Value objekt(Json::objectValue);
		objekt = root["tiles"];

		for (Json::Value::iterator it = objekt.begin(); it != objekt.end(); ++it)

		{
			Json::Value key = it.key();
			Json::Value value = (*it);

			string menoTextury = value["image"].asString();
			int id = atoi(key.asCString());
			textury[id + 1] = new sf::Texture();
			if (!textury[id + 1]->loadFromFile(cestakTexturam + "" + menoTextury, sf::IntRect(0, 0, 32, 32))) {
				cout << "Chyba nahravania textury policka" << endl;
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
		for (map<string, Mapa*>::iterator it = nacitaneMapy.begin(); it != nacitaneMapy.end(); ++it)
		{
			delete it->second;
		}
		nacitaneMapy.clear();
	}

	nacitaneMapy.insert(pair<string, Mapa*>(paMeno, novaMapa));

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


void Loader::nacitajNpc(string menoMapy, Mapa* mapa) {
	string cestaKNpc = "./Data/Npc/";
	string cestaNpcAnimacie = "./Data/Grafika/Npc/";


	bool alive = true;
	while (alive) {

		Json::Value root;
		Json::Reader reader;
		ifstream json(cestaKNpc + "" + menoMapy + "npc.json", ifstream::binary);

		bool parsingSuccessful = reader.parse(json, root, false);

		if (!parsingSuccessful)
		{
			cout << "chyba pri parsovani Jsonu npc " << "\n";
		}

		Json::Value objekt(Json::objectValue);
		objekt = root["npc"];

		for (Json::Value::iterator it = objekt.begin(); it != objekt.end(); ++it)

		{
			Json::Value key = it.key();

			Json::Value value = (*it);

			string meno = value["meno"].asString();
			int posX = value["posX"].asInt();
			int posY = value["posY"].asInt();
			string nazovDialogu = value["dialog"].asString();

			Json::Value animacia(Json::objectValue);
			animacia = value["animacia"];
			string animaciaMeno = animacia["nazov"].asString();
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

sf::Font* Loader::nacitajFont(string menoFontu) {

	if (nacitaneFonty.find(menoFontu) == nacitaneFonty.end()) {

		sf::Font* font = new sf::Font();
		if (!font->loadFromFile("./Data/Grafika/" + menoFontu)) {
			exit(1);
		};

		nacitaneFonty.insert(pair<string, sf::Font*>(menoFontu, font));
		return font;
	}
	else {
		return nacitaneFonty.at(menoFontu);
	}

}

Nepriatel* Loader::nacitajNepriatela(string paMeno) {
	string cestaKNepriatelom = "./Data/Nepriatelia/";

	Nepriatel* novyNepriatel;

	Json::Value nepriatel;
	Json::Reader reader;
	ifstream json(cestaKNepriatelom + "" + paMeno + ".json", ifstream::binary);
	bool parsingSuccessful = reader.parse(json, nepriatel, false);

	if (!parsingSuccessful)
	{
		cout << "chyba pri parsovani Jsonu nepriatela " << "\n";
	}

	string meno = nepriatel["meno"].asString();
	string obrazok = nepriatel["obrazok"].asString();

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

		string typAkcie = akcia["typ"].asString();
		string menoAkcie = akcia["meno"].asString();
		string obrazokAkcie = akcia["obrazok"].asString();
		int rychlostCasteniaAkcie = akcia["rychlostCastenia"].asInt();
		int cooldownAkcie = akcia["cooldown"].asInt();
		int trvanieAkcie = akcia["trvanie"].asInt();
		string popisAkcie = akcia["popis"].asString();

		AkciaTyp enumTypAkcie;
		string statAkcie = akcia["stat"].asString();
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
			string druh = efekt["druh"].asString();
			string obrazokEfektu = efekt["obrazok"].asString();
			string statEfektu = efekt["stat"].asString();
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

		string meno = predmet["meno"].asString();
		string obrazok = predmet["obrazok"].asString();
		int typ = predmet["typ"].asInt();
		int cena = predmet["cena"].asInt();
		int uroven = predmet["uroven"].asInt();

		novyNepriatel->pridajDropItem(key.asString(), new Predmet(meno, typ, obrazok, cena, uroven));

	}


	return novyNepriatel;
}

int Loader::nahodneCislo(int min, int max) {
	if (min == max) return min;
	return min + rand() % (max - min);
}

vector<Predmet*>* Loader::nacitajObchod(string paMeno) {
	string cestaKObchodom = "./Data/Obchody/";

	vector<Predmet*>* obchod = new vector<Predmet*>();

	Json::Value jObchod;
	Json::Reader reader;
	ifstream json(cestaKObchodom + "" + paMeno + ".json", ifstream::binary);
	bool parsingSuccessful = reader.parse(json, jObchod, false);

	if (!parsingSuccessful)
	{
		cout << "chyba pri parsovani Jsonu obchodu " << "\n";
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

	string typTriedy = jPredmet["typTriedy"].asString();

	string meno = jPredmet["meno"].asString();
	string obrazok = jPredmet["obrazok"].asString();
	int typ = jPredmet["typ"].asInt();
	int cena = jPredmet["cena"].asInt();
	int uroven = jPredmet["uroven"].asInt();

	if (typTriedy == "elixir") {
		string co = jPredmet["stat"].asString();
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
	string cestaKuQuestom = "./Data/Questy/";

	Json::Value jQuest;
	Json::Reader reader;
	ifstream json(cestaKuQuestom + "" + paMeno + ".json", ifstream::binary);
	bool parsingSuccessful = reader.parse(json, jQuest, false);

	if (!parsingSuccessful)
	{
		cout << "chyba pri parsovani Jsonu questu " << paMeno << "\n";
	}

	string questNazov = jQuest["nazov"].asString();
	quest = hra->GetHrac()->Getmanazerquestov()->GetNacitanyQuest(questNazov);

	if (quest == nullptr) {

		string questPopis = jQuest["popis"].asString();
		int odmenaXp = jQuest["xp"].asInt();
		int odmenaZlato = jQuest["zlato"].asInt();
		string startNpc = jQuest["startNpc"].asString();
		string endNpc = jQuest["endNpc"].asString();

		quest = new Quest(questNazov, questPopis, odmenaXp, odmenaZlato, startNpc, endNpc,paMeno);

		//nacitanie polozky ktorá bude predstavova to èo bude rozprava npc o queste
		QuestPolozka* polozka = new QuestPolozka(quest->Getnazov());
		Json::Value polozkaTexty(Json::arrayValue);
		polozkaTexty = jQuest["polozkaTexty"];
		QuestPolozka* qp = (QuestPolozka*)polozka;
		for (unsigned int i = 0; i < polozkaTexty.size(); i++) {
			if (i == 0) {
				qp->vlozText(StavQuestu::NEPRIJATY, polozkaTexty[i].asString());
			}

			if (i == 1) {
				qp->vlozText(StavQuestu::ROZROBENY, polozkaTexty[i].asString());
			}

			if (i == 2) {
				qp->vlozText(StavQuestu::SPLNENIE_POZIADAVIEK, polozkaTexty[i].asString());
			}

			if (i == 3) {
				qp->vlozText(StavQuestu::DOKONCENY, polozkaTexty[i].asString());
			}

		}

		// nacitanie volieb ked sa hráè dostane na quest polozku 
		Json::Value volby(Json::objectValue);
		volby = jQuest["volby"];

		for (Json::Value::iterator it = volby.begin(); it != volby.end(); ++it) {
			Json::Value volbaID = it.key();
			Json::Value volbaData = (*it);


			int dalsia = volbaData["kam"].asInt();
			string volbaText = volbaData["text"].asString();
			string typ = volbaData["typ"].asString();
			if (typ == "") {
				polozka->pridajMoznost(new DialogVolba(volbaText, dalsia));
			}
			else if (typ == "upravaQuestu") {

				VolbaUpravaQuestu* volba = new VolbaUpravaQuestu(-1, quest);

				Json::Value volbaTexty(Json::arrayValue);
				volbaTexty = volbaData["volbaTexty"];

				for (unsigned int i = 0; i < volbaTexty.size(); i++) {
					if (i == 0) {
						volba->vlozText(StavQuestu::NEPRIJATY, volbaTexty[i].asString());
					}

					if (i == 1) {
						volba->vlozText(StavQuestu::ROZROBENY, volbaTexty[i].asString());
					}

					if (i == 2) {
						volba->vlozText(StavQuestu::SPLNENIE_POZIADAVIEK, volbaTexty[i].asString());
					}

					if (i == 3) {
						volba->vlozText(StavQuestu::DOKONCENY, volbaTexty[i].asString());
					}

				}

				polozka->pridajMoznost(volba);
			}
			else if (typ == "obchod") {
				string aky = volbaData["aky"].asString();
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
				volba->vlozText(StavQuestu::NEPRIJATY, volbaTexty[i].asString());
			}

			if (i == 1) {
				volba->vlozText(StavQuestu::ROZROBENY, volbaTexty[i].asString());
			}

			if (i == 2) {
				volba->vlozText(StavQuestu::SPLNENIE_POZIADAVIEK, volbaTexty[i].asString());
			}

			if (i == 3) {
				volba->vlozText(StavQuestu::DOKONCENY, volbaTexty[i].asString());
			}

		}

		quest->SetvolbaKuQuestu(volba);

		// nacitanie nasledujuceho questu
		string dalsi = jQuest["nasledujuci"].asString();
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

			string pTyp = poziadavka["typ"].asString();
			if (pTyp == "kill") {
				string pKoho = poziadavka["co"].asString();
				int pKolko = poziadavka["kolko"].asInt();
				string pKde = poziadavka["kde"].asString();
				quest->pridajPoziadavku(new PoziadavkaZabi(pKoho, pKolko, pKde));
			}
			else if (pTyp == "loot") {
				string pCo = poziadavka["co"].asString();
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


Zameranie* Loader::nacitajZameranie(string paMeno) {

	Json::Features::all();

	Zameranie* zameranie;

	string cestaKuZameraniam = "./Data/Zameranie/";

	Json::Value jZameranie;
	Json::Reader reader;
	ifstream json(cestaKuZameraniam + "" + paMeno + ".json", ifstream::binary);
	bool parsingSuccessful = reader.parse(json, jZameranie, false);

	if (!parsingSuccessful)
	{
		cout << "chyba pri parsovani Jsonu zamerania " << paMeno << "\n";
	}

	string nazov = jZameranie["nazov"].asString();
	int rastHp = jZameranie["rastHp"].asInt();
	int rastMp = jZameranie["rastMp"].asInt();
	int rastSila = jZameranie["rastSila"].asInt();
	int rastIntelekt = jZameranie["rastIntelekt"].asInt();
	int rastRychlost = jZameranie["rastRychlost"].asInt();

	zameranie = new Zameranie(nazov, rastHp, rastMp, rastSila, rastRychlost, rastIntelekt);
	
	Json::Value akcie(Json::objectValue);
	akcie = jZameranie["akcie"];

	for (Json::Value::iterator it = akcie.begin(); it != akcie.end(); ++it) {
		Json::Value volbaID = it.key();
		Json::Value jAkcia = (*it);
	
		Akcia* akcia;

		string trieda = jAkcia["trieda"].asString();
		string meno = jAkcia["meno"].asString();
		string obrazok = jAkcia["obrazok"].asString();
		int casCastenia = jAkcia["casCastenia"].asInt();
		int cooldown = jAkcia["cooldown"].asInt();
		int trvanie = jAkcia["trvanie"].asInt();
		string popis = jAkcia["popis"].asString();
		int mana = jAkcia["mana"].asInt();
		string typ = jAkcia["typ"].asString();

		if (trieda == "akciadmg") {
			double zaklad = jAkcia["zaklad"].asDouble();
			if (typ == "magicka") {
				akcia = new AkciaDmg(meno, obrazok, casCastenia, cooldown, trvanie, popis, mana, AkciaTyp::MAGICKA, zaklad);
			}
			else {
				akcia = new AkciaDmg(meno, obrazok, casCastenia, cooldown, trvanie, popis, mana, AkciaTyp::FYZICKA, zaklad);
			}
		}
		else if (trieda == "akcialiecenie") {
			double zaklad = jAkcia["zaklad"].asDouble();
			if (typ == "magicka") {
				akcia = new AkciaLiecenie(meno, obrazok, casCastenia, cooldown, trvanie, popis, mana, AkciaTyp::MAGICKA, zaklad);
			}
			else {
				akcia = new AkciaLiecenie(meno, obrazok, casCastenia, cooldown, trvanie, popis, mana, AkciaTyp::FYZICKA, zaklad);
			}
		}
		else {
			Efekt* efekt;
			Json::Value jEfekt(Json::objectValue);
			jEfekt = jAkcia["efekt"];

			string efektTyp = jEfekt["typ"].asString();
			bool efektNaHraca = jEfekt["naHraca"].asBool();

			if (efektTyp == "upravStat") {
				string efektAky = jEfekt["stat"].asString();
				int efektZaklad = jEfekt["zaklad"].asInt();
				efekt = new EfektUpravStat(obrazok, efektAky, efektZaklad);
			}


			akcia = new AkciaPridanieEfektu(meno,obrazok,casCastenia,cooldown,trvanie,popis,mana,efekt,efektNaHraca);
		}

		int akciaLevel = jAkcia["uroven"].asInt();

		if (akcia != nullptr) {
			zameranie->vlozAkciu(akcia, akciaLevel);
		}
	}

	return zameranie;


}

bool Loader::save() {

	Hrac* hrac = hra->GetHrac();
	QuestManager* qm = hrac->Getmanazerquestov();
	Inventar* inv = hrac->Getinventar();
	Statistika* stat = hrac->Getstatistika();

	Json::Value root;

	root["skusenosti"] = stat->Getskusenosti();
	root["zameranie"] = hrac->GetZameranie()->Getnazov();
	root["mapa"]["subor"] = hrac->getMapa()->Getmeno();
	root["mapa"]["posX"] = hrac->GetpolickoX();
	root["mapa"]["posY"] = hrac->GetpolickoY();
	root["mapa"]["orientacia"] = hrac->GetSmerPohladu();


	root["inventar"]["zlato"] = inv->Getzlato();
	root["inventar"]["kapacita"] = inv->Getkapacita();
	Json::Value predmety;
	
	for (int i = 0; i < inv->pocetPredmetov(); i++) {
		Predmet* predmet = inv->dajPredmetNaIndexe(i);

		Json::Value jPredmet;


		jPredmet["meno"] = predmet->Getmeno();
		jPredmet["obrazok"] = predmet->Getsobrazok();
		jPredmet["typ"] = predmet->Gettyp();
		jPredmet["cena"] = predmet->Getcena();
		jPredmet["uroven"] = predmet->Geturoven();


		if (dynamic_cast<Elixir*>(predmet) != NULL) {
			jPredmet["typTriedy"] = "elixir";
			Elixir* e = (Elixir*)predmet;
			jPredmet["stat"] = e->Getstat();
			jPredmet["oKolko"] = e->Getokolko();
		}
		else if (dynamic_cast<Zbran*>(predmet) != NULL) {
			jPredmet["typTriedy"] = "zbran";
			Zbran* z = (Zbran*)predmet;
			jPredmet["minDmg"] = z->Getminposkodenie();
			jPredmet["maxDmg"] = z->Getmaxposkodenie();
			jPredmet["rychlostUtoku"] = z->GetrychlostUtoku();
			jPredmet["hp"] = z->Gethp();
			jPredmet["hpMult"] = z->GethpMult();
			jPredmet["mp"] = z->Getmp();
			jPredmet["mpMult"] = z->GetmpMult();
			jPredmet["sila"] = z->Getsila();
			jPredmet["silaMult"] = z->GetsilaMult();
			jPredmet["intelekt"] = z->Getinteligencia();
			jPredmet["intelektMult"] = z->GetinteligenciaMult();
			jPredmet["rychlost"] = z->Getrychlost();
			jPredmet["rychlostMult"] = z->GetrychlostMult();
			jPredmet["obrana"] = z->Getarmor();
			jPredmet["obranaMult"] = z->GetarmorMult();


		}
		else if(dynamic_cast<Oblecenie*>(predmet) != NULL) {
			jPredmet["typTriedy"] = "oblecenie";

			Oblecenie* o = (Oblecenie*)predmet;

			jPredmet["hp"] = o->Gethp();
			jPredmet["hpMult"] = o->GethpMult();
			jPredmet["mp"] = o->Getmp();
			jPredmet["mpMult"] = o->GetmpMult();
			jPredmet["sila"] = o->Getsila();
			jPredmet["silaMult"] = o->GetsilaMult();
			jPredmet["intelekt"] = o->Getinteligencia();
			jPredmet["intelektMult"] = o->GetinteligenciaMult();
			jPredmet["rychlost"] = o->Getrychlost();
			jPredmet["rychlostMult"] = o->GetrychlostMult();
			jPredmet["obrana"] = o->Getarmor();
			jPredmet["obranaMult"] = o->GetarmorMult();

		}
		else {
			jPredmet["typTriedy"] = "normalny";
		}
		
		
		predmety.append(jPredmet);
	}
	
	root["inventar"]["predmety"] = predmety;
	
	Json::Value jOblecene;
	
	map<int, Predmet*>* oblecene = stat->Getoblecene();
	for (map<int,Predmet*>::iterator it = oblecene->begin(); it != oblecene->end(); ++it) {
		Predmet* predmet = it->second;

		Json::Value jPredmet;


		jPredmet["meno"] = predmet->Getmeno();
		jPredmet["obrazok"] = predmet->Getsobrazok();
		jPredmet["typ"] = predmet->Gettyp();
		jPredmet["cena"] = predmet->Getcena();
		jPredmet["uroven"] = predmet->Geturoven();


		if (dynamic_cast<Elixir*>(predmet) != NULL) {
			jPredmet["typTriedy"] = "elixir";
			Elixir* e = (Elixir*)predmet;
			jPredmet["stat"] = e->Getstat();
			jPredmet["oKolko"] = e->Getokolko();
		}
		else if (dynamic_cast<Zbran*>(predmet) != NULL) {
			jPredmet["typTriedy"] = "zbran";
			Zbran* z = (Zbran*)predmet;
			jPredmet["minDmg"] = z->Getminposkodenie();
			jPredmet["maxDmg"] = z->Getmaxposkodenie();
			jPredmet["rychlostUtoku"] = z->GetrychlostUtoku();
			jPredmet["hp"] = z->Gethp();
			jPredmet["hpMult"] = z->GethpMult();
			jPredmet["mp"] = z->Getmp();
			jPredmet["mpMult"] = z->GetmpMult();
			jPredmet["sila"] = z->Getsila();
			jPredmet["silaMult"] = z->GetsilaMult();
			jPredmet["intelekt"] = z->Getinteligencia();
			jPredmet["intelektMult"] = z->GetinteligenciaMult();
			jPredmet["rychlost"] = z->Getrychlost();
			jPredmet["rychlostMult"] = z->GetrychlostMult();
			jPredmet["obrana"] = z->Getarmor();
			jPredmet["obranaMult"] = z->GetarmorMult();


		}
		else if (dynamic_cast<Oblecenie*>(predmet) != NULL) {
			jPredmet["typTriedy"] = "oblecenie";

			Oblecenie* o = (Oblecenie*)predmet;

			jPredmet["hp"] = o->Gethp();
			jPredmet["hpMult"] = o->GethpMult();
			jPredmet["mp"] = o->Getmp();
			jPredmet["mpMult"] = o->GetmpMult();
			jPredmet["sila"] = o->Getsila();
			jPredmet["silaMult"] = o->GetsilaMult();
			jPredmet["intelekt"] = o->Getinteligencia();
			jPredmet["intelektMult"] = o->GetinteligenciaMult();
			jPredmet["rychlost"] = o->Getrychlost();
			jPredmet["rychlostMult"] = o->GetrychlostMult();
			jPredmet["obrana"] = o->Getarmor();
			jPredmet["obranaMult"] = o->GetarmorMult();

		}
		else {
			jPredmet["typTriedy"] = "normalny";
		}


		jOblecene.append(jPredmet);
		


	}
	
	root["oblecene"] = jOblecene;

	Json::Value jNedokoncene;
	deque < Quest*>* nedokonceneQuesty = qm->Getnedokoncenequesty();
	for (unsigned int i = 0; i < nedokonceneQuesty->size(); i++) {
		Quest* q = nedokonceneQuesty->at(i);
		vector<Poziadavka*>* poziadavky = q->Getpoziadavky();

		Json::Value jQuest;
		jQuest["subor"] = q->Getnazovsuboru();

		Json::Value jPoziadavky;

		for (unsigned int i = 0; i < poziadavky->size(); i++) {
			Poziadavka* p = poziadavky->at(i);
			if (dynamic_cast<PoziadavkaZabi*>(p) != NULL) {
				PoziadavkaZabi* pz = (PoziadavkaZabi*)p;
				Json::Value jPoziadavka;
				jPoziadavka["typ"] = "kill";
				jPoziadavka["koho"] = pz->Getkohozabit();
				jPoziadavka["aktualnyPocet"] = pz->Getaktualnypocetzabitych();
				jPoziadavky.append(jPoziadavka);
			}
			else if (dynamic_cast<PoziadavkaLoot*>(p) != NULL) {
				// netereba niè , po nacitani sa predmety daju do inventara a tato požiadavka sa kontroluje z inventara
			}
			

		}

		jQuest["poziadavky"] = jPoziadavky;

		jNedokoncene.append(jQuest);
	}
	root["nedokonceneQuesty"] = jNedokoncene;

	Json::Value jDokoncene;
	deque < Quest*>* dokonceneQuesty = qm->Getdokoncenequesty();
	for (unsigned int i = 0; i < dokonceneQuesty->size(); i++) {
		Quest* q = dokonceneQuesty->at(i);
		Json::Value jQuest(Json::objectValue);
		jQuest["subor"] = q->Getnazovsuboru();
		jDokoncene.append(jQuest);
	}

	root["dokonceneQuesty"] = jDokoncene;

	Json::StyledWriter styledWriter;
	cout << styledWriter.write(root);

	std::ofstream subor;
	subor.open("./Data/save");

	subor << styledWriter.write(root);

	subor.close();
	return true;
}

void Loader::load(){

	Json::Value save;
	Json::Reader reader;
	ifstream json("./Data/save", ifstream::binary);
	bool parsingSuccessful = reader.parse(json, save, false);

	if (!parsingSuccessful)
	{
		cout << "chyba pri parsovani savu\n";
		throw 1;
	}
	else {

		int hracSkusenosti = save["skusenosti"].asInt();
		string zameranie = save["zameranie"].asString();

		Hrac* hrac = new Hrac(nacitajZameranie(zameranie));

		hrac->Getstatistika()->vlozAkciu(new AkciaPoskodenieZbranou("Attack", "Attack with equipped weapon.", hrac->Getstatistika()));
		hra->SetHrac(hrac);
		hrac->pridajSkusenosti(hracSkusenosti, false);
		

		string mapa = save["mapa"]["subor"].asString();
		int posX = save["mapa"]["posX"].asInt();
		int posY = save["mapa"]["posY"].asInt();
		int orientacia = save["mapa"]["orientacia"].asInt();
		nacitajMapu(mapa, posX, posY, orientacia);
		
		Inventar* inv = hrac->Getinventar();
		inv->Setzlato(save["inventar"]["zlato"].asInt());
		inv->Setkapacita(save["inventar"]["kapacita"].asInt());

		Json::Value oblecene(Json::arrayValue);
		oblecene = save["oblecene"];
		if (!oblecene.isNull()) {
			for (unsigned int i = 0; i < oblecene.size(); i++) {
				Predmet* p = parsujPredmet(oblecene[i]);
				inv->pridajPredmet(p);
				p->pouzi(hrac);
			}
				
		}


		Json::Value predmety(Json::arrayValue);
		predmety = save["inventar"]["predmety"];
		if (!predmety.isNull()) {
			for (unsigned int i = 0; i < predmety.size(); i++) {
				Predmet* p = parsujPredmet(predmety[i]);
				inv->pridajPredmet(p);
			}

		}

		QuestManager* mng = hrac->Getmanazerquestov();

		Json::Value jDokonceneQuesty(Json::arrayValue);
		jDokonceneQuesty = save["dokonceneQuesty"];
		if (!jDokonceneQuesty.isNull()) {
			for (unsigned int i = 0; i < jDokonceneQuesty.size(); i++) {
				Quest* q = nacitajQuest(jDokonceneQuesty[i]["subor"].asString());
				q->setStav(StavQuestu::DOKONCENY);
				mng->pridajDoDokoncenych(q);
			}

		}


		Json::Value jNedokonceneQuesty(Json::arrayValue);
		jNedokonceneQuesty = save["nedokonceneQuesty"];
		if (!jNedokonceneQuesty.isNull()) {
			for (unsigned int i = 0; i < jNedokonceneQuesty.size(); i++) {
				Quest* q = nacitajQuest(jNedokonceneQuesty[i]["subor"].asString());
				vector<Poziadavka*>* poziadavky = q->Getpoziadavky();

				Json::Value jPoziadavky(Json::arrayValue);
				jPoziadavky = jNedokonceneQuesty[i]["poziadavky"];
				if (!jPoziadavky.isNull()) {
					for (unsigned int i = 0; i < jPoziadavky.size(); i++) {
						Json::Value jPoziadavka(Json::objectValue);
						jPoziadavka = jPoziadavky[i];
						string typ = jPoziadavka["typ"].asString();
						

						if (typ == "kill") {
							// pridanie poctu zabiti
							int aktPocet = jPoziadavka["aktualnyPocet"].asInt();
							
							for (int i = 0; i < aktPocet; i++) {
								for (unsigned int j = 0; j < poziadavky->size(); j++) {
									poziadavky->at(j)->akcia(jPoziadavka["koho"].asString());
								}

							}
							
						}// iff kill


					}
				}

				q->kontrola();
				mng->pridajDoNedokoncenych(q);
			}

		}


		hra->zmenStavRozhrania("hranieHry");

	}

}
