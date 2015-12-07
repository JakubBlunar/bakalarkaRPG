#pragma once
#include <string>
#include "Stav.h"

/**
* - nova hra, koniec, pokracovat
*/
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
	std::vector<std::string> moznosti;
	signed int oznacene;
	bool stlacenaKlavesa;
};

