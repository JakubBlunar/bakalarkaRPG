#include "Mapa.h"
#include "Policko.h"
#include "Hrac.h"
#include <iostream>
#include "PolickoDvere.h"
#include "Hra.h"
#include "Npc.h"
#include "StavHranieHry.h"
#include "Oblast.h"

#include "QuestManager.h"
#include "Quest.h"

Mapa::Mapa(string menoMapy, Hrac* paHrac, Hra* hram, int paSirka, int paVyska) {
	moznyNepriatelia = new vector<string>();
	this->menoMapy = menoMapy;
	this->hrac = paHrac;
	this->hra = hram;
	posunX = 0;
	posunY = 0;
	vyska = paVyska;
	sirka = paSirka;
	pohybDelta = 0;
	smerPohybu = PohybMapy::STOJI;

	if (!batohTextura.loadFromFile("./Data/Grafika/Predmety/batoh.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Chyba nahravania textury batohu" << endl;
	}
	batoh.setTexture(batohTextura);

	if (!zltyOtaznikTextura.loadFromFile("./Data/Grafika/otaznik.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Chyba nahravania textury" << endl;
	}
	zltyOtaznik.setTexture(zltyOtaznikTextura);

	if (!zltyVykricnikTextura.loadFromFile("./Data/Grafika/vykricnik.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Chyba nahravania textury" << endl;
	}
	zltyVykricnik.setTexture(zltyVykricnikTextura);

	if (!sedyOtaznikTextura.loadFromFile("./Data/Grafika/sivy_otaznik.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Chyba nahravania textury" << endl;
	}
	sedyOtaznik.setTexture(sedyOtaznikTextura);

	mapa = new Policko**[sirka];
	for (int i = 0; i < sirka; ++i) {
		mapa[i] = new Policko*[vyska];
	}

	for (int i = 0; i < sirka; ++i) {
		for (int j = 0; j < vyska; ++j) {
			mapa[i][j] = nullptr;
		}
	}

	hrobSuradnice = sf::Vector2i(0, 0);
	minimapa = false;
}

Mapa::~Mapa() {
	for (unsigned int i = 0; i < oblasti.size(); i++) {
		delete oblasti[i];
	}

	
	for (int i = 0; i < sirka; i++)
	{
		for (int j = 0; j < vyska; j++)
		{
			delete mapa[i][j];
		}
	}

	for (int i = 0; i < sirka; i++) {
		delete[] mapa[i];
	}

	delete[] mapa;
}

string Mapa::Getmeno() const
{
	return menoMapy;
}

void Mapa::setHrac(Hrac* paHrac) {
	hrac = paHrac;
}

void Mapa::posun(int posunX, int posunY) {
	this->posunX += posunX;
	this->posunY += posunY;

}

void Mapa::setHrobSuradnice(sf::Vector2i paSuradnice) {
	hrobSuradnice = paSuradnice;
}

sf::Vector2i Mapa::Gethrobsuradnice() const
{
	return hrobSuradnice;
}

void Mapa::render(sf::RenderWindow* okno) {
	view.reset(sf::FloatRect(posunX + 0.f, posunY + 0.f, okno->getSize().x + 0.f, okno->getSize().y + 0.f));
	okno->setView(view);

	int odX = posunX / 32 - 2;
	int doX = (posunX + okno->getSize().x) / 32 + 2;
	int odY = posunY / 32 - 2;
	int doY = (posunY + okno->getSize().y) / 32 + 2;

	if (odX < 0) odX = 0;
	if (doX > sirka) doX = sirka;
	if (odY < 0) odY = 0;
	if (doY > vyska) doY = vyska;

	sf::Sprite* sprite;
	for (int vrstva = 0; vrstva < 3; vrstva++) {

		for (int i = odX; i < doX; i++)
		{
			for (int j = odY; j < doY; j++)
			{

				sprite = mapa[i][j]->dajObrazokVrstvy(vrstva);
				sprite->setPosition(sf::Vector2f(32.f * i, 32.f * j));
				okno->draw(*sprite);

				if (vrstva == 0) {
					if (mapa[i][j]->polozenyPredmet()) {
						batoh.setPosition(sf::Vector2f(32.f * i, 32.f * j));
						okno->draw(batoh);
					}
				}

				if (vrstva == 2 && hrac->GetpolickoY() < j) {
					if (mapa[i][j]->Getnpc() != nullptr) {
						sf::Sprite* npcObrazok = mapa[i][j]->Getnpc()->dajObrazok();
						npcObrazok->setPosition(sf::Vector2f(32.f * i, 32 - npcObrazok->getGlobalBounds().height + 32.f* j));
						okno->draw(*npcObrazok);
					}
				}

				if (vrstva == 1) {
					hrac->render(okno);
				}

				if (vrstva == 1 && hrac->GetpolickoY() >= j) {
					if (mapa[i][j]->Getnpc() != nullptr) {
						sf::Sprite* npcObrazok = mapa[i][j]->Getnpc()->dajObrazok();
						npcObrazok->setPosition(sf::Vector2f(32.f * i, 32 - npcObrazok->getGlobalBounds().height + 32.f* j));
						okno->draw(*npcObrazok);
					}
				}

				if (vrstva == 2) {
					if (mapa[i][j]->Getnpc() != nullptr) {
						Npc* npc = mapa[i][j]->Getnpc();
						QuestManager* mng = hrac->Getmanazerquestov();
						Quest* quest = mng->Getzaciatocnyquestnpc(npc->Getmeno());

						if (quest == nullptr) {
							quest = mng->Getkonciaciquestnpc(npc->Getmeno());
						}

						if (quest != nullptr) {

							switch (quest->Getstav())
							{
							case StavQuestu::NEPRIJATY:
								zltyVykricnik.setPosition(sf::Vector2f(32.f * i, 32 - 48.f + 32.f* j - 32.f));
								okno->draw(zltyVykricnik);
								break;
							case StavQuestu::ROZROBENY:
								sedyOtaznik.setPosition(sf::Vector2f(32.f * i, 32 - 48.f + 32.f* j - 32.f));
								okno->draw(sedyOtaznik);
								break;
							case StavQuestu::SPLNENIE_POZIADAVIEK:
								zltyOtaznik.setPosition(sf::Vector2f(32.f * i, 32 - 48.f + 32.f* j - 32.f));
								okno->draw(zltyOtaznik);
								break;
							case DOKONCENY: break;
							default: break;
							}
						}


					}
				}

			}
		}
	}
	okno->setView(okno->getDefaultView());
	if (minimapa) {

		int sirkaRamceka = okno->getSize().x - 60;
		int vyskaRamceka = okno->getSize().y - 70;
		
		sf::RectangleShape pozadie;
		pozadie.setPosition(sf::Vector2f(30.f, 30.f));
		pozadie.setSize(sf::Vector2f(sirkaRamceka+0.f,vyskaRamceka+0.f));
		pozadie.setFillColor(sf::Color(0, 0, 0, 75));
		okno->draw(pozadie);

		int sirkaPolicka = sirkaRamceka / sirka;
		int vyskaPolicka = vyskaRamceka / vyska;

		if (sirkaPolicka > vyskaPolicka) {
			sirkaPolicka = vyskaPolicka;
		}
		sf::RectangleShape policko;
		policko.setSize(sf::Vector2f(sirkaPolicka+0.f, vyskaPolicka+0.f));
	
		for(int i = 0; i < sirka; i++)
		{
			for (int j = 0; j < vyska; j++)
			{
				if (mapa[i][j]->jePrechodne()) {
					
					if (dynamic_cast<PolickoDvere*>(mapa[i][j]) == nullptr) {
						policko.setFillColor(sf::Color(255, 0, 0, 75));
					}
					else {
						policko.setFillColor(sf::Color::White);
					}

				}else{
					policko.setFillColor(sf::Color::Transparent);
				}

				if (i == hrac->GetpolickoX() && j == hrac->GetpolickoY()) {
					policko.setFillColor(sf::Color::Yellow);
				}

				policko.setPosition(sf::Vector2f( 30.f+ i*sirkaPolicka,30.f+j*vyskaPolicka ));
				okno->draw(policko);

			}
		}

	}
}

sf::FloatRect Mapa::Getzobrazenaoblast() const
{
	return sf::FloatRect(posunX + 0.f, posunY + 0.f, view.getSize().x + 0.f, view.getSize().y + 0.f);
}

void Mapa::update() {

	for (int i = 0; i < sirka; i++)
	{
		for (int j = 0; j < vyska; j++)
		{
			if (mapa[i][j]->kedyZmazatPredmety() != -1 && mapa[i][j]->kedyZmazatPredmety() < casovac.getElapsedTime().asSeconds()) {
				mapa[i][j]->zmazPolozenePredmety();
			}
		}

	}

	switch (smerPohybu)
	{
	case PohybMapy::STOJI:
		break;
	case PohybMapy::VPRAVO:
		if (pohybDelta < 32) {
			pohybDelta++;
			posun(1, 0);
		}
		else {
			smerPohybu = PohybMapy::STOJI;
			pohybDelta = 0;
		}
		break;
	case PohybMapy::VLAVO:
		if (pohybDelta < 32) {
			pohybDelta++;
			posun(-1, 0);
		}
		else {
			smerPohybu = PohybMapy::STOJI;
			pohybDelta = 0;
		}
		break;
	case PohybMapy::HORE:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(0, -1);
		}
		else {
			smerPohybu = PohybMapy::STOJI;
			pohybDelta = 0;
		}
		break;
	case PohybMapy::DOLE:
		if (pohybDelta < 32) {
			pohybDelta++;
			posun(0, 1);
		}
		else {
			smerPohybu = PohybMapy::STOJI;
			pohybDelta = 0;
		}
		break;
	}
}


void Mapa::hracSkocilNaPolicko(int x, int y) const
{
	mapa[x][y]->hracSkok(hrac);
}

void Mapa::posunHracaNaPolicko(int x, int y, int smerPohladu) {


	int offsetHracaX = x * 32;
	int offsetHracaY = y * 32;
	int posunMapyX = 0;
	int posunMapyY = 0;

	hrac->setPolickoX(x);
	hrac->setPolickoY(y);
	
	if (offsetHracaX > 350) {
		posunMapyX = offsetHracaX - 6 * 32;
	}

	if (offsetHracaY > 350) {
		posunMapyY = offsetHracaY - 5 * 32;
	}

	if (static_cast<int>(posunMapyX) + static_cast<int>(hra->Getokno()->getSize().x) > sirka * 32) {
		posunMapyX = sirka * 32 - hra->Getokno()->getSize().x;
	}

	if (static_cast<int>(posunMapyY) + static_cast<int>(hra->Getokno()->getSize().y) > vyska * 32) {
		posunMapyY = vyska * 32 - hra->Getokno()->getSize().y;
	}



	hrac->setOffsetX(offsetHracaX);
	hrac->setOffsetY(offsetHracaY);
	posunX = posunMapyX;
	posunY = posunMapyY;

	switch (smerPohladu)
	{
	case SmerPohladu::dole :
		hrac->zmenSmerPohladu(SmerPohladu::dole);
		break;
	case SmerPohladu::vpravo:
		hrac->zmenSmerPohladu(SmerPohladu::vpravo);
		break;
	case SmerPohladu::hore:
		hrac->zmenSmerPohladu(SmerPohladu::hore);
		break;
	case SmerPohladu::vlavo:
		hrac->zmenSmerPohladu(SmerPohladu::vlavo);
		break;
	}

}

void Mapa::posunVpravo() {
	pohybDelta = 0;
	smerPohybu = PohybMapy::VPRAVO;
}

void Mapa::posunVlavo() {
	pohybDelta = 0;
	smerPohybu = PohybMapy::VLAVO;
}

void Mapa::posunHore() {
	pohybDelta = 0;
	smerPohybu = PohybMapy::HORE;
}

void Mapa::posunDole() {
	pohybDelta = 0;
	smerPohybu = PohybMapy::DOLE;
}

PohybMapy Mapa::Getsmerpohybu() const
{
	return smerPohybu;
}

int Mapa::Getvyska() const
{
	return vyska;
}

int Mapa::Getsirka() const
{
	return sirka;
}

bool Mapa::jeMoznyPohyb(int x, int y) const
{
	if (x < 0 || x >= sirka || y < 0 || y >= vyska) {
		return false;
	}

	bool priechodne = true;

	if (mapa[x][y]->Getnpc() != nullptr) {
		priechodne = false;
	}

	if (!mapa[x][y]->jePrechodne()) {
		priechodne = false;
	}
	return priechodne;
}

void Mapa::setSirkaVyska(int paSirka, int paVyska) {
	this->sirka = paSirka;
	this->vyska = paVyska;
}

void Mapa::nastavPolicko(int paX, int paY, Policko* paPolicko) const
{
	mapa[paX][paY] = paPolicko;
}

Policko* Mapa::GetPolicko(int x, int y) const
{
	return mapa[x][y];
}

void Mapa::hracInterakcia(StavHranieHry* paStav, void(StavHranieHry::*callbackFunkcia)()) const
{
	if (hrac->GethybeSa() || smerPohybu != 0) return;

	int x = hrac->GetpolickoX();
	int y = hrac->GetpolickoY();

	if (mapa[x][y]->polozenyPredmet()) {
		(paStav->*callbackFunkcia)();// volanie metody paStav
		return;
	}

	if (hrac->GetSmerPohladu() == SmerPohladu::hore) {
		y--;
	}
	if (hrac->GetSmerPohladu() == SmerPohladu::dole) {
		y++;
	}

	if (hrac->GetSmerPohladu() == SmerPohladu::vpravo) {
		x++;
	}

	if (hrac->GetSmerPohladu() == SmerPohladu::vlavo) {
		x--;
	}

	if (x < 0 || x >= sirka || y < 0 || y >= vyska) {
		return;
	}

	if (mapa[x][y]->Getnpc() != nullptr) {
		mapa[x][y]->Getnpc()->dialog(hrac);
	}
	else {
		mapa[x][y]->interakcia(hrac);
	}


}

sf::Time Mapa::aktCas() const
{
	return casovac.getElapsedTime();
}

vector<string>* Mapa::Getmoznynepriatelia() {
	moznyNepriatelia->clear();
	sf::Vector2i pos(hrac->GetpolickoX(), hrac->GetpolickoY());
	for (auto oblast : oblasti) {
		if (oblast->obsahujeSuradnicu(pos)) {
			for (auto s : oblast->Getnepriatelia()) {
				if (find(moznyNepriatelia->begin(), moznyNepriatelia->end(), s) == moznyNepriatelia->end())
				{
					moznyNepriatelia->push_back(s);
				}
			}
		}
	}

	return moznyNepriatelia;
}

void Mapa::pridajNepriatela(Oblast paOblast, string paMeno) {
	Oblast* oblast = nullptr;
	for (auto o : oblasti) {
		if (o->jeRovnaka(paOblast)) oblast = o;
	}

	if (oblast == nullptr) {
		Oblast* n = new Oblast(paOblast.x, paOblast.y, paOblast.w, paOblast.h);
		oblasti.push_back(n);
		oblast = n;
	}
	oblast->pridajNepriatela(paMeno);
}

void Mapa::toogleMinimapa() {
	minimapa = !minimapa;
}