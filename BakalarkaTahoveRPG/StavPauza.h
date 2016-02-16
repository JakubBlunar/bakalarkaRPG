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
	std::vector<std::string> moznosti;
	signed int oznacene;
};
