#pragma once
#include <SFML\Graphics.hpp>

class Vrstva
{

public:
	Vrstva(sf::Texture paTextura,bool paPriechodna,int paVelkost);
	virtual ~Vrstva();

	sf::Sprite* Getobrazok();
	bool Ispriechodna();
	void Setobrazok(sf::Texture textura);
	void Setpriechodna(bool newVal);

private:
	sf::Texture textura;
	sf::Sprite* obrazok;
	bool priechodna;
	int velkost;

};
