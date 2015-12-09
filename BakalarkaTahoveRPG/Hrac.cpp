#include "Hrac.h"
#include "Zameranie.h"
#include "Animacia.h"
#include <iostream>

Hrac::Hrac(Zameranie* paZameranie) {
	zameranie = paZameranie;
	std::cout << "Hrac vytvoreny" << std::endl;
	animaciaDole = new Animacia("Data/Grafika/Hrac/Animacia/hrac_dole.png", 4, 10,32);
	animaciaHore = new Animacia("Data/Grafika/Hrac/Animacia/hrac_hore.png", 4, 10, 32);
	animaciaVlavo = new Animacia("Data/Grafika/Hrac/Animacia/hrac_vlavo.png", 4, 10, 32);
	animaciaVpravo = new Animacia("Data/Grafika/Hrac/Animacia/hrac_vpravo.png", 4, 10, 32);
	smerPohladu = SmerPohladu::dole;
	

}



Hrac::~Hrac() {
	delete(zameranie);
	std::cout << "Hrac zmazany" << std::endl;
}





void Hrac::posunSa(int kam) {

}


void Hrac::render(sf::RenderWindow* paOkno) {

	sf::Sprite* obrazok;
	if (smerPohladu == hore) {
		obrazok = animaciaHore->dajObrazok();
	}

	if (smerPohladu == dole) {
		obrazok = animaciaDole->dajObrazok();
	}

	if (smerPohladu == vlavo) {
		obrazok = animaciaVlavo->dajObrazok();
	}

	if (smerPohladu == vpravo) {
		obrazok = animaciaVpravo->dajObrazok();
	}

	obrazok->setPosition(sf::Vector2f(0, 0));

	paOkno->draw(*obrazok);
}


void Hrac::update(double delta) {


	if (smerPohladu == hore) {
		animaciaHore->tick();
	}

	if (smerPohladu == dole) {
		animaciaDole->tick();
	}

	if (smerPohladu == vlavo) {
		animaciaVlavo->tick();
	}

	if (smerPohladu == vpravo) {
		animaciaVpravo->tick();
	}




}

void Hrac::zmenSmerPohladu(SmerPohladu paSmer) {
	smerPohladu = paSmer;

	if (smerPohladu == hore) {
		animaciaHore->reset();
	}

	if (smerPohladu == dole) {
		animaciaDole->reset();
	}

	if (smerPohladu == vlavo) {
		animaciaVlavo->reset();
	}

	if (smerPohladu == vpravo) {
		animaciaVpravo->reset();
	}

	
}



int Hrac::GetoffsetX() {
	return offsetX;
}

int Hrac::GetoffsetY() {
	return offsetY;
}

int Hrac::GetpolickoX() {
	return polickoX;
}

int Hrac::GetpolickoY() {
	return polickoY;
}