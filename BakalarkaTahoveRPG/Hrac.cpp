#include <iostream>
#include <map>

#include "Hrac.h"
#include "Zameranie.h"
#include "Animacia.h"
#include "Mapa.h"
#include "Statistika.h"
#include "Inventar.h"
#include "Akcia.h"
#include "Policko.h"

Hrac::Hrac(Zameranie* paZameranie) {
	zameranie = paZameranie;

	animaciaDole = new Animacia("Data/Grafika/Hrac/Animacia/warrior_dole.png", 4, 10, 32, 48);
	animaciaHore = new Animacia("Data/Grafika/Hrac/Animacia/warrior_hore.png", 4, 10, 32, 48);
	animaciaVlavo = new Animacia("Data/Grafika/Hrac/Animacia/warrior_vlavo.png", 4, 10, 32, 48);
	animaciaVpravo = new Animacia("Data/Grafika/Hrac/Animacia/warrior_vpravo.png", 4, 10, 32, 48);
	smerPohladu = SmerPohladu::dole;
	hybeSa = false;
	polickoX = 0;
	polickoY = 0;
	offsetX = 0;
	offsetY = 0;
	statistika = new Statistika();
	inventar = new Inventar();
	
	for (std::map<Akcia*, int>::iterator it = paZameranie->Getspelly()->begin(); it != paZameranie->Getspelly()->end(); ++it)
	{
		if (statistika->dajUroven() == it->second) {
			statistika->vlozAkciu(it->first);
		}
	}


}

Hrac::~Hrac() {
	delete statistika;
	delete zameranie;
	std::cout << "Hrac zmazany" << std::endl;
}


void Hrac::render(sf::RenderWindow* paOkno) {

	sf::Sprite* obrazok;
	if (smerPohladu == hore) {
		obrazok = animaciaHore->dajObrazok();
	}

	if (smerPohladu == dole) {
		obrazok = animaciaDole->dajObrazok();
	}

	if (smerPohladu == vlavo) {
		obrazok = animaciaVlavo->dajObrazok();
	}

	if (smerPohladu == vpravo) {
		obrazok = animaciaVpravo->dajObrazok();
	}

	obrazok->setPosition(sf::Vector2f(offsetX+0.f, 32 - animaciaDole->GetvelkostY() +offsetY+0.f));

	paOkno->draw(*obrazok);
}


void Hrac::update(double delta) {
		if (smerPohybu == vpravo && hybeSa) {
			if (pohybDelta < 32) {
				animaciaVpravo->tick();
				pohybDelta++;
				posun(1, 0);
			}else {
				hybeSa = false;
				smerPohybu = SmerPohladu::stoji;
				pohybDelta = 0;
				polickoX++;
				mapa->hracSkocilNaPolicko(polickoX, polickoY);
				
			}
		}

	if (smerPohladu == hore && hybeSa) {
		if (pohybDelta < 32) {
			animaciaHore->tick();
			pohybDelta++;
			posun(0, -1);
		}
		else {
			hybeSa = false;
			smerPohybu = SmerPohladu::stoji;
			pohybDelta = 0;
			polickoY--;
			mapa->hracSkocilNaPolicko(polickoX, polickoY);
		}
	}

	if (smerPohladu == dole && hybeSa) {
		if (pohybDelta < 32) {
			animaciaDole->tick();
			pohybDelta++;
			posun(0, 1);
		}
		else {
			hybeSa = false;
			smerPohybu = SmerPohladu::stoji;
			pohybDelta = 0;
			polickoY++;
			mapa->hracSkocilNaPolicko(polickoX, polickoY);
		}
	}

	if (smerPohladu == vlavo && hybeSa) {
		if (pohybDelta < 32) {
			animaciaVlavo->tick();
			pohybDelta++;
			posun(-1, 0);
		}
		else {
			hybeSa = false;
			smerPohybu = SmerPohladu::stoji;
			pohybDelta = 0;
			polickoX--;
			mapa->hracSkocilNaPolicko(polickoX, polickoY);
		}
	}


}

