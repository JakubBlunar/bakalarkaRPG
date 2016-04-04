#include "StavDialog.h"
#include "Hra.h"
#include "DialogovyStrom.h"
#include <string>
#include "Npc.h"
#include "AudioManager.h"


StavDialog::StavDialog(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {

	dialog = nullptr;
	npc = nullptr;
	oznacene = 0;
}


StavDialog::~StavDialog() {
}



void StavDialog::onEnter() {
	Stav::onEnter();
	oznacene = 0;
	stlacenaKlavesa = true;
}


void StavDialog::Setdialog(Npc* npc) {
	this->npc = npc;
	dialog = npc->Getdialog();
}



void StavDialog::onExit() {
	Stav::onExit();
}


void StavDialog::render() {

	if (dialog != nullptr) {

		sf::Text text(npc->Getmeno() +" (npc): " + dialog->Getaktualnapolozka()->Gettext(), *font, 28U);
		text.setPosition(sf::Vector2f(10.f, 10.f));
		okno->draw(text);

		float y = 15.f + text.getGlobalBounds().height;

		text.setCharacterSize(23U);
		for (int i = 0; i < dialog->Getaktualnapolozka()->pocetMoznosti(); i++) {
			if (oznacene == i) {
				text.setColor(sf::Color::Green);
			}
			else {
				text.setColor(sf::Color::White);
			}
			text.setString(std::to_string(i+1)+ ". " + dialog->Getaktualnapolozka()->Getvolba(i)->Gettext());
			text.setPosition(sf::Vector2f(32.f,y + i*25 +40.f));
			okno->draw(text);
		}

	}
	Stav::render();
}


void StavDialog::update() {

	if (hra->maFocus()) {

		Stav::update();

		if (stav == StavAkcia::NORMAL) {

			if (dialog == nullptr) {
				hra->zmenStavRozhrania("hranieHry");
			}

			if (dialog->Getstav() == DialogStav::BEZI) {

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					stlacenaKlavesa = true;
					if (oznacene < dialog->Getaktualnapolozka()->pocetMoznosti() - 1) {
						oznacene++;
						AudioManager::Instance()->playEfekt("klik");
					}
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					stlacenaKlavesa = true;
					if (oznacene > 0) {
						oznacene--;
						AudioManager::Instance()->playEfekt("klik");
					}
				}

				if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)|| sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
					stlacenaKlavesa = true;
					AudioManager::Instance()->playEfekt("vyber");
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
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::E)
				) {
				stlacenaKlavesa = false;
			}
		}
	}
}
