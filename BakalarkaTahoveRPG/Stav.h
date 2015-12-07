#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Hra;

class Stav
{

public:
	Stav(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra);
	virtual ~Stav();
	virtual void update(double delta);
	virtual void render();
	virtual void onEnter();
	virtual void onExit();
	std::string Getnazov();
	void Setnazov(std::string paNazov);
protected:
	std::string nazov;
	sf::RenderWindow* okno;
	Hra* hra;
};
