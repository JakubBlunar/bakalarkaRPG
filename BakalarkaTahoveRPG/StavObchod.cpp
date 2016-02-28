#include "StavObchod.h"

#include "Loader.h"
#include "Hrac.h"
#include "Inventar.h"
#include "Hra.h"
#include "PopupOkno.h"

#include "Elixir.h"
#include "Zbran.h"
#include "Oblecenie.h"

StavObchod::StavObchod(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra):StavInventar(paNazov,paOkno,paHra)
{
	nasirku = 18;
	dostupnePredmety = new std::vector<Predmet*>();
}


StavObchod::~StavObchod()
{
	delete dostupnePredmety;
}

void StavObchod::nacitajObchod(std::string aky){
	delete dostupnePredmety;
	dostupnePredmety = Loader::Instance()->nacitajObchod(aky);

}






void StavObchod::onEnter() {
	StavInventar::onEnter();
	
}


void StavObchod::onExit() {
	StavInventar::onExit();
}


void StavObchod::render() {
	sf::Text text("", *font, 45U);
	if (typObchodu == KUPA) {
		int startX = 20;
		int startY = 70;


		text.setString("Kupa");
		text.setPosition(sf::Vector2f(10.f, 10.f));
		okno->draw(text);

		text.setString("Pocet Zlata:  " + std::to_string(inventar->Getzlato()));
		text.setPosition(500, 30);
		text.setColor(sf::Color::Yellow);
		text.setCharacterSize(20);
		okno->draw(text);

		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(48, 48));


		sf::Sprite* predmetObrazok;
		for (unsigned int i = 0; i < dostupnePredmety->size(); i++) {

			rectangle.setPosition((float)startX + (i%nasirku) * 55, (float)startY + (i / nasirku) * 55);
			okno->draw(rectangle);
			
			predmetObrazok = dostupnePredmety->at(i)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(sf::Vector2f((float)startX + (i%nasirku) * 55, (float)startY + (i / nasirku) * 55));
			
			okno->draw(*predmetObrazok);
			


			if (i == oznacene) {
				ukazovatel.setPosition(sf::Vector2f((float)startX + (i%nasirku) * 55, (float)startY + (i / nasirku) * 55));
				okno->draw(ukazovatel);

			}
		}

		if (oznacene >= 0 && (signed int)oznacene < (signed int)dostupnePredmety->size()) {
			vykresliOknoPredmetu(dostupnePredmety->at(oznacene), startX + (oznacene%nasirku) * 55 + 48, startY + (oznacene / nasirku) * 55 + 48, okno,false);
		}


		
	}
	else {
		
		StavInventar::render();
		sf::RectangleShape obdlznik;
		obdlznik.setFillColor(sf::Color::Black);
		obdlznik.setSize(sf::Vector2f(300,65));
		obdlznik.setPosition(0, 0);
		okno->draw(obdlznik);

		obdlznik.setSize(sf::Vector2f(500, 200));
		obdlznik.setPosition(0.f, okno->getSize().y - 200.f);
		okno->draw(obdlznik);

		sf::Text text("Predaj", *font, 45U);
		text.setPosition(sf::Vector2f(10.f, 10.f));
		okno->draw(text);



	}

	text.setString("Tab - kupa/predaj\nEnter/E - kup/predaj predmet");
	text.setPosition(20.f, okno->getSize().y - 55.f);
	text.setColor(sf::Color::Yellow);
	text.setCharacterSize(20);
	okno->draw(text);

	Stav::render();
}


void StavObchod::update(double delta) {
	if (hra->maFocus()) {
		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				stlacenaKlavesa = true;
				oznacene = 0;
				if (typObchodu == KUPA) {
					typObchodu = PREDAJ;
				}
				else typObchodu = KUPA;
				
			}

			if (typObchodu == KUPA) { // kupovanie


				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					stlacenaKlavesa = true;

					if (oznacene + nasirku <(signed int)dostupnePredmety->size()) {
						oznacene += nasirku;
					}
					else {
						oznacene = dostupnePredmety->size() - 1;
					}
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					stlacenaKlavesa = true;
					if (oznacene >= nasirku) {
						oznacene -= nasirku;
					}
					else {
						oznacene = 0;
					}
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					stlacenaKlavesa = true;
					if (oznacene > 0) {
						oznacene--;
					}
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					stlacenaKlavesa = true;
					if (oznacene < (signed int)dostupnePredmety->size() - 1) {
						oznacene++;
					}
				}


				if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
					stlacenaKlavesa = true;
					Predmet* p = dostupnePredmety->at(oznacene);
					
					if (inventar->Getzlato() >= p->Getcena()) {

						Predmet* kopia;
						if (dynamic_cast<Elixir*>(p) != NULL) {
							Elixir* elixir = (Elixir*)p;
							kopia = elixir->copy();
						}

						if (dynamic_cast<Zbran*>(p) != NULL) {
							Zbran* zbran = (Zbran*)p;
							kopia = zbran->copy();
						}

						if (dynamic_cast<Oblecenie*>(p) != NULL) {
							Oblecenie* oblecenie = (Oblecenie*)p;
							kopia = oblecenie->copy();
						}

						inventar->Setzlato(inventar->Getzlato() - kopia->Getcena());
						inventar->pridajPredmet(kopia);
						zobrazPopup(new PopupOkno("Predmet " + kopia->Getmeno() + " bol uspesne kupeny!"));
					}
					else {
						zobrazPopup(new PopupOkno("Nemas dostatok zlata!"));
					}
				}


			

				if (stlacenaKlavesa && !sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::E)
					) {
					stlacenaKlavesa = false;
				}

			}
			else { // predaj veci
				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					stlacenaKlavesa = true;

					if (oznacene + nasirku < inventar->pocetPredmetov()) {
						oznacene += nasirku;
					}
					else {
						oznacene = inventar->pocetPredmetov() - 1;
					}
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					stlacenaKlavesa = true;
					if (oznacene >= nasirku) {
						oznacene -= nasirku;
					}
					else {
						oznacene = 0;
					}
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					stlacenaKlavesa = true;
					if (oznacene > 0) {
						oznacene--;
					}
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					stlacenaKlavesa = true;
					if (oznacene < inventar->pocetPredmetov() - 1) {
						oznacene++;
					}
				}


				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					stlacenaKlavesa = true;
					if (oznacene >= 0 && oznacene < inventar->pocetPredmetov()) {
						Predmet* p = inventar->dajPredmetNaIndexe(oznacene);
						inventar->zmazPredmet(p);
						inventar->pridajZlato((int)round(p->Getcena()/2));
						std::string info = "Predmet " + p->Getmeno() + " bol predany!";
						//delete p;
						zobrazPopup(new PopupOkno(info));

					}
				}


				if (stlacenaKlavesa && !sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
					) {
					stlacenaKlavesa = false;
				}
			}
			
			if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {
				hra->zmenStavRozhrania("stavDialog");
			}
			
		}
	}
}
