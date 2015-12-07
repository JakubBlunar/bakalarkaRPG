#pragma once

#include <SFML/Graphics.hpp>

//#include "Hrac.h"


class StavRozhrania;

class Hra
{

public:
	Hra();
	virtual ~Hra();
	//Hrac *m_Hrac;
	StavRozhrania* stavRozhraniaHry;
	sf::RenderWindow* okno;
	void start();
	void hlavnaSlucka();
	void zmenStavRozhrania(std::string paStav);

private:
	
};

