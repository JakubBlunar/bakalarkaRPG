#include "StavPauza.h"
#include "Loader.h"
#include "Hra.h"
#include "Tlacidlo.h"
#include "PopupOkno.h"
#include "AudioManager.h"

StavPauza::StavPauza(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	
	sf::Texture texture;
	texture.create(200, 100);

	sf::Sprite* normalne = new sf::Sprite();
	normalne->setTexture(texture);
	normalne->setTextureRect(sf::IntRect(0, 0, 48, 48));
	normalne->setColor(sf::Color(0, 0, 0, 255));

	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Resume game", sf::Vector2f(0, 150), sf::Vector2f(500, 0), font, 85));
	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Save game", sf::Vector2f(0, 260), sf::Vector2f(500, 0), font, 85));
	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Exit", sf::Vector2f(0, 350), sf::Vector2f(500, 0), font, 85));

	for (unsigned int i = 0; i < tlacidla.size(); i++) {
		Tlacidlo* t = tlacidla.at(i);
		t->setSize(sf::Vector2f(t->Gettext().getGlobalBounds().width, t->Gettext().getGlobalBounds().height));
		t->Setpozicia(sf::Vector2f(paOkno->getSize().x / 2 - t->getSize().x / 2, t->Gettext().getPosition().y));
	}

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
	hra->Getstav("hranieHry")->render();
	
	for (unsigned int i = 0; i < tlacidla.size(); i++)
	{
		sf::RectangleShape r = tlacidla.at(i)->Getramcek();
		r.setOutlineColor(sf::Color::Black);
		r.setOutlineThickness(5.f);
		r.setSize(sf::Vector2f(r.getSize().x + 10.f, r.getSize().y + 10.f));
		r.setPosition(r.getPosition().x - 5.f, r.getPosition().y - 5.f);
		okno->draw(r);
		sf::Text text = tlacidla.at(i)->Gettext();
		text.setPosition(text.getPosition().x, text.getPosition().y - text.getCharacterSize() / 2 + 3);
		if (oznacene == i) {
			text.setColor(sf::Color::Red);
		}
		else {
			text.setColor(sf::Color::Black);
		}
		okno->draw(text);
	}

	Stav::render();
}


void StavPauza::update() {
	if (hra->maFocus()) {

		Stav::update();

		if (stav == StavAkcia::NORMAL) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
			{
				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
				for (unsigned int i = 0; i < tlacidla.size(); i++)
				{
					tlacidla[i]->skontrolujKlik(pozicia);
					if (tlacidla[i]->Getzakliknute()) {
						stlacenaMys = true;
						AudioManager::Instance()->playEfekt("vyber");
						tlacidla[i]->Setzakliknute(false);
						if (i == 0) {
							hra->zmenStavRozhrania("hranieHry");
						}

						if (i == 1) {
							if (Loader::Instance()->save()) {
								zobrazPopup(new PopupOkno("Game has been saved!"));
								AudioManager::Instance()->playEfekt("beep");
							}
							else {
								zobrazPopup(new PopupOkno("Error! Game has not been saved!"));
								AudioManager::Instance()->playEfekt("beep");
							}
						}

						if (i == 2) {
							okno->close();
						}

					}
				}
			}

			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				stlacenaMys = false;
			}

			sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
			for (unsigned int i = 0; i < tlacidla.size(); i++)
			{
				if(tlacidla[i]->hover(pozicia))
				{
					oznacene = i;
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				AudioManager::Instance()->playEfekt("klik");
				if (oznacene > 0) {
					oznacene--;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				AudioManager::Instance()->playEfekt("klik");
				if (oznacene < (signed int)tlacidla.size() - 1) {
					oznacene++;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				AudioManager::Instance()->playEfekt("vyber");
				if (oznacene == 0) {
					hra->zmenStavRozhrania("hranieHry");
				}else if(oznacene == 1)
				{
					if (Loader::Instance()->save()) {
						zobrazPopup(new PopupOkno("Game has been saved!"));
						AudioManager::Instance()->playEfekt("beep");
					}
					else {
						zobrazPopup(new PopupOkno("Error! Game has not been saved!"));
						AudioManager::Instance()->playEfekt("beep");
					}
				}else
				{
					okno->close();
				}
			}



			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				stlacenaKlavesa = false;
			}
		}
	}
}