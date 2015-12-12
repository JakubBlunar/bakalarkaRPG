#include "StavHranieHry.h"
#include "Hra.h"
#include "Hrac.h"
#include "Mapa.h"


#define RAMCEK 96

StavHranieHry::StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra, Mapa* paMapa) : Stav(paNazov, paOkno, paHra)
{
	mapa = paMapa;
	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font.ttf");

}


StavHranieHry::~StavHranieHry()
{
}


void StavHranieHry::onEnter() {
	Stav::onEnter();
}


void StavHranieHry::onExit() {
	Stav::onExit();
}


void StavHranieHry::render() {
	

	if (mapa->GetNacitava()) {
		sf::Text text;

		// select the font
		text.setFont(*font);
		text.setString("Nacitavam");
		text.setCharacterSize(64);
		text.setPosition(sf::Vector2f(100, 100));
		okno->draw(text);
		return;
	}

	mapa->render(okno);
}

void StavHranieHry::Setmapa(Mapa* newVal) {
	delete mapa;
	mapa = newVal;
}



void StavHranieHry::update(double delta) {
	if (mapa->GetNacitava()) {
		return;
	}

	Hrac* hrac = hra->GetHrac();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		
		if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
			hrac->zmenSmerPohladu(SmerPohladu::vlavo);
			if (mapa->jeMoznyPohyb(hrac->GetpolickoX()-1,hrac->GetpolickoY()) ) {
				if (hrac->GetoffsetX() > RAMCEK) {
					hrac->chodVlavo();
				}
				else {
					mapa->posunVlavo();
				}
			}
		}
		
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		
		if (!hrac->GethybeSa() && mapa->Getsmerpohybu() ==0 ) {
			hrac->zmenSmerPohladu(SmerPohladu::vpravo);
			if (mapa->jeMoznyPohyb(hrac->GetpolickoX() +1, hrac->GetpolickoY())) {
				if ((signed int)hrac->GetoffsetX() < (signed int)okno->getSize().x - RAMCEK) {
					hrac->chodVpravo();
				}
				else {
					mapa->posunVpravo();
				}
			}
		}



	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {		
		if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
			hrac->zmenSmerPohladu(SmerPohladu::hore);
			if (mapa->jeMoznyPohyb(hrac->GetpolickoX(),hrac->GetpolickoY() - 1)) {
				if (hrac->GetoffsetY() > RAMCEK) {
					hrac->chodHore();
				}
				else {
					mapa->posunHore();
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
			hrac->zmenSmerPohladu(SmerPohladu::dole);
			if (mapa->jeMoznyPohyb(hrac->GetpolickoX(), hrac->GetpolickoY() +1)) {
				if ((signed int)hrac->GetoffsetY() < (signed int)okno->getSize().y-RAMCEK) {
					hrac->chodDole();
				}
				else {
					mapa->posunDole();
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		hra->zmenStavRozhrania("stavPauza");
	}

	

	/*
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		stlacenaKlavesa = false;
	}
	*/
	mapa->update(delta);
	hra->GetHrac()->update(delta);
	
}

Mapa* StavHranieHry::getMapa() {
	return mapa;
}
