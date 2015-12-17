#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;
class Inventar;

class StavInventar : public Stav
{

public:
	StavInventar(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavInventar();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

private:
	sf::Font* font;
	bool stlacenaKlavesa;
	

	int oznacene;
	sf::Sprite* ukazovatel;

	Inventar* inventar;
	Hrac* hrac;
};