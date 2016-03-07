#include "StavHranieHry.h"
#include "Hra.h"
#include "Hrac.h"
#include "Mapa.h"
#include "Loader.h"
#include "PopupOkno.h"
#include "Inventar.h"
#include "Policko.h"

#define RAMCEK 96

StavHranieHry::StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra, Mapa* mapa) : Stav(paNazov, paOkno, paHra)
{
	this->mapa = mapa;
	font = Loader::Instance()->nacitajFont("font2.otf");
	loot = nullptr;
	
	
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
	loot = nullptr;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::C) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::I)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		stlacenaKlavesa = true;
	}
}


void StavHranieHry::onExit() {
	Stav::onExit();
}


void StavHranieHry::render() {
	mapa->render(okno);
	
	if (loot == nullptr && !GetzobrazujePopup()) {
		lootIndex = 0;
		stav = StavAkcia::NORMAL;
	}

	if (stav == StavAkcia::ZOBRAZUJE_LOOT) {
		sf::RectangleShape rect;
		
		int oknoLootX, oknoLootY;
		oknoLootX = 50;
		oknoLootY = 50;

		rect.setSize(sf::Vector2f(48+12, 48*4+24+6));
		rect.setFillColor(sf::Color::White);
		rect.setPosition(sf::Vector2f(oknoLootX+0.f,oknoLootY + 0.f));
		okno->draw(rect);

		int pocet = loot->size();
		if (pocet > 4) {
			pocet = 4;
		}


		for (int i = 0; i < pocet; i++) {
			unsigned int index = lootIndex + i;
			
			if (index >= loot->size()) {
				index -= loot->size();
			}

			sf::Text meno("",*font,20);
			meno.setString(loot->at(index)->Getmeno());
			meno.setColor(sf::Color::Black);
			rect.setSize(sf::Vector2f(meno.getLocalBounds().width + 10, 28));
			
			
			sf::Sprite* sprite = loot->at(index)->Getobrazok();
			sprite->setScale(1.5, 1.5);
			sprite->setPosition(oknoLootX + 6.f, oknoLootY + 6 + i*sprite->getGlobalBounds().height+ i*6.f);
			rect.setPosition(oknoLootX + 6 + 48.f, oknoLootY + 6 + i*sprite->getGlobalBounds().height + i * 6.f);
			meno.setPosition(oknoLootX + 6+3.f + 48, 3+oknoLootY + 6 + i*sprite->getGlobalBounds().height + i * 6.f);
			okno->draw(*sprite);
			okno->draw(rect);
			okno->draw(meno);

		}
			
		rect.setSize(sf::Vector2f(48, 48));
		rect.setFillColor(sf::Color(255, 0, 0, 128));
		rect.setPosition(oknoLootX + 6.f, oknoLootY + 6.f);
		okno->draw(rect);
	}


	Stav::render();
}

void StavHranieHry::Setmapa(Mapa* newVal) {
	mapa = newVal;
}

void StavHranieHry::update(double delta) {

	if (hra->maFocus()) {
		Stav::update(delta);

		if (stav == StavAkcia::ZOBRAZUJE_LOOT) {
			
			if (loot == nullptr) {
				lootIndex = 0;
				stav = StavAkcia::NORMAL;
			}


			if (stlacenaKlavesa && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				stlacenaKlavesa = false;
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				stlacenaKlavesa = true;
				loot = nullptr;
				lootIndex = 0;
				stav = StavAkcia::NORMAL;
			}

			if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
				stlacenaKlavesa = true;
				Predmet* predmet = loot->at(lootIndex);
				hrac->Getinventar()->pridajPredmet(predmet);
				loot->erase(loot->begin() + lootIndex);
				if ((unsigned int)lootIndex >= loot->size()) {
					lootIndex = 0;
				}
				
				if (loot->size() == 0) {
					loot = nullptr;
					lootIndex = 0;
					stav = StavAkcia::NORMAL;
				}
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				stlacenaKlavesa = true;
				
				if (lootIndex == 0) {
					lootIndex = loot->size()-1;
				}
				else {
					lootIndex--;
				}
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				stlacenaKlavesa = true;
				if ((unsigned int)lootIndex >= loot->size()-1) {
					lootIndex = 0;
				}
				else {
					lootIndex++;
				}
				
			}
		}



		if (stav == StavAkcia::NORMAL) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == PohybMapy::STOJI) {
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

				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == PohybMapy::STOJI) {
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
				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == PohybMapy::STOJI) {
					hrac->zmenSmerPohladu(SmerPohladu::hore);
					if (mapa->jeMoznyPohyb(hrac->GetpolickoX(), hrac->GetpolickoY() - 1)) {
						hrac->chodHore();
						if (hrac->GetoffsetY() - mapa->Getzobrazenaoblast().top - RAMCEK < 0) mapa->posunHore();
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				if (!hrac->GethybeSa() && mapa->Getsmerpohybu() == PohybMapy::STOJI) {
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && !stlacenaKlavesa) {
				hra->zmenStavRozhrania("stavPrehladQuestov");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !stlacenaKlavesa) {
				hra->zmenStavRozhrania("stavInfoHraca");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && !stlacenaKlavesa) {
				hra->zmenStavRozhrania("stavInventar");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !stlacenaKlavesa) { // cheat :D
				stlacenaKlavesa = true;
				hrac->pridajSkusenosti(10);
				hrac->Getinventar()->pridajZlato(1000);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				void(StavHranieHry::*callbackFunkcia)();
				callbackFunkcia = &StavHranieHry::zobrazLoot;
				mapa->hracInterakcia(this, callbackFunkcia);

			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::C)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::X)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::I)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::E)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
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

void StavHranieHry::zobrazLoot() {
	stav = StavAkcia::ZOBRAZUJE_LOOT;
	lootIndex = 0;
	loot = mapa->GetPolicko(hrac->GetpolickoX(), hrac->GetpolickoY())->dajPolozenePredmety();
}