
#include "Stav.h"
#include "Hra.h"
#include "PopupOkno.h"

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
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) stlacenaKlavesa = false;
		
		if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			
			if (popupText->skoncil()) {
				delete popupText;
				popupText = nullptr;
				stav = StavAkcia::NORMAL;
			}
			else {
				stlacenaKlavesa = true;
				popupText->dajDalsi();
			}
		}
	}

}


void Stav::render() {

	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {

		sf::RectangleShape pozadie;
		sf::Text text("", *font, 17);
		if (!popupText->skoncil()) {
			text.setString(popupText->aktualnaStrana() + "\n>>>");
		}
		else {
			text.setString(popupText->aktualnaStrana());
		}
		

		pozadie.setSize(sf::Vector2f(okno->getSize().x-50.f, text.getGlobalBounds().height + 10.f));
		pozadie.setOutlineColor(sf::Color::Red);
		pozadie.setOutlineThickness(2);
		pozadie.setPosition(sf::Vector2f(23, okno->getSize().y - pozadie.getSize().y - 50));
		
		//ak sa text nezmesti na širku tak sa zmenší ve¾kos
		if (text.getGlobalBounds().width > pozadie.getGlobalBounds().width-20) {
			text.setScale(sf::Vector2f((pozadie.getGlobalBounds().width-20) / text.getGlobalBounds().width, (pozadie.getGlobalBounds().width-20) / text.getGlobalBounds().width));
			pozadie.setSize(sf::Vector2f(okno->getSize().x - 50.f, text.getGlobalBounds().height+10.f));
			pozadie.setPosition(sf::Vector2f(23, okno->getSize().y - pozadie.getSize().y - 25));
		}

		okno->draw(pozadie);
		text.setColor(sf::Color::Black);
		text.setPosition(sf::Vector2f(pozadie.getGlobalBounds().left + 5, pozadie.getGlobalBounds().top + 5));
		okno->draw(text);
	}
}


void Stav::onEnter() {
	stlacenaKlavesa = true;
}


void Stav::onExit() {
	
}

std::string Stav::Getnazov() {
	return nazov;
}

void Stav::Setnazov(std::string paNazov) {
	nazov = paNazov;
}

void Stav::zobrazPopup(PopupOkno* paCo) {
	popupText = paCo;
	stav = StavAkcia::ZOBRAZUJE_POPUP;
}

bool Stav::GetzobrazujePopup() {
	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {
		return true;
	}
	else return false;
}