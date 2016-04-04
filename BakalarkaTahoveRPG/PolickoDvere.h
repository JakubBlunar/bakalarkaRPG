#pragma once
#include "Policko.h"

class Hrac;

class PolickoDvere: public Policko
{
public:
	/// <summary>
	/// Vytvorí nove policko a nastavi mu priechodnost podla parametra
	/// </summary>
	/// <param name="paPriechodne">ci je policko priechodne</param>
	/// <param name="kam">meno mapy na ktoru bude hrac presunuty</param>
	/// <param name="posX">pozicia x na ktorom policku sa objavi</param>
	/// <param name="posY">pozicia y na ktorom policku sa objavi</param>
	/// <param name="smerPohladu">ako bude hrac otoceny</param>
	PolickoDvere(bool paPriechodne,std::string kam, int posX, int posY, int smerPohladu);
	~PolickoDvere();
	
	/// <summary>
	/// Teleportuje hraca na ine miesto podla atributov
	/// </summary>
	/// <param name="paHrac"></param>
	void hracSkok(Hrac* paHrac) override;

private:
	std::string menoMapy;
	int poziciaX;
	int poziciaY;
	int smerPohladu;
};

