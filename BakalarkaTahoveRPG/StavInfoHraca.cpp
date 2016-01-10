#include "StavInfoHraca.h"
#include "Hra.h"
#include "Hrac.h"
#include "Statistika.h"
#include "Zameranie.h"
#include "Pouzitelny.h"
#include "Zbran.h"

StavInfoHraca::StavInfoHraca(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font2.otf");


	sf::Texture texture;
	texture.create(200, 200);
	texture.setSmooth(true);
	ukazovatel = new sf::Sprite();
	ukazovatel->setTexture(texture);
	ukazovatel->setTextureRect(sf::IntRect(0, 0, 48, 48));
	ukazovatel->setColor(sf::Color(255, 0, 0, 128));
	oznacene = 1;

}


StavInfoHraca::~StavInfoHraca() {
	delete font;
	delete ukazovatel;
}



void StavInfoHraca::onEnter() {
	Stav::onEnter();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		stlacenaKlavesa = true;
	}
	oznacene = 1;
	hrac = hra->GetHrac();
	oblecene = hrac->Getstatistika()->Getoblecene();
	
}


void StavInfoHraca::onExit() {
	Stav::onExit();
}


void StavInfoHraca::render() {
		ukazovatel->setColor(sf::Color(255, 0, 0, 128));
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

		int xpTeraz = hrac->Getstatistika()->Getskusenosti();
		int xpNaDalsi = hrac->GetZameranie()->xpNaLevel(lvl+1);
		text.setCharacterSize(15U);
		text.setString(" Skusenosti: " + std::to_string(xpTeraz) + " / " + std::to_string(xpNaDalsi));
		text.setPosition(sf::Vector2f(15.f, 135.f));
		okno->draw(text);


		int hpTeraz = hrac->Getstatistika()->Gethp();
		int hpMax = hrac->Getstatistika()->GethpMax();
		text.setString(" Hp: " + std::to_string(hpTeraz) + " / " + std::to_string(hpMax));
		text.setPosition(sf::Vector2f(15.f, 152.f));
		okno->draw(text);

		int mpTeraz = hrac->Getstatistika()->Getmp();
		int mpMax = hrac->Getstatistika()->GetmpMax();
		text.setString(" Mp: " + std::to_string(mpTeraz) + " / " + std::to_string(mpMax));
		text.setPosition(sf::Vector2f(15.f, 170.f));
		okno->draw(text);

		int stat = hrac->Getstatistika()->Getsila();
		text.setString(" Sila: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 187.f));
		okno->draw(text);

		stat = hrac->Getstatistika()->Getintelekt();
		text.setString(" Intelekt: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 204.f));
		okno->draw(text);

		stat = hrac->Getstatistika()->Getrychlost();
		text.setString(" Rychlost: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 221.f));
		okno->draw(text);
		
		stat = hrac->Getstatistika()->Getobrana();
		text.setString(" Obrana: " + std::to_string(stat));
		text.setPosition(sf::Vector2f(15.f, 238.f));
		okno->draw(text);

		int pMin = hrac->Getstatistika()->Getminposkodenie();
		int pMax = hrac->Getstatistika()->Getmaxposkodenie();
		text.setString(" Poskodenie: " + std::to_string(pMin) + " / " + std::to_string(pMax));
		text.setPosition(sf::Vector2f(15.f, 255.f));
		okno->draw(text);

		// vykreslovanie oblecenych veci

		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(48, 48));

		sf::Sprite* predmetObrazok;
		int x = 20;
		int y = 280;

		//helma
		rectangle.setPosition(x + 0.f, y + 0.f);
		okno->draw(rectangle);
		
		if(oblecene->count(1)){
			predmetObrazok = oblecene->at(1)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
			
		}
		//ramena
		rectangle.setPosition(x + 0.f, y + 60.f);
		okno->draw(rectangle);
		
		if (oblecene->count(2)) {
			predmetObrazok = oblecene->at(2)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		//brnenie
		rectangle.setPosition(x+0.f, y + 120.f);
		okno->draw(rectangle);
		
		if (oblecene->count(3)) {
			predmetObrazok = oblecene->at(3)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		//nohavice
		rectangle.setPosition(x+0.f, y + 180.f);
		okno->draw(rectangle);
		
		if (oblecene->count(4)) {
			predmetObrazok = oblecene->at(4)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		//nahrdelnik
		rectangle.setPosition(x+200.f, y + 0.f);
		okno->draw(rectangle);
		if (oblecene->count(5)) {
			predmetObrazok = oblecene->at(5)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		//prsten
		rectangle.setPosition(x + 200.f, y+60.f);
		okno->draw(rectangle);
		if (oblecene->count(6)) {
			predmetObrazok = oblecene->at(6)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		//rukavice
		rectangle.setPosition(x + 200.f, y + 120.f);
		okno->draw(rectangle);
		if (oblecene->count(7)) {
			predmetObrazok = oblecene->at(7)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		//topanky
		rectangle.setPosition(x + 200.f, y + 180.f);
		okno->draw(rectangle);
		if (oblecene->count(8)) {
			predmetObrazok = oblecene->at(8)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		//zbran v lavej
		rectangle.setPosition(x + 70.f, y + 180.f);
		okno->draw(rectangle);
		if (oblecene->count(9)) {
			predmetObrazok = oblecene->at(9)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}
		//zbran v pravej
		rectangle.setPosition(x + 130.f, y + 180.f);
		okno->draw(rectangle);
		if (oblecene->count(10)) {
			predmetObrazok = oblecene->at(10)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(rectangle.getPosition());
			okno->draw(*predmetObrazok);
		}

		
		// oznacenie a info predmetu
		switch (oznacene)
		{
		case (1) :
			ukazovatel->setPosition(x + 0.f, y + 0.f);
			okno->draw(*ukazovatel);
			if(oblecene->count(1))  vykresliOknoPredmetu(oblecene->at(1), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (2) :
			ukazovatel->setPosition(x + 0.f, y + 60.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(2)) vykresliOknoPredmetu(oblecene->at(2), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (3) :
			ukazovatel->setPosition(x + 0.f, y + 120.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(3)) vykresliOknoPredmetu(oblecene->at(3), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (4) :
			ukazovatel->setPosition(x + 0.f, y + 180.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(4)) vykresliOknoPredmetu(oblecene->at(4), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (5) :
			ukazovatel->setPosition(x + 200.f, y + 0.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(5)) vykresliOknoPredmetu(oblecene->at(5), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (6) :
			ukazovatel->setPosition(x + 200.f, y + 60.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(6)) vykresliOknoPredmetu(oblecene->at(6), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (7) :
			ukazovatel->setPosition(x + 200.f, y + 120.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(7)) vykresliOknoPredmetu(oblecene->at(7), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (8) :
			ukazovatel->setPosition(x + 200.f, y + 180.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(8)) vykresliOknoPredmetu(oblecene->at(8), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (9) :
			ukazovatel->setPosition(x + 70.f, y + 180.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(9)) vykresliOknoPredmetu(oblecene->at(9), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		case (10) :
			ukazovatel->setPosition(x + 130.f, y + 180.f);
			okno->draw(*ukazovatel);
			if (oblecene->count(10)) vykresliOknoPredmetu(oblecene->at(10), ukazovatel->getPosition().x, ukazovatel->getPosition().y, okno);
			break;
		default:
			break;
		}

	//std::cout << oznacene << std::endl;
}


void StavInfoHraca::update(double delta) {

	if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		stlacenaKlavesa = true;
		if(oznacene < 10){
		oznacene++;
		}
		else {
			oznacene = 1;
		}
		
	}

	if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		stlacenaKlavesa = true;
		if (oznacene >1) {
			oznacene--;
		}
		else {
			oznacene = 10;
		}
	}

	if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		stlacenaKlavesa = true;
		if (oblecene->count(oznacene)) {
			oblecene->at(oznacene)->pouzi(hrac);
		}
	}



	if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::C))) {
		hra->zmenStavRozhrania("hranieHry");
	}

	if (stlacenaKlavesa 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::C) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		stlacenaKlavesa = false;
	}
}


void StavInfoHraca::vykresliOknoPredmetu(Predmet*predmet, float x, float y, sf::RenderWindow* okno) {

	// vykreslenie obdlznika na ktorom sa bude vypisovat info predmetu 
	sf::RectangleShape obdlznik;
	obdlznik.setSize(sf::Vector2f(230.f, 200.f));// vyska a sirka okienka
	obdlznik.setOutlineColor(sf::Color::Red);
	obdlznik.setOutlineThickness(2);


	float posX, posY;
	posX = x - 5.f+48;
	posY = y - 5.f+48;

	
	obdlznik.setPosition(posX, posY);
	okno->draw(obdlznik);

	// tu už je samotny vypis infa
	sf::Text text(predmet->Getmeno(), *font, 14U);

	text.setColor(sf::Color::Black);

	if (hrac->Getstatistika()->dajUroven() < predmet->Geturoven()) text.setColor(sf::Color::Red);

	text.setPosition(sf::Vector2f(posX + 10.f, posY + 5.f));
	okno->draw(text);


	text.setCharacterSize(10U);
	text.setString(predmet->Getstringovytyp());
	text.setPosition(sf::Vector2f(posX + 5.f, posY + 23.f));
	okno->draw(text);


	text.setString("Potrebna uroven: " + std::to_string(predmet->Geturoven()));
	text.setPosition(sf::Vector2f(posX + 5.f, posY + 35.f));
	okno->draw(text);

		text.setColor(sf::Color::Black);
		text.setCharacterSize(13U);
		Pouzitelny* pouzitelny = (Pouzitelny*)predmet;
		std::string bonusy = "";

		if (dynamic_cast<Zbran*>(predmet) != NULL)
		{
			Zbran* pom = (Zbran*)predmet;
			if (pom->Gettyp() != 11) {
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

		if (pouzitelny->Gethp() != 0) {
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
			bonusy += std::to_string((int)round(pouzitelny->GetmpMult() * 100));
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
