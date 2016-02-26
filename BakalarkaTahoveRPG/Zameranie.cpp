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


std::string Zameranie::Getnazov() {

	return nazov;
}


int Zameranie::GetrastHp() {

	return rastHp;
}

int Zameranie::GetrastMp() {

	return rastMp;
}

int Zameranie::GetrastIntel() {

	return rastIntel;
}


int Zameranie::GetrastRychlost() {

	return rastRychlost;
}


int Zameranie::GetrastSila() {

	return rastSila;
}


int Zameranie::xpNaLevel(int level) {

	return (int)round((5 * (level * level * level)) / 6);
}

std::map<std::string, int> Zameranie::lvlUpBonusy(int lvl){
	std::map<std::string, int> bonusy;
	bonusy.insert(std::pair<std::string, int>("hpMax", statFunkcia(lvl,rastHp)));
	bonusy.insert(std::pair<std::string, int>("mpMax", statFunkcia(lvl, rastMp)));
	bonusy.insert(std::pair<std::string, int>("sila", statFunkcia(lvl, rastSila)));
	bonusy.insert(std::pair<std::string, int>("intel", statFunkcia(lvl, rastIntel)));
	bonusy.insert(std::pair<std::string, int>("rychlost", statFunkcia(lvl, rastRychlost)));
	return bonusy;
}


void Zameranie::vlozAkciu(Akcia* paAkcia, int paUroven) {
	spelly->insert(std::pair <Akcia*, int>(paAkcia, paUroven));
}

std::map<Akcia*, int>*  Zameranie::Getspelly() {
	return spelly;
}


int Zameranie::statFunkcia(int lvl, int zaklad) {
	return floor(floor((2 * zaklad) * lvl / 100 + 5));
}