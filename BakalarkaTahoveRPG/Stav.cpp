
#include "Stav.h"
#include "Hra.h"
Stav::Stav(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) {
	nazov = paNazov;
	okno = paOkno;
	hra = paHra;
	
}



Stav::~Stav() {
}



void Stav::update(double delta) {
	std::cout << "Stav " << nazov << " update" << delta <<  std::endl;
}


void Stav::render() {
	
	std::cout << "Stav " << nazov << " render" << std::endl;
}


void Stav::onEnter() {
	std::cout << "Stav " << nazov << " on enter." << std::endl;
}


void Stav::onExit() {
	std::cout << "Stav " << nazov << " in exit." << std::endl;
}

std::string Stav::Getnazov() {
	return nazov;
}

void Stav::Setnazov(std::string paNazov) {
	nazov = paNazov;
}