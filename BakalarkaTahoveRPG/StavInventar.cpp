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
#include "PopupOkno.h"
#include "Tlacidlo.h"


StavInventar::StavInventar(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	
	ukazovatel.setSize(sf::Vector2f(48, 48));
	ukazovatel.setFillColor(sf::Color(255, 0, 0, 128));
	oznacene = 0;
	nasirku =18;
	otvoreneZboja = false;

	sf::Sprite* s = new sf::Sprite();
	tlacidloSpat = new Tlacidlo(s, s, "<--", sf::Vector2f(okno->getSize().x - 60.f, 10.f), sf::Vector2f(30, 25.f), font, 20U);
}


StavInventar::~StavInventar() {
	delete tlacidloSpat;
}



void StavInventar::onEnter() {
	Stav::onEnter();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		stlacenaKlavesa = true;
	}
	

	hrac = hra->GetHrac();
	inventar = hrac->Getinventar();
	oznacene = 0;
	
}


void StavInventar::onExit() {
	Stav::onExit();
}


void StavInventar::render() {

	int startX = 20;
	int startY = 70;
	

	sf::Text text("Inventory", *font, 45U);
	text.setPosition(sf::Vector2f(10.f, 10.f));
	okno->draw(text);


	text.setString("Gold: " + std::to_string(inventar->Getzlato()));
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
		vykresliOknoPredmetu(inventar->dajPredmetNaIndexe(oznacene), startX + (oznacene%nasirku) * 55 + 48, startY + (oznacene / nasirku) * 55 + 48, okno, true);
	}

	okno->draw(tlacidloSpat->Getramcek());
	sf::Text tt = tlacidloSpat->Gettext();
	tt.setColor(sf::Color::Black);
	okno->draw(tt);


	text.setString("Enter - use selected item\nX - drop selected item");
	text.setPosition(20.f, okno->getSize().y - 55.f);
	text.setColor(sf::Color::Yellow);
	text.setCharacterSize(20);
	okno->draw(text);

	Stav::render();

}


