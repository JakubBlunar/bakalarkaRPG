#include "StavInventar.h"

#include <math.h>
#include <typeinfo>

#include "Loader.h"
#include "Hra.h"
#include "Hrac.h"
#include "Statistika.h"
#include "Zameranie.h"
#include "Inventar.h"
#include "Pouzitelny.h"
#include "Zbran.h"
#include "Elixir.h"


StavInventar::StavInventar(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	font = Loader::Instance()->nacitajFont("font2.otf");
	
	ukazovatel.setSize(sf::Vector2f(48, 48));
	ukazovatel.setFillColor(sf::Color(255, 0, 0, 128));
	oznacene = -10;
	nasirku =18;
}


StavInventar::~StavInventar() {
}



void StavInventar::onEnter() {
	Stav::onEnter();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		stlacenaKlavesa = true;
	}
	

	hrac = hra->GetHrac();
	inventar = hrac->Getinventar();
	if (inventar->pocetPredmetov() > 0) {
		oznacene = 0;
	}
	else {
		oznacene = -10;
	}
}


void StavInventar::onExit() {
	Stav::onExit();
}


void StavInventar::render() {

	int startX = 20;
	int startY = 70;
	

	sf::Text text("Inventar", *font, 45U);
	text.setPosition(sf::Vector2f(10.f, 10.f));
	okno->draw(text);


	text.setString("Pocet Zlata:  " + std::to_string(inventar->Getzlato()));
	text.setPosition(500, 30);
	text.setColor(sf::Color::Yellow);
	text.setCharacterSize(20);
	okno->draw(text);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(48, 48));


	sf::Sprite* predmetObrazok;
	for (int i = 0; i < inventar->Getkapacita(); i++) {
		
		rectangle.setPosition((float)startX + (i%nasirku)*55 , (float)startY + (i/nasirku)*55);
		okno->draw(rectangle);

		if (i < inventar->pocetPredmetov()) {
			
			predmetObrazok = inventar->dajPredmetNaIndexe(i)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(sf::Vector2f((float)startX + (i%nasirku) * 55, (float)startY + (i / nasirku) * 55));

			okno->draw(*predmetObrazok);
		}


		if (i == oznacene) {
			ukazovatel.setPosition(sf::Vector2f((float)startX + (i%nasirku) * 55, (float)startY + (i / nasirku) * 55));
			okno->draw(ukazovatel);
			
		}
	}

	if (oznacene >= 0 && oznacene < inventar->pocetPredmetov()) {
		vykresliOknoPredmetu(inventar->dajPredmetNaIndexe(oznacene), startX + (oznacene%nasirku) * 55 + 48, startY + (oznacene / nasirku) * 55 + 48, okno);
	}

	text.setString("Enter - pouzi oznaceny predmet\nX - vyhod predmet");
	text.setPosition(20.f, okno->getSize().y - 55.f);
	text.setColor(sf::Color::Yellow);
	text.setCharacterSize(20);
	okno->draw(text);

	Stav::render();
	//std::cout << oznacene << std::endl;
}


void StavInventar::update(double delta) {
	if (hra->maFocus()) {
		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				stlacenaKlavesa = true;

				if (oznacene + nasirku < inventar->pocetPredmetov()) {
					oznacene += nasirku;
				}
				else {
					oznacene = inventar->pocetPredmetov() - 1;
				}
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				stlacenaKlavesa = true;
				if (oznacene >= nasirku) {
					oznacene -= nasirku;
				}
				else {
					oznacene = 0;
				}
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				stlacenaKlavesa = true;
				if (oznacene > 0) {
					oznacene--;
				}
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				stlacenaKlavesa = true;
				if (oznacene < inventar->pocetPredmetov() - 1) {
					oznacene++;
				}
			}


			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				stlacenaKlavesa = true;
				if (oznacene >= 0 && oznacene < inventar->pocetPredmetov()) {
					Predmet* p = inventar->dajPredmetNaIndexe(oznacene);
					p->pouzi(hrac);
				}
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				stlacenaKlavesa = true;
				if (oznacene >= 0 && oznacene < inventar->pocetPredmetov()) {
					hrac->vyhodPredmet(inventar->dajPredmetNaIndexe(oznacene));
				}
			}

			if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::I))) {
				hra->zmenStavRozhrania("hranieHry");
			}

			if (stlacenaKlavesa && !sf::Keyboard::isKeyPressed(sf::Keyboard::I)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::X)
				) {
				stlacenaKlavesa = false;
			}
		}
	}
}


