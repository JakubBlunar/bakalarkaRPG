#include "StavInventar.h"

#include <math.h>
#include <typeinfo>

#include "Hra.h"
#include "Hrac.h"
#include "Statistika.h"
#include "Zameranie.h"
#include "Inventar.h"
#include "Pouzitelny.h"
#include "Zbran.h"



StavInventar::StavInventar(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font2.otf");
	
	
	sf::Texture texture;
	texture.create(200, 200);
	
	ukazovatel = new sf::Sprite();
	ukazovatel->setTexture(texture);
	ukazovatel->setTextureRect(sf::IntRect(0, 0, 48, 48));
	ukazovatel->setColor(sf::Color(0, 0, 255, 128));
	oznacene = -10;
	nasirku =18;
}


StavInventar::~StavInventar() {
	delete(font);
	delete(ukazovatel);
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

	//text.setCharacterSize(35U);
	//text.setString(hrac->GetZameranie()->Getnazov());
	//text.setPosition(sf::Vector2f(32.f, 56.f));
	//okno->draw(text);

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
			ukazovatel->setPosition(sf::Vector2f((float)startX + (i%nasirku) * 55, (float)startY + (i / nasirku) * 55));
			okno->draw(*ukazovatel);
			
		}
	}

	if (oznacene >= 0 && oznacene < inventar->pocetPredmetov()) {
		vykresliOknoPredmetu(inventar->dajPredmetNaIndexe(oznacene), startX + (oznacene%nasirku) * 55 + 48, startY + (oznacene / nasirku) * 55 + 48, okno);
	}

	//std::cout << oznacene << std::endl;
}


void StavInventar::update(double delta) {

	if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		stlacenaKlavesa = true;

		if (oznacene+nasirku < inventar->pocetPredmetov()) {
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
			if (oznacene>=0 && oznacene < inventar->pocetPredmetov()) {
				Predmet* p = inventar->dajPredmetNaIndexe(oznacene);
				p->pouzi(hrac);
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
			) {
			stlacenaKlavesa = false;
		}
		
}


void StavInventar::vykresliOknoPredmetu(Predmet*predmet, int x, int y, sf::RenderWindow* okno) {
	
	// vykreslenie obdlznika na ktorom sa bude vypisovat info predmetu 
	sf::RectangleShape obdlznik;
	obdlznik.setSize(sf::Vector2f(180.f, 200.f));// vyska a sirka okienka
	obdlznik.setOutlineColor(sf::Color::Red);
	obdlznik.setOutlineThickness(2);


	float posX, posY;
	posX = x -5.f;
	posY = y -5.f;

	if ((signed int)posX < (signed int)okno->getSize().x - 200) {
		obdlznik.setPosition(posX, posY);
	}
	else {
		posX -= 180;
		obdlznik.setPosition(posX, posY);
	}
	okno->draw(obdlznik);

	// tu už je samotny vypis infa
	sf::Text text(predmet->Getmeno(), *font, 15U);

	text.setColor(sf::Color::Black);
	
	if (hrac->Getstatistika()->dajUroven() < predmet->Geturoven()) text.setColor(sf::Color::Red);

	text.setPosition(sf::Vector2f(posX+10.f, posY+5.f));
	okno->draw(text);

	
	text.setCharacterSize(10U);
	text.setString(predmet->Getstringovytyp());
	text.setPosition(sf::Vector2f(posX+5.f, posY+23.f));
	okno->draw(text);


	text.setString("Potrebna uroven: " +std::to_string( predmet->Geturoven()));
	text.setPosition(sf::Vector2f(posX + 5.f, posY + 35.f));
	okno->draw(text);

	
	if (dynamic_cast<Pouzitelny*>(predmet) != NULL) {
		text.setColor(sf::Color::Black);
		text.setCharacterSize(13U);
		Pouzitelny* pouzitelny = (Pouzitelny*)predmet;
		std::string bonusy = "";

		if (dynamic_cast<Zbran*>(predmet) != NULL)
		{
			Zbran* pom = (Zbran*)predmet;
			if (pom->Gettyp() != 3) {
				bonusy += "DMG: ";
				bonusy += std::to_string(pom->Getminposkodenie()) + " - ";
				bonusy += std::to_string(pom->Getmaxposkodenie());
				bonusy += "\n";
			}
		}


		if (pouzitelny->Getarmor() != 0) {
			bonusy += "Obrana: ";
			bonusy += std::to_string(pouzitelny->Getarmor());
			bonusy += "\n";
		}

		if (pouzitelny->Gethp()!=0) {
			bonusy += "Hp: ";
			bonusy += std::to_string(pouzitelny->Gethp());
			bonusy += "\n";
		}

		if (pouzitelny->Getmp() != 0) {
			bonusy += "Mp: ";
			bonusy += std::to_string(pouzitelny->Getmp());
			bonusy += "\n";
		}

		if (pouzitelny->Getsila() != 0) {
			bonusy += "Sila: ";
			bonusy += std::to_string(pouzitelny->Getsila());
			bonusy += "\n";
		}

		if (pouzitelny->Getrychlost() != 0) {
			bonusy += "Rychlost: ";
			bonusy += std::to_string(pouzitelny->Getrychlost());
			bonusy += "\n";
		}

		if (pouzitelny->Getinteligencia() != 0) {
			bonusy += "Intelekt: ";
			bonusy += std::to_string(pouzitelny->Getinteligencia());
			bonusy += "\n";
		}

		if (pouzitelny->GetarmorMult() != 0) {
			bonusy += "Obrana: ";
			bonusy += std::to_string((int)round(pouzitelny->GetarmorMult() * 100));
			bonusy += " %\n";
		}

		if (pouzitelny->GethpMult() != 0) {
			bonusy += "Hp: ";
			bonusy += std::to_string((int)round(pouzitelny->GethpMult() * 100));
			bonusy += " %\n";
		}

		if (pouzitelny->GetmpMult() != 0) {
			bonusy += "Mp: ";
			bonusy += std::to_string((int)round(pouzitelny->GetmpMult()*100));
			bonusy += " %\n";
		}

		if (pouzitelny->GetsilaMult() != 0) {
			bonusy += "Sila: ";
			bonusy += std::to_string((int)round(pouzitelny->GetsilaMult() * 100));
			bonusy += " %\n";
		}

		if (pouzitelny->GetrychlostMult() != 0) {
			bonusy += "Rychlost: ";
			bonusy += std::to_string((int)round(pouzitelny->GetrychlostMult() * 100));
			bonusy += " %\n";
		}

		if (pouzitelny->GetinteligenciaMult() != 0) {
			bonusy += "Intelekt: ";
			bonusy += std::to_string((int)round(pouzitelny->GetinteligenciaMult() * 100));
			bonusy += " %\n";
		}


		text.setPosition(sf::Vector2f(posX + 5.f, posY + 48.f));
		text.setString(bonusy);
		okno->draw(text);

	}

}