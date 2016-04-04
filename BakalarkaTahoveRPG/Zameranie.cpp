#include "Zameranie.h"
#include <map>
#include <math.h>
#include "Akcia.h"

#include <iostream>

Zameranie::Zameranie(std::string nazov, int paRastHp, int paRastMp, int paRastSila, int paRastRychlost, int paRastIntel) {
	this->nazov = nazov;
	rastHp = paRastHp;
	rastMp = paRastMp;
	rastSila = paRastSila;
	rastRychlost = paRastRychlost;
	rastIntel = paRastIntel;
	spelly = new std::map<Akcia*, int>();
}



Zameranie::~Zameranie() {
	delete spelly;
}


std::string Zameranie::Getnazov() const
{
	return nazov;
}


int Zameranie::xpNaLevel(int level) const
{
	return static_cast<int>(round((7 * (level * level * level)) / 6));
}

std::map<std::string, int> Zameranie::lvlUpBonusy(int lvl) const
{
	std::map<std::string, int> bonusy;
	bonusy.insert(std::pair<std::string, int>("hpMax", statFunkcia(lvl,rastHp)));
	bonusy.insert(std::pair<std::string, int>("mpMax", statFunkcia(lvl, rastMp)));
	bonusy.insert(std::pair<std::string, int>("sila", statFunkcia(lvl, rastSila)));
	bonusy.insert(std::pair<std::string, int>("intel", statFunkcia(lvl, rastIntel)));
	bonusy.insert(std::pair<std::string, int>("rychlost", statFunkcia(lvl, rastRychlost)));
	return bonusy;
}


void Zameranie::vlozAkciu(Akcia* paAkcia, int paUroven) const
{
	spelly->insert(std::pair <Akcia*, int>(paAkcia, paUroven));
}

std::map<Akcia*, int>*  Zameranie::Getspelly() const
{
	return spelly;
}


int Zameranie::statFunkcia(int lvl, int zaklad) const
{
	return static_cast<int>(floor(floor((2 * zaklad) * lvl / 100 + 5)));
}
