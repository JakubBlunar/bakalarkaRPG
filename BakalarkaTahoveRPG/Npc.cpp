#include "Npc.h"
#include "Hrac.h"
#include "Animacia.h"
#include <iostream>

Npc::Npc(std::string paMeno) {
	meno = paMeno;
}



Npc::~Npc() {
	delete animacia;
}





sf::Sprite* Npc::dajObrazok() {
	return animacia->dajObrazok();
}


void Npc::dialog(Hrac* hrac) {
	std::cout << "Spustenie dialogu" << std::endl;
}


void Npc::update() {

}

void Npc::Setanimacia(Animacia* animacia) {
	this->animacia = animacia;
}