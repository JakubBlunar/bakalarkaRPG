#pragma once


#include "Stav.h"

class StavHranieHry : public Stav
{

public:
	StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavHranieHry();

	void onEnter();
	void onExit();
	void render();
	//void Setmapa(Mapa newVal);
	void update(double delta);

private:
	//Mapa mapa;

};

