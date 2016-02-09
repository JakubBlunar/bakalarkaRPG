#pragma once
#include <string>
#include <map>

class Akcia;

class Zameranie
{

public:
	Zameranie(std::string nazov, double paRastHp, double paRastMp, double paRastSila, double paRastRychlost, double paRastIntel);
	virtual ~Zameranie();

	std::string Getnazov();
	double GetrastHp();
	double GetrastMp();
	double GetrastIntel();
	double GetrastRychlost();
	double GetrastSila();
	int xpNaLevel(int level);
	void vlozAkciu(Akcia* paAkcia, int paUroven);
	std::map<std::string, int> lvlUpBonusy();
	std::map<Akcia*, int>  Getspelly();

private:
	std::string nazov;
	double rastHp;
	double rastMp;
	double rastIntel;
	double rastRychlost;
	double rastSila;
	std::map<Akcia*, int>  spelly;

};

