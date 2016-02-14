#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;
class Predmet;
class Akcia;
class Tlacidlo;

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
	void vykresliOknoPredmetu(Predmet*predmet, float x, float y, sf::RenderWindow* okno);
	
	sf::Font* font;
	bool stlacenaKlavesa;
	bool stlacenaMys;

	int oznacene;
	sf::Sprite* ukazovatel;

	Hrac* hrac;
	std::map<int, Predmet*>* oblecene;
	std::vector<Akcia*> hracoveAkcie;

	std::vector<Tlacidlo*> tlacidlaAkcie;

	Akcia* akciaInfo;
};