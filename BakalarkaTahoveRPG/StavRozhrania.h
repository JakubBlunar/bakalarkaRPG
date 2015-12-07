#pragma once
#include <map>
#include <iostream>

#include "Stav.h"

class StavRozhrania
{

public:
	StavRozhrania(Stav* pociatocnyStav);
	~StavRozhrania();

	void zmenMapu();
	void render(sf::RenderWindow* okno);
	void update(double cas);
	void pridajStav(Stav* stav);
	Stav* GetaktualnyStav();
	void zmenStav(std::string stav);
	Stav* dajStav(std::string stav);

private:
	std::map<std::string, Stav*> stavy;
	Stav* aktualnyStav;

};
