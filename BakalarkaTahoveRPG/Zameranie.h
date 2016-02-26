#pragma once
#include <string>
#include <map>

class Akcia;

class Zameranie
{

public:
	Zameranie(std::string nazov, int paRastHp, int paRastMp, int paRastSila, int paRastRychlost, int paRastIntel);
	virtual ~Zameranie();

	std::string Getnazov();
	int GetrastHp();
	int GetrastMp();
	int GetrastIntel();
	int GetrastRychlost();
	int GetrastSila();
	int xpNaLevel(int level);
	void vlozAkciu(Akcia* paAkcia, int paUroven);
	std::map<std::string, int> lvlUpBonusy(int lvl);
	std::map<Akcia*, int>*  Getspelly();

private:
	std::string nazov;
	int rastHp;
	int rastMp;
	int rastIntel;
	int rastRychlost;
	int rastSila;
	std::map<Akcia*, int>*  spelly;

	int statFunkcia(int lvl,int zaklad);
};

