#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;
class Inventar;
class Predmet;

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

	void vykresliOknoPredmetu(Predmet* predmet, int x, int y, sf::RenderWindow* okno);
	sf::Font* font;
	bool stlacenaKlavesa;
	

	int oznacene;
	sf::Sprite* ukazovatel;
	int nasirku;

	Inventar* inventar;
	Hrac* hrac;
};