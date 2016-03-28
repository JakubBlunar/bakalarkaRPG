#pragma once

#include <SFML/Graphics.hpp>

//#include "Hrac.h"
#include <string>

class Stav;
class Hrac;
class StavRozhrania;
class Loader;

class Hra
{

public:
	Hra();
	virtual ~Hra();
	
	StavRozhrania* stavRozhraniaHry;
	sf::RenderWindow* okno;
	void start();
	void hlavnaSlucka();
	void zmenStavRozhrania(std::string paStav) const;
	void SetHrac(Hrac* paHrac);
	Hrac* GetHrac() const;
	Stav* dajStav(std::string stav) const;
	bool maFocus() const;

private:
	Hrac* hrac;
	Loader* loader;
	sf::Clock clock;
	void init();

	bool focus;

};