void StavInventar::vykresliOknoPredmetu(Predmet*predmet, int x, int y, sf::RenderWindow* okno) {
	
	// vykreslenie obdlznika na ktorom sa bude vypisovat info predmetu 
	sf::RectangleShape obdlznik;
	obdlznik.setSize(sf::Vector2f(230.f, 200.f));// vyska a sirka okienka
	obdlznik.setOutlineColor(sf::Color::Red);
	obdlznik.setOutlineThickness(2);


	float posX, posY;
	posX = x -5.f;
	posY = y -5.f;

	if ((signed int)posX < (signed int)okno->getSize().x - 230) {
		obdlznik.setPosition(posX, posY);
	}
	else {
		posX -= 180;
		obdlznik.setPosition(posX, posY);
	}
	okno->draw(obdlznik);

	// tu už je samotny vypis infa
	sf::Text text(predmet->Getmeno(), *font, 14U);//vypisanie mena

	text.setColor(sf::Color::Black);
	
	if (hrac->Getstatistika()->dajUroven() < predmet->Geturoven()) text.setColor(sf::Color::Red);

	text.setPosition(sf::Vector2f(posX+5.f, posY+5.f));
	okno->draw(text);

	
	text.setCharacterSize(10U);
	text.setString(predmet->Getstringovytyp());
	text.setPosition(sf::Vector2f(posX+5.f, posY+23.f));
	okno->draw(text);


	text.setString("Potrebna uroven: " +std::to_string( predmet->Geturoven()));
	text.setPosition(sf::Vector2f(posX + 5.f, posY + 35.f));
	okno->draw(text);

	if (dynamic_cast<Elixir*>(predmet) != NULL) {
		text.setColor(sf::Color::Black);
		text.setCharacterSize(13U);

		Elixir* elixir = (Elixir*)predmet;

		std::string info = elixir->dajInfo();
		info += "\n\nCena: " + std::to_string(elixir->Getcena());

		text.setPosition(sf::Vector2f(posX + 5.f, posY + 48.f));
		text.setString(info);
		okno->draw(text);
		return;

	}


	
	if (dynamic_cast<Pouzitelny*>(predmet) != NULL) {
		text.setColor(sf::Color::Black);
		text.setCharacterSize(13U);
		Pouzitelny* pouzitelny = (Pouzitelny*)predmet;
		std::string info = "";

		if (dynamic_cast<Zbran*>(predmet) != NULL)
		{
			Zbran* pom = (Zbran*)predmet;
			if (pom->Gettyp() != 11) {
				info += "DMG: ";
				info += std::to_string(pom->Getminposkodenie()) + " - ";
				info += std::to_string(pom->Getmaxposkodenie());
				info += "\n";
				info += "Rychlost utoku: " + std::to_string(pom->GetrychlostUtoku()) + " ms\n";
			}
		}


		if (pouzitelny->Getarmor() != 0) {
			info += "Obrana: ";
			info += std::to_string(pouzitelny->Getarmor());
			info += "\n";
		}

		if (pouzitelny->Gethp()!=0) {
			info += "Hp: ";
			info += std::to_string(pouzitelny->Gethp());
			info += "\n";
		}

		if (pouzitelny->Getmp() != 0) {
			info += "Mp: ";
			info += std::to_string(pouzitelny->Getmp());
			info += "\n";
		}

		if (pouzitelny->Getsila() != 0) {
			info += "Sila: ";
			info += std::to_string(pouzitelny->Getsila());
			info += "\n";
		}

		if (pouzitelny->Getrychlost() != 0) {
			info += "Rychlost: ";
			info += std::to_string(pouzitelny->Getrychlost());
			info += "\n";
		}

		if (pouzitelny->Getinteligencia() != 0) {
			info += "Intelekt: ";
			info += std::to_string(pouzitelny->Getinteligencia());
			info += "\n";
		}

		if (pouzitelny->GetarmorMult() != 0) {
			info += "Obrana: ";
			info += std::to_string((int)round(pouzitelny->GetarmorMult() * 100));
			info += " %\n";
		}

		if (pouzitelny->GethpMult() != 0) {
			info += "Hp: ";
			info += std::to_string((int)round(pouzitelny->GethpMult() * 100));
			info += " %\n";
		}

		if (pouzitelny->GetmpMult() != 0) {
			info += "Mp: ";
			info += std::to_string((int)round(pouzitelny->GetmpMult()*100));
			info += " %\n";
		}

		if (pouzitelny->GetsilaMult() != 0) {
			info += "Sila: ";
			info += std::to_string((int)round(pouzitelny->GetsilaMult() * 100));
			info += " %\n";
		}

		if (pouzitelny->GetrychlostMult() != 0) {
			info += "Rychlost: ";
			info += std::to_string((int)round(pouzitelny->GetrychlostMult() * 100));
			info += " %\n";
		}

		if (pouzitelny->GetinteligenciaMult() != 0) {
			info += "Intelekt: ";
			info += std::to_string((int)round(pouzitelny->GetinteligenciaMult() * 100));
			info += " %\n";
		}

		info += "\n\nCena: " + std::to_string(pouzitelny->Getcena());

		text.setPosition(sf::Vector2f(posX + 5.f, posY + 48.f));
		text.setString(info);
		okno->draw(text);

		

	}

}