#include "Stav.h"
#include "Hra.h"
#include "PopupOkno.h"
#include "Loader.h"

#include <sstream>
#include <iomanip>  

Stav::Stav(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) {
	nazov = paNazov;
	okno = paOkno;
	hra = paHra;
	stav = StavAkcia::NORMAL;

	stlacenaMys = true;
	stlacenaKlavesa = true;
	font = Loader::Instance()->nacitajFont("font2.ttf");
}



Stav::~Stav() {
}



void Stav::update(double delta) {

	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) stlacenaKlavesa = false;
		
		if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			if (popupText.size() > 0) {
				if (popupText.at(0)->skoncil()) {
					PopupOkno* skonceny = popupText.at(0);
					popupText.pop_front();
					delete skonceny;
					stlacenaKlavesa = true;	
				}
				else {
					stlacenaKlavesa = true;
					popupText.at(0)->dajDalsi();
				}
			}
			else {
				stav = StavAkcia::NORMAL;
			}
		}
	}

}


void Stav::render() {

	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {
		if (popupText.size() == 0) {
			stav = StavAkcia::NORMAL;
		}
		else {


			sf::RectangleShape pozadie;
			sf::Text text("", *font, 17);
			PopupOkno* pop = popupText.at(0);

			if (!pop->skoncil()) {
				text.setString(pop->aktualnaStrana() + "\n>>>");
			}
			else {
				text.setString(pop->aktualnaStrana());
			}


			pozadie.setSize(sf::Vector2f(okno->getSize().x - 50.f, text.getGlobalBounds().height + 10.f));
			pozadie.setOutlineColor(sf::Color::Red);
			pozadie.setOutlineThickness(2);
			pozadie.setPosition(sf::Vector2f(23, okno->getSize().y - pozadie.getSize().y - 100));

			//ak sa text nezmesti na širku tak sa zmenší ve¾kos
			if (text.getGlobalBounds().width > pozadie.getGlobalBounds().width - 20) {
				text.setScale(sf::Vector2f((pozadie.getGlobalBounds().width - 20) / text.getGlobalBounds().width, (pozadie.getGlobalBounds().width - 20) / text.getGlobalBounds().width));
				pozadie.setSize(sf::Vector2f(okno->getSize().x - 50.f, text.getGlobalBounds().height + 10.f));
				pozadie.setPosition(sf::Vector2f(23, okno->getSize().y - pozadie.getSize().y - 25));
			}

			okno->draw(pozadie);
			text.setColor(sf::Color::Black);
			text.setPosition(sf::Vector2f(pozadie.getGlobalBounds().left + 5, pozadie.getGlobalBounds().top + 5));
			okno->draw(text);
		}
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
	popupText.push_back(paCo);
	stav = StavAkcia::ZOBRAZUJE_POPUP;
}

bool Stav::GetzobrazujePopup() {
	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {
		return true;
	}
	else return false;
}

std::string Stav::floattostring(float cislo) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << cislo;
	std::string ssekundy = stream.str();
	return ssekundy;
}