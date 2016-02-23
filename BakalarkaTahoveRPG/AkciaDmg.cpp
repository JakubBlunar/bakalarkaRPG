#include "AkciaDmg.h"
#include "Statistika.h"
#include <math.h>
#include <random>
#include <iostream>

AkciaDmg::AkciaDmg(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana,AkciaTyp typ,int paZakladnyDmg):Akcia(meno,obrazok,casCastenia,cooldown,trvanie,popis,mana,typ)
{
	this->zakladnyDmg =paZakladnyDmg;
}


AkciaDmg::~AkciaDmg()
{
}

bool AkciaDmg::vykonajSa(Statistika* statHrac, Statistika* statNepriatel) {
	Akcia::vykonajSa(statHrac,statNepriatel);
	
	std::random_device rd;  
	std::mt19937 generator(rd()); 
	std::uniform_int_distribution<int> uni(minPoskodenie(statHrac), maxPoskodenie(statHrac));
	int poskodenie = uni(generator);

	std::uniform_real_distribution<double> real(0, 1);
	double p = real(generator);
	
	if (p >= statNepriatel->Getsancanauhyb()) {
		statNepriatel->Sethp(statNepriatel->Gethp() - (int)ceil(poskodenie*(1 - statNepriatel->Getodolnostvociposkodeniu())));
	}
	else {
		std::cout << "miss " << std::endl;
	}
	return true;
}

int AkciaDmg::minPoskodenie(Statistika* statistika) {
	int stat;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return (int)ceil(0.7*stat* zakladnyDmg);
	
}

int AkciaDmg::maxPoskodenie(Statistika* statistika) {
	int stat;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return (int)ceil(1.3*stat* zakladnyDmg);
}