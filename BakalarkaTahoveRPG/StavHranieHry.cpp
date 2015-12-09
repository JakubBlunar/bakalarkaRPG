#include "StavHranieHry.h"
#include "Hra.h"
#include "Hrac.h"
#include "Mapa.h"

#define RAMCEK 96

StavHranieHry::StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra)
{
	mapa = new Mapa(hra->GetHrac());
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
	mapa->render(okno);
}

/*
void StavHranieHry::Setmapa(Mapa newVal) {

	mapa = newVal;
}
*/


void StavHranieHry::update(double delta) {

	
	Hrac* hrac = hra->GetHrac();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		
		if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
			hrac->zmenSmerPohladu(SmerPohladu::vlavo);
			if (hrac->GetpolickoX() > 0) {
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
			if (hrac->GetpolickoX() < mapa->Getsirka()-1) {
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
			if (hrac->GetpolickoY() > 0) {
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
			if (hrac->GetpolickoY() < mapa->Getvyska()-1) {
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