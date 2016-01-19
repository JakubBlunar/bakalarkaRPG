#include "StavPauza.h"
#include "Loader.h"
#include "Hra.h"

StavPauza::StavPauza(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	moznosti.push_back("Pokracovat");
	moznosti.push_back("Ulozit");
	moznosti.push_back("Koniec");

	oznacene = 0;

	font = Loader::Instance()->nacitajFont("font2.otf");

}



StavPauza::~StavPauza() {
	moznosti.clear();
}





void StavPauza::onEnter() {
	Stav::onEnter();
}


void StavPauza::onExit() {
	Stav::onExit();
}


void StavPauza::render() {
	for (unsigned int i = 0; i < moznosti.size(); i++)
	{
		sf::Text text(moznosti.at(i), *font, 75U);

		if (oznacene == i) {
			text.setColor(sf::Color::Blue);
		}
		else {
			text.setColor(sf::Color::White);
		}
		text.setPosition(sf::Vector2f(sf::Vector2f(100.f, 100 + 75.f*i)));

		okno->draw(text);
	}
}


void StavPauza::update(double delta) {
	if (hra->maFocus()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !stlacenaKlavesa) {
			stlacenaKlavesa = true;
			if (oznacene > 0) {
				oznacene--;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !stlacenaKlavesa) {
			stlacenaKlavesa = true;
			if (oznacene < (signed int)moznosti.size() - 1) {
				oznacene++;
			}
		}



		if (oznacene == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
			stlacenaKlavesa = true;
			hra->zmenStavRozhrania("hranieHry");
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