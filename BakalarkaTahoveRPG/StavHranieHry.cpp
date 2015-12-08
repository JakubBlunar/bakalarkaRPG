#include "StavHranieHry.h"
#include "Hra.h"
#include "Hrac.h"

StavHranieHry::StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra)
{

}


StavHranieHry::~StavHranieHry()
{
}


void StavHranieHry::onEnter() {
	Stav::onEnter();
}


void StavHranieHry::onExit() {
	Stav::onExit();
}


void StavHranieHry::render() {
	hra->GetHrac()->render(okno);
}

/*
void StavHranieHry::Setmapa(Mapa newVal) {

	mapa = newVal;
}
*/

void StavHranieHry::update(double delta) {

	
	Hrac* hrac = hra->GetHrac();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		hrac->zmenSmerPohladu(SmerPohladu::vlavo);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		hrac->zmenSmerPohladu(SmerPohladu::vpravo);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		hrac->zmenSmerPohladu(SmerPohladu::hore);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		hrac->zmenSmerPohladu(SmerPohladu::dole);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		hra->zmenStavRozhrania("stavPauza");
	}

	/*
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		stlacenaKlavesa = false;
	}
	*/

	hra->GetHrac()->update(delta);
}