#include "StavVolbaZamerania.h"
#include <string>
#include "Loader.h"
#include "Hra.h"
#include "Hrac.h"
#include "Zameranie.h"
#include "StavHranieHry.h"
#include "Mapa.h"
#include "Akcia.h"

#include "AkciaDmg.h"

#include "Nepriatel.h"
#include "StavBoj.h"
#include "Boj.h"
#include "AkciaPoskodenieZbranou.h"
#include "AkciaLiecenie.h"
#include "AkciaPridanieEfektu.h"
#include "EfektUpravStat.h"


StavVolbaZamerania::StavVolbaZamerania(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra) : Stav(paNazov,paOkno,paHra) {
	font = Loader::Instance()->nacitajFont("font2.otf");
	std::cout << "Volba zamerania vytvorena" << std::endl;
}



StavVolbaZamerania::~StavVolbaZamerania() {
	std::cout << "Volba zamerania zmazana" << std::endl;
}

void StavVolbaZamerania::onEnter() {
	Stav::onEnter();
	oznacene = 1;
    stlacenaKlavesa = true;
	
}


void StavVolbaZamerania::onExit() {
	Stav::onExit();
}


void StavVolbaZamerania::render() {
	
	int i = 60;
	sf::RectangleShape rectangle;
	
	rectangle.setSize(sf::Vector2f(20.f+okno->getSize().x / 4, okno->getSize().y -40.f));
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(  i*oznacene -10.f + (oznacene-1)*(okno->getSize().x / 4.f)  , 30-10.f);
	okno->draw(rectangle);
	
	rectangle.setFillColor(sf::Color::White);
	rectangle.setSize(sf::Vector2f(okno->getSize().x/4.f, okno->getSize().y /2.f));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition((float)i, 30.f);
	okno->draw(rectangle);

	rectangle.setSize(sf::Vector2f(okno->getSize().x / 4.f, okno->getSize().y / 2.f));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(i*2 + okno->getSize().x / 4.f, 30.f);
	okno->draw(rectangle);
	
	rectangle.setSize(sf::Vector2f(okno->getSize().x / 4.f, okno->getSize().y / 2.f));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(i*3 + 2*okno->getSize().x / 4.f, 30.f);
	okno->draw(rectangle);

	Stav::render();
}


void StavVolbaZamerania::update(double delta) {
	if (hra->maFocus()) {

		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				if (oznacene > 1) {
					oznacene--;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				if (oznacene < 3) {
					oznacene++;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				hra->zmenStavRozhrania("hlavneMenu");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				Zameranie* zameranie = new Zameranie("Warrior",800,400,80,60,40);

				Efekt* efekt = new EfektUpravStat("shout","sila", 2);
				Efekt* efekt2 = new EfektUpravStat("shout", "sila", -2);


				zameranie->vlozAkciu(new AkciaPridanieEfektu("Bojovnikov rev", "shout", 500, 5000, 20000, efekt->popis(),3,efekt,true), 1);
				zameranie->vlozAkciu(new AkciaPridanieEfektu("Hrozivy rev", "shout", 500, 0, 15000, "Znizi utocnikovu silu\n" + efekt2->popis(), 2, efekt2, false), 1);
				zameranie->vlozAkciu(new AkciaLiecenie("Slabé liecenie:", "healing1", 3000, 10000, 20, "Vylieci ta!", 1,AkciaTyp::MAGICKA,10), 1);
				zameranie->vlozAkciu(new AkciaDmg("Bash", "attack", 1000, 3000, 0, "Postava silno buchne zbranou\nSposobi nepriatelovi velke skody.",0,AkciaTyp::FYZICKA,1), 1);

				Hrac* hrac = new Hrac(zameranie);
				hrac->Getstatistika()->vlozAkciu(new AkciaPoskodenieZbranou("Utok", "Bezny utok nasadenou zbranou", hrac->Getstatistika()));
				hra->SetHrac(hrac);

				

				Loader* loader = Loader::Instance();
				loader->nacitajMapu("start", 0, 2, 2);
				hra->zmenStavRozhrania("hranieHry");

			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				stlacenaKlavesa = false;
			}
		}
	}
}