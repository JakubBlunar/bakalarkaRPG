#pragma once
#include <string>
#include "Stav.h"

/**
* - nova hra, koniec, pokracovat
*/
class StavLoading: public Stav
{

public:
	StavLoading(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavLoading();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

private:
	sf::Font* font;
};

