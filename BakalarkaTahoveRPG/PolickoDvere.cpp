#include "PolickoDvere.h"
#include "Hrac.h"
#include "Hra.h"
#include <iostream>
#include <string>
#include "Mapa.h"
#include "StavHranieHry.h"
#include "Loader.h"

PolickoDvere::PolickoDvere(bool paPriechodne, std::string kam, int posX,int posY,int smerPohladu):Policko(paPriechodne)
{
	this->hra = hra;
	this->menoMapy = kam;
	this->poziciaX = posX;
	this->poziciaY = posY;
	this->smerPohladu = smerPohladu;
}


PolickoDvere::~PolickoDvere()
{
	
}

void PolickoDvere::hracSkok(Hrac* paHrac) {
	
	/*StavHranieHry* stav = (StavHranieHry*)hra->dajStav("hranieHry");
	Mapa* mapa = new Mapa(menoMapy, hra->GetHrac(), hra, poziciaX, poziciaY, smerPohladu);
	hra->GetHrac()->setMapa(mapa);
	stav->Setmapa(mapa);*/

	Loader* loader = Loader::Instance();
	loader->nacitajMapu(menoMapy, poziciaX, poziciaY,smerPohladu);
	loader->Gethra()->zmenStavRozhrania("hranieHry");
	
}