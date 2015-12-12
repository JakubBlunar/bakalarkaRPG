#pragma once
#include "Policko.h"

class Hrac;
class Hra;

class PolickoDvere: public Policko
{
public:
	PolickoDvere(bool paPriechodne,Hra* hra,std::string kam, int posX, int posY, int smerPohladu);
	~PolickoDvere();
	
	void hracSkok(Hrac* paHrac);

private:
	Hra* hra;
	std::string menoMapy;
	int poziciaX;
	int poziciaY;
	int smerPohladu;
};

