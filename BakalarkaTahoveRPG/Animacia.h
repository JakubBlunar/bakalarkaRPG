#pragma once

#include <SFML/Graphics.hpp>

class Animacia
{

public:
	Animacia(std::string cesta, int pocetObrazkov, int trvanie, int velkost);
	virtual ~Animacia();

	sf::Sprite* dajObrazok();
	void reset();
	void tick();

private:
	int aktObrazok;
	sf::Texture textura;
	sf::Sprite* obrazok;
	int pocetObrazkov;
	int trvanie;
	int trvanieCounter;
	int velkostTextury;

};

