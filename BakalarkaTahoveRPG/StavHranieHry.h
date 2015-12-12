#pragma once


#include "Stav.h"
class Mapa;

class StavHranieHry : public Stav
{

public:
	StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra,Mapa* mapa);
	virtual ~StavHranieHry();

	void onEnter();
	void onExit();
	void render();
	void Setmapa(Mapa* newVal);
	void update(double delta);
	Mapa* getMapa();

private:
	Mapa* mapa;
	int posHracaX;
	int posHracaY;

};

