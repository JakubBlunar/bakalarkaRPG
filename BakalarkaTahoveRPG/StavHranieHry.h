#pragma once
#include "Stav.h"
#include <vector>

class Mapa;
class Hrac;
class Predmet;

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
	void zobrazLoot();
	Mapa* mapa;
	Hrac* hrac;
	int posHracaX;
	int posHracaY;

	std::vector<Predmet*>* loot;
	int lootIndex;
};

