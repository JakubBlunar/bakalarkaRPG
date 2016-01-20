#pragma once


#if !defined(statistika_h)
#define statistika_h

#include <string>
#include <map>

class Predmet;
class Akcia;

class Statistika
{

public:
	Statistika();
	Statistika(int paUroven, int paHp, int paHpMax, int paMp, int mpMax,int paSila, int paIntelekt, int paRychlost, int paObrana,std::map<int, Predmet*>* paObleceneVeci);
	virtual ~Statistika();

	std::map<int, Predmet*>* Getoblecene();
	std::map<std::string, Akcia*>* Getakcie();

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

	void prepocitajPoskodenia();
	int Getminposkodenie();
	int Getmaxposkodenie();
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
	int minPoskodenie;
	int maxPoskodenie;

	std::map<std::string, Akcia*>* akcie;
	std::map<int, Predmet*>* oblecene;
};
#endif 
