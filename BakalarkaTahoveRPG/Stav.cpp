
#include "Stav.h"
#include "Hra.h"
Stav::Stav(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) {
	nazov = paNazov;
	okno = paOkno;
	hra = paHra;
	stav = StavAkcia::NORMAL;

	stlacenaMys = true;
	stlacenaKlavesa = true;
}



Stav::~Stav() {
}



void Stav::update(double delta) {

	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {
		if (stlacenaKlavesa && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) stlacenaKlavesa = false;
		
		if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			stlacenaKlavesa = true;
			stav = StavAkcia::NORMAL;
		}
	}

}


void Stav::render() {

	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {

		sf::RectangleShape pozadie;
		sf::Text text(popupText, *font, 17U);
		

		pozadie.setSize(sf::Vector2f(okno->getSize().x-100.f, text.getGlobalBounds().height + 20.f));
		pozadie.setOutlineColor(sf::Color::Red);
		pozadie.setOutlineThickness(2);
		pozadie.setPosition(sf::Vector2f(48, okno->getSize().y - pozadie.getSize().y- 50));
		okno->draw(pozadie);

		text.setColor(sf::Color::Black);
		text.setPosition(sf::Vector2f(pozadie.getGlobalBounds().left + 5, pozadie.getGlobalBounds().top + 5));
		okno->draw(text);

		//std::cout << "tu je ten popup" << std::endl;
	}
}


void Stav::onEnter() {
	
}


void Stav::onExit() {
	
}

std::string Stav::Getnazov() {
	return nazov;
}

void Stav::Setnazov(std::string paNazov) {
	nazov = paNazov;
}

void Stav::zobrazPopup(std::string paCo) {
	popupText = paCo;
	stav = StavAkcia::ZOBRAZUJE_POPUP;
}