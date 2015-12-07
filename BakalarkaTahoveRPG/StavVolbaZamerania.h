#pragma once
#include <iostream>
#include "Stav.h"

class StavVolbaZamerania : public Stav
{

public:
	StavVolbaZamerania(std::string paNazov,sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavVolbaZamerania();

	void onEnter();
	void onExit();
	void render(sf::RenderWindow* okno);
	void update(double delta);
private:
	sf::Font* font;
	signed int oznacene;
	bool stlacenaKlavesa;

};
