#include "Stav.h"
#include "Hra.h"
#include "PopupOkno.h"
#include "Loader.h"

#include "Tlacidlo.h"

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

	sf::Sprite* s = new sf::Sprite();
	popDalej = new Tlacidlo(s, s, "-->", sf::Vector2f(0.f,0.f), sf::Vector2f(30.f, 25.f), font, 20U);

}



Stav::~Stav() {
}



void Stav::update(double delta) {

	if (stav == StavAkcia::ZOBRAZUJE_POPUP) {
		

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) stlacenaKlavesa = false;
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
		{
			sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
			popDalej->skontrolujKlik(pozicia);

		}

		if ((!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) || popDalej->Getzakliknute() ) {

			if (popDalej->Getzakliknute()) {
				stlacenaMys = true;
				popDalej->Setzakliknute(false);
			}

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

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			stlacenaMys = false;
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
			sf::Text text("", *font, 20);
			PopupOkno* pop = popupText.at(0);

			if (!pop->skoncil()) {
				text.setString(pop->aktualnaStrana() + "\n\n>>>");
			}
			else {
				text.setString(pop->aktualnaStrana());
			}


			pozadie.setSize(sf::Vector2f(okno->getSize().x - 50.f, text.getGlobalBounds().height + 25.f));
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

			// tlacidlo -->
			popDalej->Setpozicia(sf::Vector2f(pozadie.getGlobalBounds().left + pozadie.getGlobalBounds().width - popDalej->getGlobalBounds().width -1,
				pozadie.getGlobalBounds().top - popDalej->getGlobalBounds().height));

			sf::RectangleShape ramcek = popDalej->Getramcek();
			ramcek.setOutlineColor(sf::Color::Red);
			okno->draw(ramcek);
			text = popDalej->Gettext();
			text.setColor(sf::Color::Black);
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