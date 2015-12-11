#include "Mapa.h"
#include "Policko.h"
#include "Hrac.h"
#include <iostream>
#include "json.h"
#include <fstream>
#include <map>

Mapa::Mapa(Hrac* paHrac) {
	this->hrac = paHrac;

	nacitajMapu("mapa1");
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

	for (int vrstva = 0; vrstva < 4; vrstva++) {

		for (int i = 0; i < sirka; i++)
		{
			for (int j = 0; j < vyska; j++)
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
			pohybDelta++;
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


void Mapa::nacitajMapu(std::string paMeno) {

	std::map<int, sf::Texture*> textury;

	std::string cestaKMapam = "Data/Mapy/";


	/*
	for (int i = 0; i < sirka; i++)
	{
	for (int j = 0; j < vyska; j++)
	{
	
	}
	}*/


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

			textury[id+1] = new sf::Texture() ;
			if (!textury[id+1]->loadFromFile(cestaKMapam+""+paMeno+"/"+menoTextury, sf::IntRect(0, 0, 32, 32))) {
				std::cout << "Chyba nahravania textury policka" << std::endl;
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
		
		alive = false;
	}

}