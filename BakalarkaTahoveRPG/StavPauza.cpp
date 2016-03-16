#include "StavPauza.h"
#include "Loader.h"
#include "Hra.h"
#include "Tlacidlo.h"
#include "PopupOkno.h"

StavPauza::StavPauza(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	
	sf::Texture texture;
	texture.create(1000, 1000);

	sf::Sprite* normalne = new sf::Sprite();
	normalne->setTexture(texture);
	normalne->setTextureRect(sf::IntRect(0, 0, 48, 48));
	normalne->setColor(sf::Color(0, 0, 0, 255));

	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Resume game", sf::Vector2f(10, 10), sf::Vector2f(500, 80), font, 75));
	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Save game", sf::Vector2f(10, 100), sf::Vector2f(500, 80), font, 75));
	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Exit game", sf::Vector2f(10, 190), sf::Vector2f(500, 80), font, 75));

	stlacenaMys = true;
	stlacenaKlavesa = true;

	oznacene = 0;

}



StavPauza::~StavPauza() {
	for each (Tlacidlo* tlacidlo in tlacidla)
	{
		delete tlacidlo;
	}
}



void StavPauza::onEnter() {
	Stav::onEnter();
	stlacenaMys = true;
	stlacenaKlavesa = true;
}


void StavPauza::onExit() {
	Stav::onExit();
}


void StavPauza::render() {
	for (unsigned int i = 0; i < tlacidla.size(); i++)
	{

		okno->draw(*tlacidla.at(i)->Getsprite());
		sf::Text text = tlacidla.at(i)->Gettext();

		if (oznacene == i) {
			text.setColor(sf::Color::Blue);
		}
		else {
			text.setColor(sf::Color::White);
		}
		okno->draw(text);
	}

	Stav::render();
}


void StavPauza::update(double delta) {
	if (hra->maFocus()) {

		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
			{
				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
				for (unsigned int i = 0; i < tlacidla.size(); i++)
				{
					tlacidla[i]->skontrolujKlik(pozicia);
					if (tlacidla[i]->Getzakliknute()) {
						stlacenaMys = true;
						
						tlacidla[i]->Setzakliknute(false);
						if (i == 0) {
							hra->zmenStavRozhrania("hranieHry");
						}

						if (i == 1) {
							if (Loader::Instance()->save()) {
								Loader::Instance()->Gethra()->dajStav("stavPauza")->zobrazPopup(new PopupOkno("Game has been saved!"));
							}
							else {
								Loader::Instance()->Gethra()->dajStav("stavPauza")->zobrazPopup(new PopupOkno("Error! Game has not been saved!"));
							}
						}

						if (i == 2) {
							okno->close();
						}

					}
				}
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == true) {
				stlacenaMys = false;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				if (oznacene > 0) {
					oznacene--;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				if (oznacene < (signed int)tlacidla.size() - 1) {
					oznacene++;
				}
			}

			if (oznacene == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				hra->zmenStavRozhrania("hranieHry");
			}

			if (oznacene == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				if (Loader::Instance()->save()) {
					Loader::Instance()->Gethra()->dajStav("stavPauza")->zobrazPopup(new PopupOkno("Game has been saved!"));
				}
				else {
					Loader::Instance()->Gethra()->dajStav("stavPauza")->zobrazPopup(new PopupOkno("Error! Game has not been saved!"));
				}
			}


			if (oznacene == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				okno->close();
			}


			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				stlacenaKlavesa = false;
			}
		}
	}
}