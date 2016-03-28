#pragma once
#include "Policko.h"

class Hrac;

class PolickoDvere: public Policko
{
public:
	PolickoDvere(bool paPriechodne,std::string kam, int posX, int posY, int smerPohladu);
	~PolickoDvere();
	
	void hracSkok(Hrac* paHrac) override;

private:
	std::string menoMapy;
	int poziciaX;
	int poziciaY;
	int smerPohladu;
};

