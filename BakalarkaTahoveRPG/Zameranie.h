#pragma once
#include <string>

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
	//map<Akcie, int>  Getspelly();

private:
	std::string nazov;
	double rastHp;
	double rastMp;
	double rastIntel;
	double rastRychlost;
	double rastSila;
	//map<Akcie, int>  spelly;

};

