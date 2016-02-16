#pragma once
#include <vector>
#include <iostream>
#include "Stav.h"


class Zameranie;

class StavVolbaZamerania : public Stav
{

public:
	StavVolbaZamerania(std::string paNazov,sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavVolbaZamerania();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);
private:
	signed int oznacene;
};
