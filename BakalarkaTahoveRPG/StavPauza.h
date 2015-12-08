#pragma once
#include "Stav.h"

class StavPauza : public Stav
{

public:
	StavPauza(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavPauza();

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
