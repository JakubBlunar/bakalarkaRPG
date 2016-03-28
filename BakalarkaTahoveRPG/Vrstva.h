#pragma once
#include <SFML\Graphics.hpp>

class Vrstva
{

public:
	Vrstva(int velkost);
	Vrstva(sf::Texture paTextura,int paVelkost);
	virtual ~Vrstva();

	sf::Sprite* Getobrazok() const;
	void Setobrazok(sf::Texture* textura) const;
	void Setpriechodna(bool newVal);

private:
	sf::Sprite* obrazok;
	int velkost;

};
