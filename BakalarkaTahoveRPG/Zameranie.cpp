#include "Zameranie.h"
#include <map>
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

std::map<std::string, int> Zameranie::lvlUpBonusy(){
	std::map<std::string, int> bonusy;
	bonusy.insert(std::pair<std::string, int>("hpMax", (int)rastHp));
	bonusy.insert(std::pair<std::string, int>("mpMax", (int)rastMp));
	bonusy.insert(std::pair<std::string, int>("sila", (int)rastSila));
	bonusy.insert(std::pair<std::string, int>("intel", (int)rastIntel));
	bonusy.insert(std::pair<std::string, int>("rychlost", (int)rastRychlost));
	return bonusy;
}


void Zameranie::vlozAkciu(Akcia* paAkcia, int paUroven) {
	spelly->insert(std::pair <Akcia*, int>(paAkcia, paUroven));
}

std::map<Akcia*, int>*  Zameranie::Getspelly() {
	return spelly;
}
