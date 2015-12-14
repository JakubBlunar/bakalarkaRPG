#pragma once


#if !defined(statistika_h)
#define statistika_h

#include <string>

//#include "Akcia.h"



class Statistika
{

public:
	Statistika();
	virtual ~Statistika();
	//Akcia *m_Akcia;

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
	int xpNaLevel(int level);
	void zvysStat(int kolko, std::string paCo);
	void pridajXp(int pocet);

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

};
#endif 
