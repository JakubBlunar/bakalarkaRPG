#include "StavHlavneMenu.h"
#include "Loader.h"
#include "Hra.h"
#include "Tlacidlo.h"

StavHlavneMenu::StavHlavneMenu(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra): Stav(paNazov,paOkno,paHra){
	
	font = Loader::Instance()->nacitajFont("font2.otf");

	sf::Texture texture;
	texture.create(1000, 1000);

	sf::Sprite* normalne = new sf::Sprite();
	normalne->setTexture(texture);
	normalne->setTextureRect(sf::IntRect(0, 0, 48, 48));
	normalne->setColor(sf::Color(0, 0, 0, 255));

	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Nova hra", sf::Vector2f(10, 10), sf::Vector2f(500, 80), font, 75));
	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Nacitaj", sf::Vector2f(10, 100), sf::Vector2f(500, 80), font,75));
	tlacidla.push_back(new Tlacidlo(normalne, normalne, "Koniec", sf::Vector2f(10, 190), sf::Vector2f(500, 80), font, 75));
	
	stlacenaMys = true;
	oznacene = 0;

}


StavHlavneMenu::~StavHlavneMenu() {
	for each (Tlacidlo* tlacidlo in tlacidla)
	{
		delete tlacidlo;
	}
}



void StavHlavneMenu::onEnter() {
	Stav::onEnter();
	stlacenaMys = true;
}


void StavHlavneMenu::onExit() {
	Stav::onExit();
}


void StavHlavneMenu::render() {


	for (unsigned int i = 0; i < tlacidla.size(); i++)
	{
		
		okno->draw(*tlacidla.at(i)->Getsprite());
		sf::Text text = tlacidla.at(i)->Gettext();

		if(oznacene == i){
			text.setColor(sf::Color::Blue);
		}
		else {
			text.setColor(sf::Color::White);
		}
		okno->draw(text);
	}
	
	Stav::render();
	//std::cout << oznacene << std::endl;
}


void StavHlavneMenu::update(double delta) {
	
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
							hra->zmenStavRozhrania("volbaZamerania");
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
				hra->zmenStavRozhrania("volbaZamerania");
			}

			if (oznacene == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				okno->close();
			}


			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				stlacenaKlavesa = false;
			}
		}
	}

}