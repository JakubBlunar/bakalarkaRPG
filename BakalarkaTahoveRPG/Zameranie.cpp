#include "Zameranie.h"


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

/*
map<Akcie, int>  Zameranie::Getspelly() {

	return spelly;
}

*/