#include "StavHranieHry.h"
#include "Hra.h"
#include "Hrac.h"
#include "Mapa.h"


#define RAMCEK 96

StavHranieHry::StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra, Mapa* mapa) : Stav(paNazov, paOkno, paHra)
{
	this->mapa = mapa;
}


StavHranieHry::~StavHranieHry()
{
}


void StavHranieHry::onEnter() {
	Stav::onEnter();
	hrac = hra->GetHrac();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::C) || sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		stlacenaKlavesa = true;
	}
}


void StavHranieHry::onExit() {
	Stav::onExit();
}


void StavHranieHry::render() {
	mapa->render(okno);
}

void StavHranieHry::Setmapa(Mapa* newVal) {
	mapa = newVal;
}



void StavHranieHry::update(double delta) {
	if (hra->maFocus()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
				hrac->zmenSmerPohladu(SmerPohladu::vlavo);
				if (mapa->jeMoznyPohyb(hrac->GetpolickoX() - 1, hrac->GetpolickoY())) {
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

			if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
				hrac->zmenSmerPohladu(SmerPohladu::vpravo);
				if (mapa->jeMoznyPohyb(hrac->GetpolickoX() + 1, hrac->GetpolickoY())) {
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
				if (mapa->jeMoznyPohyb(hrac->GetpolickoX(), hrac->GetpolickoY() - 1)) {
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
				if (mapa->jeMoznyPohyb(hrac->GetpolickoX(), hrac->GetpolickoY() + 1)) {
					if ((signed int)hrac->GetoffsetY() < (signed int)okno->getSize().y - RAMCEK) {
						hrac->chodDole();
					}
					else {
						mapa->posunDole();
					}
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !stlacenaKlavesa) {
			hra->zmenStavRozhrania("stavPauza");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !stlacenaKlavesa) {
			hra->zmenStavRozhrania("stavInfoHraca");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && !stlacenaKlavesa) {
			hra->zmenStavRozhrania("stavInventar");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !stlacenaKlavesa) {
			stlacenaKlavesa = true;
			hrac->pridajSkusenosti(10);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !stlacenaKlavesa) {
			stlacenaKlavesa = true;
			mapa->hracInterakcia();
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::C)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::X)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::I)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			stlacenaKlavesa = false;
		}
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
