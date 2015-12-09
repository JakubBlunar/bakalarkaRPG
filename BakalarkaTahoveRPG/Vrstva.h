#pragma once
#include <SFML\Graphics.hpp>

class Vrstva
{

public:
	Vrstva(int velkost);
	Vrstva(sf::Texture paTextura,int paVelkost);
	virtual ~Vrstva();

	sf::Sprite* Getobrazok();
	void Setobrazok(sf::Texture* textura);
	void Setpriechodna(bool newVal);

private:
	sf::Sprite* obrazok;
	int velkost;

};
