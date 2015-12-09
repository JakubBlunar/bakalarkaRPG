#pragma once

#include <SFML/Graphics.hpp>

//#include "Hrac.h"
#include <string>

class Stav;
class Hrac;
class StavRozhrania;

class Hra
{

public:
	Hra();
	virtual ~Hra();
	
	StavRozhrania* stavRozhraniaHry;
	sf::RenderWindow* okno;
	void start();
	void hlavnaSlucka();
	void zmenStavRozhrania(std::string paStav);
	void SetHrac(Hrac* paHrac);
	Hrac* GetHrac();
	Stav* dajStav(std::string stav);
private:
	Hrac* hrac;
};

