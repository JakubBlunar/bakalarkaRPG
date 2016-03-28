#pragma once
#include <string>
#include <map>

class Akcia;

class Zameranie
{

public:
	Zameranie(std::string nazov, int paRastHp, int paRastMp, int paRastSila, int paRastRychlost, int paRastIntel);
	virtual ~Zameranie();

	std::string Getnazov() const;
	int GetrastHp() const;
	int GetrastMp() const;
	int GetrastIntel() const;
	int GetrastRychlost() const;
	int GetrastSila() const;
	int xpNaLevel(int level) const;
	void vlozAkciu(Akcia* paAkcia, int paUroven) const;
	std::map<std::string, int> lvlUpBonusy(int lvl) const;
	std::map<Akcia*, int>*  Getspelly() const;

private:
	std::string nazov;
	int rastHp;
	int rastMp;
	int rastIntel;
	int rastRychlost;
	int rastSila;
	std::map<Akcia*, int>*  spelly;

	int statFunkcia(int lvl,int zaklad) const;
};

