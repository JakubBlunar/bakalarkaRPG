#include "StavHranieHry.h"
#include "Hra.h"
#include "Hrac.h"
#include "Mapa.h"
#include "Loader.h"
#include "PopupOkno.h"

#define RAMCEK 96

StavHranieHry::StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra, Mapa* mapa) : Stav(paNazov, paOkno, paHra)
{
	this->mapa = mapa;
	font = Loader::Instance()->nacitajFont("font2.otf");
	/*
	PopupOkno* popup = new PopupOkno("Vitaj v mojej hre asdasdasd... \n\n asdadasd\n\n\n\n\n\n\n dalsi");
	popup->pridajStranku("Toto je dalsia stranka");
	popup->pridajStranku("Tretia");
	Stav::zobrazPopup(popup);*/
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
	Stav::render();
}

void StavHranieHry::Setmapa(Mapa* newVal) {
	mapa = newVal;
}

void StavHranieHry::update(double delta) {

	if (hra->maFocus()) {
		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
					hrac->zmenSmerPohladu(SmerPohladu::vlavo);
					if (mapa->jeMoznyPohyb(hrac->GetpolickoX() - 1, hrac->GetpolickoY())) {
						hrac->chodVlavo();
						if (hrac->GetoffsetX() - mapa->Getzobrazenaoblast().left - RAMCEK < 0) {
							mapa->posunVlavo();
						}
					}
				}


			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
					hrac->zmenSmerPohladu(SmerPohladu::vpravo);
					if (mapa->jeMoznyPohyb(hrac->GetpolickoX() + 1, hrac->GetpolickoY())) {
						hrac->chodVpravo();
						if (hrac->GetoffsetX() - mapa->Getzobrazenaoblast().left >= okno->getSize().x-RAMCEK) { 
							mapa->posunVpravo(); 
						}
					}
				}

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
					hrac->zmenSmerPohladu(SmerPohladu::hore);
					if (mapa->jeMoznyPohyb(hrac->GetpolickoX(), hrac->GetpolickoY() - 1)) {
						hrac->chodHore();
						if (hrac->GetoffsetY() - mapa->Getzobrazenaoblast().top - RAMCEK < 0) mapa->posunHore();
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == 0) {
					hrac->zmenSmerPohladu(SmerPohladu::dole);
					if (mapa->jeMoznyPohyb(hrac->GetpolickoX(), hrac->GetpolickoY() + 1)) {
						hrac->chodDole();
						if (hrac->GetoffsetY() - mapa->Getzobrazenaoblast().top >= okno->getSize().y-RAMCEK) { mapa->posunDole(); };
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
	}

	mapa->update(delta);
	hra->GetHrac()->update(delta);

}

Mapa* StavHranieHry::getMapa() {
	return mapa;
}
