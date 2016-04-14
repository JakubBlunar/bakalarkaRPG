#include "StavObchod.h"

#include "Loader.h"
#include "Inventar.h"
#include "Hra.h"
#include "PopupOkno.h"

#include "Elixir.h"
#include "Zbran.h"
#include "Oblecenie.h"
#include "AudioManager.h"
#include  "Tlacidlo.h"

StavObchod::StavObchod(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra):StavInventar(paNazov,paOkno,paHra)
{
	typObchodu = KUPA;
	nasirku = 12;
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

void StavObchod::predajPredmet()
{
	if (oznacene >= 0 && oznacene < inventar->pocetPredmetov()) {
		Predmet* p = inventar->dajPredmetNaIndexe(oznacene);
		inventar->zmazPredmet(p);
		inventar->pridajZlato(static_cast<int>(round(p->Getcena() / 2)));
		std::string info = "You sold " + p->Getmeno() + ".";
		delete p;
		zobrazPopup(new PopupOkno(info));
		AudioManager::Instance()->playEfekt("sell_buy");
	}
}

void StavObchod::kupPredmet()
{
	Predmet* p = dostupnePredmety->at(oznacene);

	if (inventar->Getzlato() >= p->Getcena()) {

		Predmet* kopia = nullptr;
		if (dynamic_cast<Elixir*>(p) != nullptr) {
			Elixir* elixir = static_cast<Elixir*>(p);
			kopia = elixir->copy();
		}

		if (dynamic_cast<Zbran*>(p) != nullptr) {
			Zbran* zbran = static_cast<Zbran*>(p);
			kopia = zbran->copy();
		}

		if (dynamic_cast<Oblecenie*>(p) != nullptr) {
			Oblecenie* oblecenie = static_cast<Oblecenie*>(p);
			kopia = oblecenie->copy();
		}

		if (kopia != nullptr) {
			if (inventar->Getkapacita() > inventar->pocetPredmetov()) {
				inventar->Setzlato(inventar->Getzlato() - kopia->Getcena());
				inventar->pridajPredmet(kopia);
				zobrazPopup(new PopupOkno("You bought " + kopia->Getmeno() + " !"));
				AudioManager::Instance()->playEfekt("sell_buy");
			}
			else {
				zobrazPopup(new PopupOkno("Inventory is full! You can't buy " + kopia->Getmeno() + "."));
				AudioManager::Instance()->playEfekt("beep");
			}
		}
	}
	else {
		zobrazPopup(new PopupOkno("You cant't afford that!"));
		AudioManager::Instance()->playEfekt("beep");
	}
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


		text.setString("Buy");
		text.setPosition(sf::Vector2f(10.f, 10.f));
		okno->draw(text);

		text.setString("Gold:  " + std::to_string(inventar->Getzlato()));
		text.setPosition(500, 30);
		text.setColor(sf::Color::Yellow);
		text.setCharacterSize(20);
		okno->draw(text);

		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(48, 48));


		sf::Sprite* predmetObrazok;
		for (unsigned int i = 0; i < dostupnePredmety->size(); i++) {

			rectangle.setPosition(startX + (i%nasirku) * 55.f, startY + (i / nasirku) * 55.f);
			okno->draw(rectangle);
			
			predmetObrazok = dostupnePredmety->at(i)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(sf::Vector2f(startX + (i%nasirku) * 55.f, startY + (i / nasirku) * 55.f));
			
			okno->draw(*predmetObrazok);
			


			if (i == oznacene) {
				ukazovatel.setPosition(sf::Vector2f(startX + (i%nasirku) * 55.f, startY + (i / nasirku) * 55.f));
				okno->draw(ukazovatel);

			}
		}

		if (oznacene >= 0 &&oznacene < static_cast<signed int>(dostupnePredmety->size())) {
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

		obdlznik.setPosition(okno->getSize().x - 100.f, 0.f);
		okno->draw(obdlznik);


		obdlznik.setSize(sf::Vector2f(500, 200));
		obdlznik.setPosition(0.f, okno->getSize().y - 200.f);
		okno->draw(obdlznik);

		sf::Text text2("Sell", *font, 45U);
		text2.setPosition(sf::Vector2f(10.f, 10.f));
		okno->draw(text2);



	}

	text.setString("Esc - Exit\nTab - change buying or selling\nEnter/E - buy/sell item");
	text.setPosition(20.f, okno->getSize().y - 75.f);
	text.setColor(sf::Color::Yellow);
	text.setCharacterSize(20);
	okno->draw(text);

	Stav::render();
}


void StavObchod::update() {
	if (hra->maFocus()) {
		Stav::update();

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


				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
				{
					sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);

					for (unsigned int i = 0; i < dostupnePredmety->size(); i++) {
						tlacidla.at(i)->skontrolujKlik(pozicia);
						if (tlacidla.at(i)->Getzakliknute())
						{
							oznacene = i;
							tlacidla.at(i)->Setzakliknute(false);
							kupPredmet();
						}

					}
					stlacenaMys = true;

				}

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					stlacenaMys = false;
				}

				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);

				for (unsigned int i = 0; i < dostupnePredmety->size(); i++)
				{
					if(tlacidla.at(i)->hover(pozicia))
					{
						oznacene = i;
					}
				}


				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					stlacenaKlavesa = true;

					if (oznacene + nasirku <static_cast<signed int>(dostupnePredmety->size())) {
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
					if (oznacene < static_cast<signed int>(dostupnePredmety->size()) - 1) {
						oznacene++;
					}
				}


				if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
					stlacenaKlavesa = true;
					kupPredmet();
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


				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
				{
					sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);

					for (unsigned int i = 0; i < tlacidla.size(); i++) {
						tlacidla.at(i)->skontrolujKlik(pozicia);
						if (tlacidla.at(i)->Getzakliknute())
						{
							oznacene = i;
							tlacidla.at(i)->Setzakliknute(false);
							predajPredmet();
						}

					}
					stlacenaMys = true;

				}

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					stlacenaMys = false;
				}

				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);

				for (unsigned int i = 0; i < tlacidla.size(); i++)
				{
					if (tlacidla.at(i)->hover(pozicia))
					{
						oznacene = i;
					}
				}

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
					predajPredmet();
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
