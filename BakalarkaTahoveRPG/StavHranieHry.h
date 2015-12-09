#pragma once


#include "Stav.h"
class Mapa;


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
	Mapa* mapa;
	int posHracaX;
	int posHracaY;



};

