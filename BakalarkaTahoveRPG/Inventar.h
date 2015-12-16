#pragma once

#if !defined(inventar_h)
#define inventar_h

#include <string>
#include "Predmet.h"


class Inventar
{

public:
	Inventar();
	virtual ~Inventar();

	bool maDostatokZlata(int aktualneZlato);
	int pocetPredmetov(std::string meno);
	void pridajPredmet(Predmet* predmet);
	void vyberPredmet(Predmet* predmet);
	void zdviholPredemt(Predmet* paPredmet);

private:
	int pocetZlata;
	std::vector<Predmet*> predmety;

};
#endif 
