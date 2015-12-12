#include "Mapa.h"
#include "Policko.h"
#include "Hrac.h"
#include <iostream>
#include "json.h"
#include <fstream>
#include <map>

Mapa::Mapa(std::string menoMapy,Hrac* paHrac) {
	this->hrac = paHrac;
	nacitajMapu(menoMapy);

}



Mapa::~Mapa() {
	for (int i = 0; i < sirka; i++)
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

void Mapa::posunHracaNaPolicko(int x, int y) {
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


void Mapa::nacitajMapu(std::string paMeno) {

	std::string cestaKMapam = "Data/Mapy/";

	bool alive = true;
	while (alive) {

		Json::Value root;   // will contains the root value after parsing.
		Json::Reader reader;
		std::ifstream test(cestaKMapam+""+paMeno+"/"+paMeno+".json", std::ifstream::binary);
		std::cout << cestaKMapam + "" + paMeno + "/" + paMeno + ".json" << std::endl;
		bool parsingSuccessful = reader.parse(test, root, false);

		if (!parsingSuccessful)
		{
			std::cout << "chyba pri parsovani Jsonu" << "\n";
		}

		vyska = root["height"].asInt();
		sirka = root["width"].asInt();

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
				if (!textury[id + 1]->loadFromFile(cestaKMapam + "" + paMeno + "/" + menoTextury, sf::IntRect(0, 0, 32, 32))) {
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
				
				if (idTextury2 != 0) {
					mapa[j][i] = new Policko(false);
				}
				else {

					mapa[j][i] = new Policko(true);
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

		for (int i = 0; i < vyska; i++) {
			for (int j = 0; j < sirka; j++) {

				int idSpecPolicka = root["akcnePolicka"][i*vyska + j].asInt();
				
				if (specialnePolicka[idSpecPolicka] == "start") {
					posunHracaNaPolicko(j, i);
				}
			
			}
		}
		
		alive = false;
	}

}