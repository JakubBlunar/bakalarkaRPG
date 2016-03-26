#include "Generator.h"


#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <math.h>
#include <io.h>
#include <time.h>

#include "Pouzitelny.h"
#include "Zbran.h"
#include "Oblecenie.h"
#include "Elixir.h"

Generator* Generator::instancia = NULL;

Generator* Generator::Instance()
{
	if (!instancia) {
		srand((unsigned int)time(NULL));
		instancia = new Generator();
	}
	return instancia;
}


int Generator::randomInt(int min, int max) {
	if (min == max) {
		return min;
	}
	return min + (rand() % (int)(max - min + 1));
}

Predmet* Generator::nahodnyElixir() {

	Elixir* elixir;

	int kolko = randomInt(1, 6) * 25;

	string obrazok = "";
	string stat = "";
	string nazov = "";

	int lvl = 1;

	int p = randomInt(0, 99);
	if (p < 70) {
		nazov = "Hp potion";
		stat = "hp";
		obrazok = "elixir";
	}
	else {
		nazov = "Mp potion";
		stat = "mp";
		obrazok = "manae";
	}

	elixir = new Elixir(nazov, 12, obrazok, 5 * kolko, lvl, stat, kolko);
	return elixir;

}


Predmet* Generator::nahodneOblecenie(int paUroven) {
	
	Pouzitelny* oblecenie;


	int typ = randomInt(1, 8);
	string menoOblecenia = "";


	string cesta = "./Data/Grafika/Predmety/";
	switch (typ)
	{
	case (1) :
		cesta += "Helma";
		menoOblecenia = "Helm";
		break;
	case (2) :
		cesta += "Ramena";
		menoOblecenia = "Shoulders";
		break;
	case (3) :
		cesta += "Brnenie";
		menoOblecenia = "Armor";
		break;
	case (4) :
		cesta += "Nohavice";
		menoOblecenia = "Trousers";
		break;
	case (5) :
		cesta += "Nahrdelnik";
		menoOblecenia = "Necklace";
		break;
	case (6) :
		cesta += "Prsten";
		menoOblecenia = "Ring";
		break;
	case (7) :
		cesta += "Rukavice";
		menoOblecenia = "Gloves";
		break;
	case (8) :
		cesta += "Topanky";
		menoOblecenia = "Boots";
		break;
	}
	cesta += "/*.png";
	vector<string>* obrazky;
	obrazky = najdiSubory(cesta);

	std::string obrazok = obrazky->at(randomInt(0, obrazky->size() - 1));
	size_t lastindex = obrazok.find_last_of(".");
	obrazok = obrazok.substr(0, lastindex);
	delete obrazky;

	vector<string> list1 = { "adept", "raiding", "fiendish", "noble", "vampiric", "socketed", "brutal", "dazzling" };
	vector<string> list2 = { "marauder", "champion", "mage", "barbarian", "warrior", "rogue" };
	vector<string> list3 = { "of invasion", "of war", "of love", "of peace", "of fire", "of frost" };

	string pridmeno = "";
	int p = randomInt(0, 99);
	if (p < 40) {
		pridmeno = list1.at(randomInt(0, list1.size() - 1)) + " ";
	}

	string classa = "";
	p = randomInt(0, 99);
	if (p < 40) {
		classa = list2.at(randomInt(0, list2.size() - 1)) + " ";
	}

	string dodatok = "";
	p = randomInt(0, 99);
	if (p < 40) {
		dodatok = " " + list3.at(randomInt(0, list3.size() - 1)) + " ";
	}

	string nazov = pridmeno + classa + menoOblecenia + dodatok;
	int cena = randomInt(paUroven * 45, paUroven * 75);
	oblecenie = new Oblecenie(nazov, typ, obrazok, cena, paUroven);

	generujStatistiky(oblecenie);

	cout << endl;
	return oblecenie;
}




