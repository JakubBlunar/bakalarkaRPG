#include "Statistika.h"
#include <map>
#include <math.h>
#include "Predmet.h"
#include "Pouzitelny.h"
#include "Zbran.h"

Statistika::Statistika() {
	akcie = new std::map<std::string, Akcia*>();
	uroven = 1;
	hp = 20;
	hpMax = 80;
	mp = 10;
	mpMax = 10;
	sila = 1;
	intelekt = 1;
	obrana = 1;
	rychlost = 1;
	obrana = 0;
	skusenosti = 0;
	oblecene = new std::map<int, Predmet*>();
	prepocitajPoskodenia();
	
}

Statistika::Statistika(int paUroven, int paHp, int paHpMax, int paMp, int paMpMax, int paSila, int paIntelekt, int paRychlost, int paObrana,std::map<int, Predmet*>* paObleceneVeci) {
	skusenosti = 0;
	uroven = paUroven;
	hp = paHp;
	hpMax = paHpMax;
	mp = paMp;
	mpMax = paMpMax;
	sila = paSila;
	intelekt = paIntelekt;
	rychlost = paRychlost;
	obrana = paObrana;
	oblecene = paObleceneVeci;
	akcie = new std::map<std::string, Akcia*>();
	this->prepocitajPoskodenia();
}


Statistika::~Statistika() {
	delete oblecene;
}


int Statistika::dajUroven() {

	return uroven;
}


int Statistika::Gethp() {
	return hp;
}


int Statistika::GethpMax() {
	int bonus = 0;
	double mult = 0;

	typedef std::map<int, Predmet*>::iterator it_t;

	for (it_t it = oblecene->begin(); it != oblecene->end(); ++it)
	{
		Pouzitelny* p = (Pouzitelny*)it->second;
		bonus += p->Gethp();
		mult += p->GethpMult();
	}
	return (int)round((hpMax+bonus)*(1+mult));
}


int Statistika::Getintelekt() {

	int bonus = 0;
	double mult = 0;

	typedef std::map<int, Predmet*>::iterator it_t;

	for (it_t it = oblecene->begin(); it != oblecene->end(); ++it)
	{
		Pouzitelny* p = (Pouzitelny*)it->second;
		bonus += p->Getinteligencia();
		mult += p->GetinteligenciaMult();
	}
	return (int)round((intelekt + bonus)*(1 + mult));
}


int Statistika::Getmp() {

	return mp;
}

int Statistika::GetmpMax() {

	int bonus = 0;
	double mult = 0;

	typedef std::map<int, Predmet*>::iterator it_t;

	for (it_t it = oblecene->begin(); it != oblecene->end(); ++it)
	{
		Pouzitelny* p = (Pouzitelny*)it->second;
		bonus += p->Getmp();
		mult += p->GetmpMult();
	}
	return (int)round((mpMax + bonus)*(1 + mult));
}



int Statistika::Getobrana() {

	int bonus = 0;
	double mult = 0;

	typedef std::map<int, Predmet*>::iterator it_t;

	for (it_t it = oblecene->begin(); it != oblecene->end(); ++it)
	{
		Pouzitelny* p = (Pouzitelny*)it->second;
		bonus += p->Getarmor();
		mult += p->GetarmorMult();
	}
	return (int)round((obrana + bonus)*(1 + mult));
}


int Statistika::Getrychlost() {

	int bonus = 0;
	double mult = 0;

	typedef std::map<int, Predmet*>::iterator it_t;

	for (it_t it = oblecene->begin(); it != oblecene->end(); ++it)
	{
		Pouzitelny* p = (Pouzitelny*)it->second;
		bonus += p->Getrychlost();
		mult += p->GetrychlostMult();
	}
	return (int)round((rychlost + bonus)*(1 + mult));
}


int Statistika::Getsila() {

	int bonus = 0;
	double mult = 0;

	typedef std::map<int, Predmet*>::iterator it_t;

	for (it_t it = oblecene->begin(); it != oblecene->end(); ++it)
	{
		Pouzitelny* p = (Pouzitelny*)it->second;
		bonus += p->Getsila();
		mult += p->GetsilaMult();
	}
	return (int)round((sila + bonus)*(1 + mult));
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

void Statistika::pridajXp(int pocet) {
	skusenosti += pocet;
}

void Statistika::zvysStat(int kolko, std::string paCo) {

	//hp
	if (paCo == "hp") {
		if (hp + kolko > hpMax) {
			hp = hpMax;
		}
		else {
			hp += kolko;
		}
		
	}

	//hpMax
	if (paCo == "hpMax") {
		hpMax += kolko;
	}

	//mp
	if (paCo == "mp") {
		if (mp + kolko > mpMax) {
			mp = mpMax;
		}
		else {
			mp += kolko;
		}
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

void Statistika::setUroven(int paUroven) {
	uroven = paUroven;
}

std::map<int, Predmet*>* Statistika::Getoblecene() {
	return oblecene;
}

std::map<std::string, Akcia*>* Statistika::Getakcie() {
	return akcie;
}

void Statistika::prepocitajPoskodenia() {
	if (oblecene->count(9)) {
		Zbran* zbran1 =(Zbran*)oblecene->at(9);
		if (oblecene->count(10)) {
			Zbran* zbran2 = (Zbran*)oblecene->at(10);
			double sucet = zbran1->Getminposkodenie() + 0.75*zbran2->Getmaxposkodenie();
			minPoskodenie = (int)round(sucet + sucet*(0.1 * sila / uroven));

			sucet = zbran1->Getmaxposkodenie() + 0.75*zbran2->Getmaxposkodenie();
			maxPoskodenie = (int)round(sucet + sucet*(0.1 * sila / uroven));
		}
		else {
			minPoskodenie = (int)round(zbran1->Getminposkodenie() + zbran1->Getminposkodenie()*(0.1 * sila / uroven));
			maxPoskodenie = (int)round(zbran1->Getmaxposkodenie() + zbran1->Getmaxposkodenie()*(0.1 * sila / uroven));
		}
	}
	else {
		minPoskodenie = (int)ceil((sila / (double)uroven));
		maxPoskodenie = (int)ceil((sila / (double)uroven));
	}

}

int Statistika::Getminposkodenie() {
	return minPoskodenie;
}
int Statistika::Getmaxposkodenie() {
	return maxPoskodenie;
}