#include "Mapa.h"
#include "Policko.h"
#include "Hrac.h"
#include <iostream>
#include "json.h"
#include <fstream>
#include <map>
#include <array>
#include "PolickoDvere.h"
#include "Hra.h"

Mapa::Mapa(std::string menoMapy, Hrac* paHrac,Hra* hra) {
	this->hrac = paHrac;
	this->hra = hra;
	nacitajMapu(menoMapy);
	smerPohybu = 0;
}

Mapa::Mapa(std::string menoMapy,Hrac* paHrac,Hra* hra,int posHracaX, int posHracaY, int smerPohladu) {
	this->hrac = paHrac;
	this->hra = hra;
	smerPohybu = 0;
	nacitajMapu(menoMapy);
	posunHracaNaPolicko(posHracaX, posHracaY,smerPohladu);
	

}



Mapa::~Mapa() {
	
	for (int i = 0; i < vyska; i++)
	{
		for (int j = 0; j < vyska; j++)
		{
			delete mapa[i][j];
		}
	}


}


void Mapa::setHrac(Hrac* paHrac) {
	hrac = paHrac;
}


void Mapa::posun(int posunX, int posunY) {
	this->posunX += posunX;
	this->posunY += posunY;

}

void Mapa::render(sf::RenderWindow* okno) {

	sf::Sprite* sprite;

	//od akeho policka po ake policko sa ma vykreslovat mapa
	int odX = (int)(hrac->GetpolickoX() - 34 * (1.0*hrac->GetoffsetX() / okno->getSize().x)-2);
	if (odX <0) {
		odX = 0;
	}

	int doX = (int)(hrac->GetpolickoX() + 34 *(1-(1.0*hrac->GetoffsetX()/okno->getSize().x ))+2);
	if (doX >= sirka) {
		doX = sirka - 1;
	}

	int odY = (int)(hrac->GetpolickoY() - 24 * (1.0*hrac->GetoffsetY() / okno->getSize().y) - 1);
	if (odY <0) {
		odY = 0;
	}
	
	int doY = (int)(hrac->GetpolickoY() + 24 * (1 - (1.0*hrac->GetoffsetY() / okno->getSize().y)) + 1);
	if (doY >= vyska) {
		doY = vyska - 1;
	}

	for (int vrstva = 0; vrstva < 4; vrstva++) {

		for (int i = odX; i < doX; i++)
		{
			for (int j = odY; j < doY; j++)
			{
				if (vrstva == 1) {
					hrac->render(okno);
				}
				sprite = mapa[i][j]->dajObrazokVrstvy(vrstva);
				sprite->setPosition(sf::Vector2f(32.f * i + posunX, 32.f * j+posunY));
				okno->draw(*sprite);
			}
		}
	}
	
}

void Mapa::hracSkocilNaPolicko(int x, int y) {
	mapa[x][y]->hracSkok(hrac);
}

void Mapa::posunHracaNaPolicko(int x, int y,int smerPohladu) {
	int offsetHracaX = x*32;
	int offsetHracaY = y*32;
	int posunMapyX = 0;
	int posunMapyY = 0;

	hrac->setPolickoX(x);
	hrac->setPolickoY(y);
	if (offsetHracaX > 350) {
		posunMapyX = offsetHracaX - 350;
		offsetHracaX = 350;
	}

	if (offsetHracaY > 350) {
		posunMapyY = offsetHracaY - 350;
		offsetHracaY = 350;
	}
	hrac->setOffsetX(offsetHracaX);
	hrac->setOffsetY(offsetHracaY);
	posunX = -posunMapyX;
	posunY = -posunMapyY;

	switch (smerPohladu)
	{
	case 0:
		hrac->zmenSmerPohladu(SmerPohladu::dole);
		break;
	case 1:
		hrac->zmenSmerPohladu(SmerPohladu::vpravo);
		break;
	case 2:
		hrac->zmenSmerPohladu(SmerPohladu::hore);
		break;
	case 3:
		hrac->zmenSmerPohladu(SmerPohladu::vlavo);
		break;
	default:
		hrac->zmenSmerPohladu(SmerPohladu::dole);
		break;
	}




}

