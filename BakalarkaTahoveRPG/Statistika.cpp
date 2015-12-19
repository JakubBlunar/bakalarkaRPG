#include "Statistika.h"
#include <map>
#include <math.h>
#include "Predmet.h"
#include "Pouzitelny.h"

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
	skusenosti = 0;
	oblecene = new std::map<int, Predmet*>();
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
	return (int)round((sila + bonus)*(1 + mult));
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

void Statistika::setUroven(int paUroven) {
	uroven = paUroven;
}

std::map<int, Predmet*>* Statistika::Getoblecene() {
	return oblecene;
}