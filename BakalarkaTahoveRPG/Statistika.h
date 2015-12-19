#pragma once


#if !defined(statistika_h)
#define statistika_h

#include <string>
#include <map>
//#include "Akcia.h"

class Predmet;


class Statistika
{

public:
	Statistika();
	virtual ~Statistika();
	//Akcia *m_Akcia;

	std::map<int, Predmet*>* Getoblecene();

	int dajUroven();
	int Gethp();
	int GethpMax();
	int Getintelekt();
	int Getmp();
	int GetmpMax();
	int Getobrana();
	int Getrychlost();
	int Getsila();
	int Getskusenosti();
	void Sethp(int novaHodnota);
	void SethpMax(int novaHodnota);
	void Setintelekt(int novaHodnota);
	void Setmp(int novaHodnota);
	void Setobrana(int novaHodnota);
	void Setrychlost(int novaHodnota);
	void Setsila(int novaHodnota);
	void Setskusenosti(int novaHodnota);
	void zvysStat(int kolko, std::string paCo);
	void pridajXp(int pocet);
	void setUroven(int paUroven);

private:
	int hp;
	int hpMax;
	int intelekt;
	int mp;
	int mpMax;
	int obrana;
	int rychlost;
	int sila;
	int skusenosti;
	int uroven;
	//std::Map<string, Akcia*> kuzla;
	std::map<int, Predmet*>* oblecene;
};
#endif 