void Mapa::update(double delta) {

	switch (smerPohybu)
	{
	case 0:
		break;
	case 1:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(-1, 0);
		}
		else {
			hrac->setPolickoX(hrac->GetpolickoX() +1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 2:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(+1, 0);
		}
		else {
			hrac->setPolickoX(hrac->GetpolickoX() - 1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 3:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta ++;
			posun(0, 1);
		}
		else {
			hrac->setPolickoY(hrac->GetpolickoY() - 1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 4:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(0, -1);
		}
		else {
			hrac->setPolickoY(hrac->GetpolickoY() +1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;

	default:
		break;
	}
}



void Mapa::posunVpravo() {
	pohybDelta = 0;
	smerPohybu = 1;
}

void Mapa::posunVlavo() {
	pohybDelta = 0;
	smerPohybu = 2;
	hybeSa = true;
}

void Mapa::posunHore() {
	pohybDelta = 0;
	smerPohybu = 3;
	hybeSa = true;
}

void Mapa::posunDole() {
	pohybDelta = 0;
	smerPohybu = 4;
	hybeSa = true;
}

int Mapa::Getsmerpohybu() {
	return smerPohybu;
}

int Mapa::Getvyska() {
	return vyska;
}


int Mapa::Getsirka() {
	return sirka;
}


bool Mapa::jeMoznyPohyb(int x, int y) {
	if (x < 0 || x >= sirka || y < 0 || y >= vyska) {
		return false;
	}
	return mapa[x][y]->jePrechodne();
}


bool Mapa::GetNacitava() {
	return nacitavam;
}

void Mapa::nacitajMapu(std::string paMeno) {
	nacitavam = true;

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

		Json::Value root;   // will contains the root value after parsing.
		Json::Reader reader;
		std::ifstream test(cestaKMapam+""+ paMeno +".json", std::ifstream::binary);
		std::cout << cestaKMapam +"" + paMeno + ".json" << std::endl;
		bool parsingSuccessful = reader.parse(test, root, false);

		if (!parsingSuccessful)
		{
			std::cout << "chyba pri parsovani Jsonu" << "\n";
		}

		vyska = root["height"].asInt();
		sirka = root["width"].asInt();


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

			polickoDvere[x][y]= new PolickoDvere(true,hra,kam, posX, posY, smerPohladu);
		}

		Json::Value objekt(Json::objectValue);
		objekt = root["tiles"];

		for (Json::Value::iterator it = objekt.begin(); it != objekt.end(); ++it)

		{

			Json::Value key = it.key();

			Json::Value value = (*it);

			std::string menoTextury = value["image"].asCString();
			int id = atoi(key.asCString());

			if (menoTextury.find(".") != std::string::npos) {
				textury[id + 1] = new sf::Texture();
				if (!textury[id + 1]->loadFromFile(cestakTexturam+"" + menoTextury, sf::IntRect(0, 0, 32, 32))) {
					std::cout << "Chyba nahravania textury policka" << std::endl;
				}
			}
			else {
				specialnePolicka[id+1] = menoTextury;
			}
			
		}

		for (int i = 0; i < vyska; i++) {
			for (int j = 0; j < sirka; j++)
			{
				
				
				int idTextury1 = root["Vrstva1"][i*vyska + j].asInt();
				int idTextury2 = root["Vrstva2"][i*vyska + j].asInt();
				int idTextury3 = root["Vrstva3"][i*vyska + j].asInt();
				
				if (polickoDvere[i][j] != nullptr) {
					mapa[j][i] = polickoDvere[i][j];
				}
				else {

					if (idTextury2 != 0) {
						mapa[j][i] = new Policko(false);
					}
					else {

						mapa[j][i] = new Policko(true);
					}
				}

				if (idTextury1 != 0) {
					mapa[j][i]->nastavTexturu(textury[idTextury1], 0);
				}
				if (idTextury2 != 0) {
					mapa[j][i]->nastavTexturu(textury[idTextury2], 1);
				}
				if(idTextury3!= 0){
					mapa[j][i]->nastavTexturu(textury[idTextury3], 2);
				}

			}

		}


		/*
		for (int i = 0; i < vyska; i++) {
			for (int j = 0; j < sirka; j++) {

				int idSpecPolicka = root["akcnePolicka"][i*vyska + j].asInt();
				
				if (specialnePolicka[idSpecPolicka] == "start") {
					posunHracaNaPolicko(j, i);
				}
			
			}
		}
		*/
		alive = false;
	}
	nacitavam = false;
}