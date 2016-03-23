#pragma once
#include "Stav.h"

class StavLoading:public Stav
{
public:
	StavLoading(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavLoading();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

};

