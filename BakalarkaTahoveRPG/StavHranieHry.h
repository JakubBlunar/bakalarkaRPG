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

	void onEnter() override;
	void onExit() override;
	void render() override;
	void Setmapa(Mapa* newVal);
	void update(double delta) override;
	Mapa* getMapa();

private:
	void zobrazLoot();
	Mapa* mapa;
	Hrac* hrac;

	std::vector<Predmet*>* loot;
	int lootIndex;
};

