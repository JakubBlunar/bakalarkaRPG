#include "Zameranie.h"
#include <map>
#include "Akcia.h"

Zameranie::Zameranie(std::string nazov, double paRastHp, double paRastMp, double paRastSila, double paRastRychlost, double paRastIntel) {
	this->nazov = nazov;
	rastHp = paRastHp;
	rastMp = paRastMp;
	rastSila = paRastSila;
	rastRychlost = paRastRychlost;
	rastIntel = paRastIntel;
}



Zameranie::~Zameranie() {
	
}


std::string Zameranie::Getnazov() {

	return nazov;
}


double Zameranie::GetrastHp() {

	return rastHp;
}

double Zameranie::GetrastMp() {

	return rastMp;
}

double Zameranie::GetrastIntel() {

	return rastIntel;
}


double Zameranie::GetrastRychlost() {

	return rastRychlost;
}


double Zameranie::GetrastSila() {

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
	spelly.insert_or_assign(paAkcia, paUroven);
}

std::map<Akcia*, int>  Zameranie::Getspelly() {
	return spelly;
}