bool Hrac::GethybeSa() {
	return hybeSa;
}

void Hrac::chodVpravo() {
	pohybDelta = 0;
	smerPohybu = SmerPohladu::vpravo;
	hybeSa = true;
}

void Hrac::chodVlavo() {
	pohybDelta = 0;
	smerPohybu = SmerPohladu::vlavo;
	hybeSa = true;
}

void Hrac::chodHore() {
	pohybDelta = 0;
	smerPohybu = SmerPohladu::hore;
	hybeSa = true;
}

void Hrac::chodDole() {
	pohybDelta = 0;
	smerPohybu = SmerPohladu::dole;
	hybeSa = true;
}

void Hrac::posun(int x, int y) {
	offsetX += x;
	offsetY += y;
}


void Hrac::zmenSmerPohladu(SmerPohladu paSmer) {
	smerPohladu = paSmer;
	
	if (smerPohladu == hore) {
		animaciaHore->reset();
	}

	if (smerPohladu == dole) {
		animaciaDole->reset();
	}

	if (smerPohladu == vlavo) {
		animaciaVlavo->reset();
	}

	if (smerPohladu == vpravo) {
		animaciaVpravo->reset();
	}

}

void Hrac::animaciaTick() {
	animaciaDole->tick();
	animaciaHore->tick();
	animaciaVlavo->tick();
	animaciaVpravo->tick();
}


int Hrac::GetoffsetX() {
	return offsetX;
}

int Hrac::GetoffsetY() {
	return offsetY;
}

int Hrac::GetpolickoX() {
	return polickoX;
}

int Hrac::GetpolickoY() {
	return polickoY;
}

void Hrac::setPolickoX(int paX) {
	polickoX = paX;
}

void Hrac::setPolickoY(int paY) {
	polickoY = paY;
}

void Hrac::setOffsetX(int paX) {
	offsetX = paX;
}

void Hrac::setOffsetY(int paY) {
	offsetY = paY;
}

void Hrac::setMapa(Mapa* mapa) {
	this->mapa = mapa;
}

void Hrac::Setstatistika(Statistika* paStatistika) {
	statistika = paStatistika;
}

Statistika* Hrac::Getstatistika() {
	return statistika;
}

Zameranie* Hrac::GetZameranie() {
	return zameranie;
}

Inventar* Hrac::Getinventar() {
	return inventar;
}

void Hrac::pridajSkusenosti(int pocet) {
	statistika->pridajXp(pocet);
	int xpnalevel = zameranie->xpNaLevel(statistika->dajUroven() + 1);

	int skusenosti = statistika->Getskusenosti();
	std::map<std::string, int> bonusy = zameranie->lvlUpBonusy();
	if (skusenosti >= xpnalevel) {
		statistika->setUroven(statistika->dajUroven() + 1);
		for (std::map<std::string, int>::iterator it = bonusy.begin(); it != bonusy.end(); ++it)
		{
			statistika->zvysStat(it->second, it->first);
			statistika->Sethp(statistika->GethpMax());
			statistika->Setmp(statistika->GetmpMax());
		}
		
		for (std::map<Akcia*, int>::iterator it = zameranie->Getspelly()->begin(); it != zameranie->Getspelly()->end(); ++it)
		{
			if (statistika->dajUroven() == it->second) {
				statistika->vlozAkciu(it->first);
			}
		}

	}
	
}

SmerPohladu Hrac::GetSmerPohladu() {
	return smerPohladu;
}

void Hrac::vyhodPredmet(Predmet* paPredmet) {
	Policko* policko = mapa->GetPolicko(polickoX, polickoY);
	inventar->zmazPredmet(paPredmet);
	policko->polozPredmet(paPredmet,mapa->aktCas());
}