Predmet* Generator::nahodnaZbran(int paUroven) {

	int typ = randomInt(9,11);
	ZbranTyp enumTyp;

	std::string obrazok;
	string cesta = "./Data/Grafika/Predmety/";
	if (typ == 9) {
		enumTyp = static_cast<ZbranTyp>(randomInt(0, 3));
		cesta += "Zbran1h/";	
		switch (enumTyp)
		{
		case 0:
			obrazok += "Onehand_Axe/";
			cesta += "Onehand_Axe/";
			break;
		case 1:

			obrazok += "Onehand_Sword/";
			cesta += "Onehand_Sword/";
			break;
		case 2:
			obrazok += "Dagger/";
			cesta += "Dagger/";
			break;
		case 3:
			obrazok += "Onehand_Mace/";
			cesta += "Onehand_Mace/";
			break;
		}

	}
	else if (typ == 10) {
		enumTyp = static_cast<ZbranTyp>(randomInt(4, 8));
		cesta += "Zbran2h/";
		switch (enumTyp)
		{
		case 4:
			obrazok += "Twohand_Mace/";
			cesta += "Twohand_Mace/";
			break;
		case 5:
			obrazok += "Stave/";
			cesta += "Stave/";
			break;
		case 6:
			obrazok += "Polearm/";
			cesta += "Polearm/";
			break;
		case 7:
			obrazok += "Twohand_Axe/";
			cesta += "Twohand_Axe/";
			break;
		case 8:
			obrazok += "Twohand_Sword/";
			cesta += "Twohand_Sword/";
			break;
		}
	}else{ 
		enumTyp = ZbranTyp::SHIELD;
		cesta += "Stit/";
	}
	cesta += "*.png";
	vector<string>* obrazky;
	obrazky = najdiSubory(cesta);

	std::string menoobrazku = obrazky->at(randomInt(0, obrazky->size() - 1));
	size_t lastindex = menoobrazku.find_last_of(".");
	obrazok += menoobrazku.substr(0, lastindex);


	delete obrazky;

	vector<string> list1 = { "adept", "raiding", "fiendish", "noble", "vampiric", "socketed", "brutal", "dazzling" };
	vector<string> list2 = { "marauder", "champion", "mage", "barbarian", "warrior", "rogue" };
	vector<string> list3 = { "of invasion", "of war", "of love", "of peace", "of fire", "of frost" };

	string pridmeno = "";
	int p = randomInt(0, 99);
	if (p < 40) {
		pridmeno = list1.at(randomInt(0, list1.size()-1)) + " ";
	}

	string classa = "";
	p = randomInt(0, 99);
	if (p < 40) {
		classa = list2.at(randomInt(0, list2.size()-1)) + " ";
	}

	string dodatok = "";
	p = randomInt(0, 99);
	if (p < 40) {
		dodatok = " " + list3.at(randomInt(0, list3.size()-1)) + " ";
	}
	
	
	string menoZbrane = pridmeno + classa;

	switch (enumTyp)
	{
	case 0:
		menoZbrane += "Axe";
		break;
	case 1:
		menoZbrane += "Sword";
		break;
	case 2:
		menoZbrane += "Dagger";
		break;
	case 3:
		menoZbrane += "Mace";
		break;
	case 4:
		menoZbrane += "Warhammer";
		break;
	case 5:
		menoZbrane += "Stave";
		break;
	case 6:
		menoZbrane += "Polearm";
		break;
	case 7:
		menoZbrane += "Greataxe";
		break;
	case 8:
		menoZbrane += "Greatsword";
		break;
	case 9:
		menoZbrane += "Shield";
		break;
	}

	menoZbrane += dodatok;
	/*
	if (typ != 11) {
		vector<string> oneHand = { "Sword", "Axe", "Dagger","Mace" };
		vector<string> twoHand = { "Greatsword","Greataxe","Polearm","Staff","Warhammer" };
		if (typ == 9) {
			menoZbrane = pridmeno + classa + oneHand.at(randomInt(0, oneHand.size()-1)) + dodatok;
		}

		if (typ == 10) {
			menoZbrane = pridmeno + classa + twoHand.at(randomInt(0, twoHand.size()-1)) + dodatok;
		}
	}
	else {
		menoZbrane = pridmeno + classa + "Shield" + dodatok;
	}*/
	
	int cena = randomInt(paUroven * 45, paUroven * 75);


	Zbran* zbran;
	if (typ != 11) {
		int minPoskodenie = 0;
		int maxPoskodenie = 0;
		int poskOd;
		if (paUroven <= 7) {
			poskOd = 1;
		}
		else {
			poskOd = paUroven - 7;
		}

		minPoskodenie = randomInt(poskOd, paUroven);
		maxPoskodenie = randomInt(paUroven, paUroven + 2);

		if (typ == 10) {
			minPoskodenie = (int)round(minPoskodenie*1.3);
			maxPoskodenie = (int)round(maxPoskodenie*1.3);
		}

		int rychlost = randomInt(1, 5) * 500;

		zbran = new Zbran(menoZbrane, typ, obrazok, cena,paUroven,minPoskodenie,maxPoskodenie,rychlost);
	}
	else {
		zbran = new Zbran(menoZbrane, typ, obrazok, cena, paUroven, 0,0, 2000000);
	}
	generujStatistiky(zbran);

	return zbran;
}

void Generator::generujStatistiky(Pouzitelny* paPredmet) {


	if (paPredmet->Gettyp() != 5  && paPredmet->Gettyp() != 6) {
		int stat = randomInt(0, paPredmet->Geturoven() / 4 + 1);
		int aky = randomInt(0, 5);
		switch (aky)
		{
		case 0:
			paPredmet->Setsila(stat);
			break;
		case 1:
			paPredmet->Setrychlost(stat);
			break;
		case 2:
			paPredmet->Setinteligencia(stat);
			break;
		case 3:
			paPredmet->Sethp(stat*5);
			break;
		case 4:
			paPredmet->Setmp(stat*5);
			break;
		default:
			break;
		}
	}
	else {
		double stat = randomInt(1, paPredmet->Geturoven() / 8 + 1);
		int aky = randomInt(0, 5);
		switch (aky)
		{
		case 0:
			paPredmet->SetsilaMult(stat / 100);
			break;
		case 1:
			paPredmet->SetrychlostMult(stat / 100);
			break;
		case 2:
			paPredmet->SetinteligenciaMult(stat/100);
			break;
		case 3:
			paPredmet->SethpMult(stat / 100);
			break;
		case 4:
			paPredmet->SetmpMult(stat / 100);
			break;
		default:
			break;
		}
	}


	// ak to je nejaké brnenie
	if ((paPredmet->Gettyp() < 5 && paPredmet->Gettyp() > 0) || (paPredmet->Gettyp() == 7 || paPredmet->Gettyp() == 8)) {
		int armor = randomInt(1, paPredmet->Geturoven() * 3);
		paPredmet->Setarmor(armor);
	}

	//stit
	if (paPredmet->Gettyp() == 11) {
		int armor = randomInt(1, paPredmet->Geturoven() * 6);
		paPredmet->Setarmor(armor);
	}

}


vector<string>* Generator::najdiSubory(string cesta) {
	vector<string> *subory = new vector<string>();

	_finddata_t data;
	int ff = _findfirst(cesta.c_str(), &data);
	if (ff != -1)
	{
		int res = 0;
		while (res != -1)
		{
			subory->push_back(data.name);
			res = _findnext(ff, &data);
		}
		_findclose(ff);
	}
	return subory;
}

