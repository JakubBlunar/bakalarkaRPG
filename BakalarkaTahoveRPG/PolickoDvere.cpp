#include "PolickoDvere.h"
#include "Hrac.h"
#include "Hra.h"
#include "Loader.h"

PolickoDvere::PolickoDvere(bool paPriechodne, std::string kam, int posX,int posY,int smerPohladu):Policko(paPriechodne)
{
	this->menoMapy = kam;
	this->poziciaX = posX;
	this->poziciaY = posY;
	this->smerPohladu = smerPohladu;
}


PolickoDvere::~PolickoDvere()
{
	
}

void PolickoDvere::hracSkok(Hrac* paHrac) {

	Loader* loader = Loader::Instance();
	loader->nacitajMapu(menoMapy, poziciaX, poziciaY,smerPohladu);
	loader->Gethra()->zmenStavRozhrania("hranieHry");
	
}