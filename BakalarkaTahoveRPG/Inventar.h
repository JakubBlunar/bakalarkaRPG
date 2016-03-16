#pragma once

#if !defined(inventar_h)
#define inventar_h

#include <string>
#include "Predmet.h"


class Inventar
{

public:
	Inventar(int kapacita = 36);
	virtual ~Inventar();

	int Getzlato();
	void Setzlato(int paPocet);
	void pridajZlato(int paPocet);
	bool maDostatokZlata(int aktualneZlato);
	
	int Getkapacita();
	void Setkapacita(int paNova);
	int pocetPredmetov(std::string meno);
	int pocetPredmetov();
	void pridajPredmet(Predmet* predmet,bool loot = true);
	void zmazPredmet(Predmet* predmet);
	void zmazPredmet(std::string paNazovPredmetu);
	Predmet* dajPredmetNaIndexe(int i);

private:
	int kapacita;
	int pocetZlata;
	std::vector<Predmet*> predmety;

};
#endif 
