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
#include "QuestManager.h"

#include "Loader.h"
#include "Stav.h"
#include "Hra.h"
#include "PopupOkno.h"
#include "Akcia.h"


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
	
	std::map<std::string, int> bonusy = zameranie->lvlUpBonusy(statistika->dajUroven());
	for (std::map<std::string, int>::iterator it = bonusy.begin(); it != bonusy.end(); ++it){
		statistika->zvysStat(it->second - statistika->Getstat(it->first), it->first);
		statistika->Sethp(statistika->GethpMax());
		statistika->Setmp(statistika->GetmpMax());
	}

	for (std::map<Akcia*, int>::iterator it = zameranie->Getspelly()->begin(); it != zameranie->Getspelly()->end(); ++it){
		if (statistika->dajUroven() == it->second) {
			statistika->vlozAkciu(it->first);
		}
	}

	manazerQuestov = new QuestManager();

}

Hrac::~Hrac() {
	delete statistika;
	delete zameranie;
	delete manazerQuestov;
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

void Hrac::pridajSkusenosti(int pocet, bool oznamenie) {
	
	int ostatok = pocet;

	int lvlPred = statistika->dajUroven();
	unsigned int pocetAkciiPred = statistika->Getakcie()->size();

	while (ostatok > 0)
	{
		int xpnalevel = zameranie->xpNaLevel(statistika->dajUroven() + 1);

		int skusenosti = statistika->Getskusenosti();
		
		if (skusenosti + ostatok > xpnalevel) {
			statistika->pridajXp(xpnalevel - skusenosti);
			ostatok -= (xpnalevel - skusenosti);
		}
		else {
			statistika->pridajXp(ostatok);
			ostatok = 0;
		}

		if (skusenosti >= xpnalevel) {
			statistika->setUroven(statistika->dajUroven() + 1);
			std::map<std::string, int> bonusy = zameranie->lvlUpBonusy(statistika->dajUroven());
			for (std::map<std::string, int>::iterator it = bonusy.begin(); it != bonusy.end(); ++it)
			{
				statistika->zvysStat(it->second - statistika->Getstat(it->first), it->first);
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
	
	if (lvlPred < statistika->dajUroven()) {
		std::map<std::string, int> bonusy = zameranie->lvlUpBonusy(lvlPred);

		std::string text = "Congratulation! You have advanced to new level " + std::to_string(statistika->dajUroven()) + "\n";
		text += "Max Hp = " + std::to_string(statistika->GethpMax()) + " ( +" + std::to_string(statistika->GethpMax() - bonusy.at("hpMax")) + " )\n";
		text += "Max mana = " + std::to_string(statistika->GetmpMax()) + " ( +" + std::to_string(statistika->GetmpMax() - bonusy.at("mpMax")) + " )\n";
		text += "Strenght = " + std::to_string(statistika->Getsila()) + " ( +" + std::to_string(statistika->Getsila() - bonusy.at("sila")) + " )\n";
		text += "Intellect = " + std::to_string(statistika->Getintelekt()) + " ( +" + std::to_string(statistika->Getintelekt() - bonusy.at("intel")) + " )\n";
		text += "Speed = " + std::to_string(statistika->Getrychlost()) + " ( +" + std::to_string(statistika->Getrychlost() - bonusy.at("rychlost")) + " )\n";
		text += "Your health and mana has been restored!";

		PopupOkno* pop = new PopupOkno(text);

		if (statistika->Getakcie()->size() > pocetAkciiPred) {
			pop->pridajStranku("You have got a new spell! \n");
			for (std::map<Akcia*, int>::iterator it = zameranie->Getspelly()->begin(); it != zameranie->Getspelly()->end(); ++it)
			{
				if (lvlPred < it->second && it->second <= statistika->dajUroven()) {
					std::string info = it->first->Getmeno() +"\n\n" + it->first->dajPopis();
					pop->pridajStranku(info);
					statistika->vlozAkciu(it->first);
				}
			}
		}
		if (oznamenie) {
			Loader::Instance()->Gethra()->dajStav("hranieHry")->zobrazPopup(pop);
		}
		else {
			delete pop;
		}
	}
	
	
}

Mapa* Hrac::getMapa() {
	return mapa;
}

SmerPohladu Hrac::GetSmerPohladu() {
	return smerPohladu;
}

void Hrac::vyhodPredmet(Predmet* paPredmet) {
	Policko* policko = mapa->GetPolicko(polickoX, polickoY);
	inventar->zmazPredmet(paPredmet);
	policko->polozPredmet(paPredmet,mapa->aktCas());
}

QuestManager* Hrac::Getmanazerquestov() {
	return manazerQuestov;
}