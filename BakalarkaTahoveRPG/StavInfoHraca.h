#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;

class StavInfoHraca : public Stav
{

public:
	StavInfoHraca(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavInfoHraca();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

private:
	sf::Font* font;
	bool stlacenaKlavesa;

	Hrac* hrac;
};