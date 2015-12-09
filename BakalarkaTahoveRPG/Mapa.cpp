#include "Mapa.h"
#include "Policko.h"
#include <iostream>

Mapa::Mapa() {
	sf::Texture* textura = new sf::Texture();
	if (!textura->loadFromFile("Data/Grafika/Mapa/Textury/trava1.png", sf::IntRect(0, 0, 32, 32))) {
		std::cout << "Chyba nahravania textury policka" << std::endl;
	}



	int rozmer = 25;

	for (int i = 0; i < rozmer; i++)
	{
		for (int j = 0; j < rozmer; j++)
		{
			mapa[i][j] = new Policko(true);
			mapa[i][j]->nastavTexturu(textura, 0);
		}
	}

}



Mapa::~Mapa() {
	
}





void Mapa::posun(int posunX, int posunY) {
	this->posunX += posunX;
	this->posunY += posunY;

}


void Mapa::render(sf::RenderWindow* okno) {
	sf::Sprite* sprite;

	for (int vrstva = 0; vrstva < 4; vrstva++) {

		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				sprite = mapa[i][j]->dajObrazokVrstvy(vrstva);
				sprite->setPosition(sf::Vector2f(32 * i + posunX, 32 * j+posunY));
				okno->draw(*sprite);
			}
		}
	}
	
}


void Mapa::update() {

}