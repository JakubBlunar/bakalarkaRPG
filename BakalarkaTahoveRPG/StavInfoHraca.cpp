#include "StavInfoHraca.h"
#include "Hra.h"
#include "Hrac.h"
#include "Statistika.h"
#include "Zameranie.h"

StavInfoHraca::StavInfoHraca(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {

	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font2.otf");
}


StavInfoHraca::~StavInfoHraca() {
	delete(font);
}



void StavInfoHraca::onEnter() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		stlacenaKlavesa = true;
	}

	hrac = hra->GetHrac();
	Stav::onEnter();
}


void StavInfoHraca::onExit() {
	Stav::onExit();
}


void StavInfoHraca::render() {

		sf::Text text("Hrac Info",*font, 45U);
		text.setPosition(sf::Vector2f(10.f, 10.f));
		okno->draw(text);
		
		text.setCharacterSize(35U);
		text.setString(hrac->GetZameranie()->Getnazov());
		text.setPosition(sf::Vector2f(32.f, 56.f));
		okno->draw(text);

		int lvl = hrac->Getstatistika()->dajUroven();
		text.setCharacterSize(30U);
		text.setString(" Level: " + std::to_string(lvl));
		text.setPosition(sf::Vector2f(38.f, 91.f));
		okno->draw(text);

		int xpTeraz = hrac->Getstatistika()->xpNaLevel(lvl);
		int xpNaDalsi = hrac->Getstatistika()->xpNaLevel(lvl+1);
		text.setCharacterSize(15U);
		text.setString(" Skusenosti: " + std::to_string(xpTeraz) + " / " + std::to_string(xpNaDalsi));
		text.setPosition(sf::Vector2f(15.f, 135.f));
		okno->draw(text);


		int hpTeraz = hrac->Getstatistika()->Gethp();
		int hpMax = hrac->Getstatistika()->GethpMax();
		text.setCharacterSize(15U);
		text.setString(" Hp: " + std::to_string(hpTeraz) + " / " + std::to_string(hpMax));
		text.setPosition(sf::Vector2f(15.f, 152.f));
		okno->draw(text);

		int mpTeraz = hrac->Getstatistika()->Getmp();
		int mpMax = hrac->Getstatistika()->GetmpMax();
		text.setCharacterSize(15U);
		text.setString(" Mp: " + std::to_string(mpTeraz) + " / " + std::to_string(mpMax));
		text.setPosition(sf::Vector2f(15.f, 170.f));
		okno->draw(text);

		int stat = hrac->Getstatistika()->Getsila();
		text.setCharacterSize(15U);
		text.setString(" Sila: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 187.f));
		okno->draw(text);

		stat = hrac->Getstatistika()->Getintelekt();
		text.setCharacterSize(15U);
		text.setString(" Intelekt: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 204.f));
		okno->draw(text);

		stat = hrac->Getstatistika()->Getrychlost();
		text.setCharacterSize(15U);
		text.setString(" Rychlost: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 221.f));
		okno->draw(text);
		
		stat = hrac->Getstatistika()->Getobrana();
		text.setCharacterSize(15U);
		text.setString(" Obrana: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 238.f));
		okno->draw(text);

	//std::cout << oznacene << std::endl;
}


void StavInfoHraca::update(double delta) {

	if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::C))) {
		hra->zmenStavRozhrania("hranieHry");
	}

	if (stlacenaKlavesa && !sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
		stlacenaKlavesa = false;
	}
}