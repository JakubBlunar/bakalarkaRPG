#include "Statistika.h"


Statistika::Statistika() {
	uroven = 1;
	hp = 10;
	hpMax = 10;
	mp = 10;
	mpMax = 10;
	sila = 5;
	intelekt = 5;
	obrana = 5;
	rychlost = 5;
	obrana = 0;
}



Statistika::~Statistika() {

}





int Statistika::dajUroven() {

	return uroven;
}


int Statistika::Gethp() {

	return hp;
}


int Statistika::GethpMax() {

	return hpMax;
}


int Statistika::Getintelekt() {

	return intelekt;
}


int Statistika::Getmp() {

	return mp;
}

int Statistika::GetmpMax() {

	return mpMax;
}



int Statistika::Getobrana() {

	return obrana;
}


int Statistika::Getrychlost() {

	return rychlost;
}


int Statistika::Getsila() {

	return sila;
}


int Statistika::Getskusenosti() {

	return skusenosti;
}


void Statistika::Sethp(int novaHodnota) {

	hp = novaHodnota;
}


void Statistika::SethpMax(int novaHodnota) {

	hpMax = novaHodnota;
}


void Statistika::Setintelekt(int novaHodnota) {

	intelekt = novaHodnota;
}


void Statistika::Setmp(int novaHodnota) {

	mp = novaHodnota;
}


void Statistika::Setobrana(int novaHodnota) {

	obrana = novaHodnota;
}


void Statistika::Setrychlost(int novaHodnota) {

	rychlost = novaHodnota;
}


void Statistika::Setsila(int novaHodnota) {

	sila = novaHodnota;
}


void Statistika::Setskusenosti(int novaHodnota) {
	skusenosti = novaHodnota;
}


int Statistika::xpNaLevel(int level) {

	return (int)round((5 * (level * level * level)) / 6);
}

void Statistika::pridajXp(int pocet) {
	int xpnalevel = xpNaLevel(uroven + 1);
	skusenosti += pocet;
	if (skusenosti >= xpnalevel) {
		uroven++;
	}
}

void Statistika::zvysStat(int kolko, std::string paCo) {

	//hp
	if (paCo == "hp") {
		hp += kolko;
	}

	//hpMax
	if (paCo == "hpMax") {
		hpMax += kolko;
	}

	//mp
	if (paCo == "mp") {
		mp += kolko;
	}

	//mpMax
	if (paCo == "mpMax") {
		mpMax += kolko;
	}

	//sila
	if (paCo == "sila") {
		sila += kolko;
	}

	//intel
	if (paCo == "intel") {
		intelekt += kolko;
	}

	//rychlost
	if (paCo == "rychlost") {
		rychlost += kolko;
	}

	//obrana
	if (paCo == "obrana") {
		obrana += kolko;
	}
	
}