#include "StavDialog.h"

#include "Hra.h"
#include "Hrac.h"
#include "DialogovyStrom.h"
#include <string>
#include "Npc.h"


StavDialog::StavDialog(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font2.otf");
	dialog = nullptr;
	npc = nullptr;
	oznacene = 0;
}


StavDialog::~StavDialog() {
	delete(font);
}



void StavDialog::onEnter() {
	Stav::onEnter();
	oznacene = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		stlacenaKlavesa = true;
	}
}


void StavDialog::Setdialog(Npc* npc) {
	this->npc = npc;
	dialog = npc->Getdialog();
}



void StavDialog::onExit() {
	Stav::onExit();
}


void StavDialog::render() {

	int startX = 20;
	int startY = 70;

	if (dialog != nullptr) {

		sf::Text text(npc->Getmeno() +"(npc): " + dialog->Getaktualnapolozka()->text, *font, 25U);
		text.setPosition(sf::Vector2f(10.f, 10.f));
		okno->draw(text);

		text.setCharacterSize(20U);
		for (int i = 0; i < dialog->Getaktualnapolozka()->dialogoveMoznosti.size(); i++) {
			if (oznacene == i) {
				text.setColor(sf::Color::Blue);
			}
			else {
				text.setColor(sf::Color::White);
			}
			text.setString(std::to_string(i)+ ". " +dialog->Getaktualnapolozka()->dialogoveMoznosti[i].text);
			text.setPosition(sf::Vector2f(32.f, i*25 +40.f));
			okno->draw(text);
		}

	}
	//std::cout << oznacene << std::endl;
}


void StavDialog::update(double delta) {

	if (dialog == nullptr) {
		hra->zmenStavRozhrania("hranieHry");
	}

	if (dialog->Getstav() == DialogStav::BEZI) {

		if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			stlacenaKlavesa = true;
			if (oznacene < dialog->Getaktualnapolozka()->dialogoveMoznosti.size()) {
				oznacene++;
			}
		}

		if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			stlacenaKlavesa = true;
			if (oznacene > 0) oznacene--;
		}

		if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			stlacenaKlavesa = true;
			dialog->zmenPolozku(oznacene);
			oznacene = 0;
		}
	}
	else {
			stlacenaKlavesa = true;
			hra->zmenStavRozhrania("hranieHry");
	}

	if (stlacenaKlavesa
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
		) {
		stlacenaKlavesa = false;
	}

}
