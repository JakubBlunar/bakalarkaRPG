#pragma once
#include <string>
#include <vector>
#include "Stav.h"

/**
* - nova hra, koniec, pokracovat
*/

class Tlacidlo;
class StavHlavneMenu : public Stav
{

public:
	StavHlavneMenu(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra);
	virtual ~StavHlavneMenu();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

private:
	sf::Font* font;
	std::vector<Tlacidlo*> tlacidla;
	signed int oznacene;
	bool stlacenaKlavesa;
	bool stlacenaMys;
};