void StavInventar::update(double delta) {
	if (hra->maFocus()) {
		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
			{
				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);


				tlacidloSpat->skontrolujKlik(pozicia);
				if (tlacidloSpat->Getzakliknute()) {
					tlacidloSpat->Setzakliknute(false);
					if (otvoreneZboja) {
						otvoreneZboja = false;
						hra->zmenStavRozhrania("stavBoj");
					}
					else {
						hra->zmenStavRozhrania("hranieHry");
					}
				}



			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				stlacenaMys = false;
			}


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
					if(otvoreneZboja){
						if (dynamic_cast<Elixir*>(p) != NULL) {
							p->pouzi(hrac);
						}
						else {
							zobrazPopup(new PopupOkno("You can't equip your items while you are fighting!"));
						}
					}
					else {
						p->pouzi(hrac);
					}
				}
			}

			if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				stlacenaKlavesa = true;
				if (oznacene >= 0 && oznacene < inventar->pocetPredmetov()) {
					hrac->vyhodPredmet(inventar->dajPredmetNaIndexe(oznacene));
				}
			}

			if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::I))) {
				if (otvoreneZboja) {
					otvoreneZboja = false;
					hra->zmenStavRozhrania("stavBoj");
				}
				else {
					hra->zmenStavRozhrania("hranieHry");
				}
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


void StavInventar::vykresliOknoPredmetu(Predmet*predmet, int x, int y, sf::RenderWindow* okno, bool predaj) {
	
	// vykreslenie obdlznika na ktorom sa bude vypisovat info predmetu 
	sf::RectangleShape obdlznik;
	obdlznik.setSize(sf::Vector2f(230.f, 200.f));// vyska a sirka okienka
	obdlznik.setOutlineColor(sf::Color::Red);
	obdlznik.setOutlineThickness(2);


	float posX, posY;
	posX = x -5.f;
	posY = y -5.f;

	// tu už je samotny vypis infa
	sf::Text text(predmet->Getmeno(), *font, 18U);//vypisanie mena
	if (text.getGlobalBounds().width > obdlznik.getGlobalBounds().width - 5) {
		obdlznik.setSize(sf::Vector2f(text.getGlobalBounds().width+20, 200));
	}

	if ((signed int)posX < (signed int)okno->getSize().x - (obdlznik.getSize().x +20)) {
		obdlznik.setPosition(posX, posY);
	}
	else {
		posX -= (obdlznik.getSize().x + 20);
		obdlznik.setPosition(posX, posY);
	}
	okno->draw(obdlznik);


	text.setColor(sf::Color::Black);
	
	if (hrac->Getstatistika()->dajUroven() < predmet->Geturoven()) text.setColor(sf::Color::Red);

	text.setPosition(sf::Vector2f(posX+5.f, posY+5.f));
	okno->draw(text);

	text.setScale(1,1);
	text.setCharacterSize(14U);
	text.setString(predmet->Getstringovytyp());
	text.setPosition(sf::Vector2f(posX+5.f, posY+23.f));
	okno->draw(text);


	text.setString("Level needed: " +std::to_string( predmet->Geturoven()));
	text.setPosition(sf::Vector2f(posX + 5.f, posY + 35.f));
	okno->draw(text);

	if (dynamic_cast<Elixir*>(predmet) != NULL) {
		text.setColor(sf::Color::Black);
		text.setCharacterSize(14U);

		Elixir* elixir = (Elixir*)predmet;

		std::string info = elixir->dajInfo();

		if (predaj) {
			info += "\n\nValue: " + std::to_string((int)round(elixir->Getcena() / 2));
		}
		else {
			info += "\n\nValue: " + std::to_string(elixir->Getcena());
		}

		text.setPosition(sf::Vector2f(posX + 5.f, posY + 48.f));
		text.setString(info);
		okno->draw(text);
		return;

	}


	
	if (dynamic_cast<Pouzitelny*>(predmet) != NULL) {
		text.setColor(sf::Color::Black);
		text.setCharacterSize(14U);
		Pouzitelny* pouzitelny = (Pouzitelny*)predmet;
		std::string info = "";

		if (dynamic_cast<Zbran*>(predmet) != NULL)
		{
			Zbran* pom = (Zbran*)predmet;
			if (pom->Gettyp() != 11) {
				info += "Damage: ";
				info += std::to_string(pom->Getminposkodenie()) + " - ";
				info += std::to_string(pom->Getmaxposkodenie());
				info += "\n";
				info += "Attack speed: " + std::to_string(pom->GetrychlostUtoku()) + " ms\n";
			}
		}


		if (pouzitelny->Getarmor() != 0) {
			info += "Armor: ";
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
			info += "Strenght: ";
			info += std::to_string(pouzitelny->Getsila());
			info += "\n";
		}

		if (pouzitelny->Getrychlost() != 0) {
			info += "Speed: ";
			info += std::to_string(pouzitelny->Getrychlost());
			info += "\n";
		}

		if (pouzitelny->Getinteligencia() != 0) {
			info += "Intellect: ";
			info += std::to_string(pouzitelny->Getinteligencia());
			info += "\n";
		}

		if (pouzitelny->GetarmorMult() != 0) {
			info += "Armor: ";
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
			info += "Strenght: ";
			info += std::to_string((int)round(pouzitelny->GetsilaMult() * 100));
			info += " %\n";
		}

		if (pouzitelny->GetrychlostMult() != 0) {
			info += "Speed: ";
			info += std::to_string((int)round(pouzitelny->GetrychlostMult() * 100));
			info += " %\n";
		}

		if (pouzitelny->GetinteligenciaMult() != 0) {
			info += "Intellect: ";
			info += std::to_string((int)round(pouzitelny->GetinteligenciaMult() * 100));
			info += " %\n";
		}

		if (predaj) {
			info += "\n\nValue: " + std::to_string((int)round(pouzitelny->Getcena() / 2));
		}
		else {
			info += "\n\nValue: " + std::to_string(pouzitelny->Getcena());
		}

		text.setPosition(sf::Vector2f(posX + 5.f, posY + 48.f));
		text.setString(info);
		okno->draw(text);

		

	}

}

void StavInventar::Setzboja(bool paNa) {
	otvoreneZboja = paNa;
}