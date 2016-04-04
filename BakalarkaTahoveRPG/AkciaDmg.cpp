#include "AkciaDmg.h"
#include "Statistika.h"
#include <math.h>
#include <cstdlib>
#include "AudioManager.h"

AkciaDmg::AkciaDmg(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana,AkciaTyp typ,double paZakladnyDmg)
	:Akcia(meno,obrazok,casCastenia,cooldown,trvanie,popis,mana,typ)
{
	this->zakladnyDmg =paZakladnyDmg;
}


AkciaDmg::~AkciaDmg()
{
	Akcia::~Akcia();
}

std::string AkciaDmg::vykonajSa(Statistika* stat1, Statistika* stat2, sf::Time aktCas) {
	Akcia::vykonajSa(stat1, stat2,aktCas);

	int minP = minPoskodenie(stat1);
	int maxP = maxPoskodenie(stat1);
	int poskodenie;
	if (minP != maxP) {
		poskodenie = minP + rand() % (maxP - minP);
	}
	else {
		poskodenie = minP;
	}

	if(typ == AkciaTyp::FYZICKA)
	{
		AudioManager::Instance()->playEfekt("fyzicka");
	}else
	{
		AudioManager::Instance()->playEfekt("magicka");
	}

	double p = rand()%100;
	if (p >= stat2->Getsancanauhyb()*100) {
		int konecnePoskodenie = static_cast<int>(ceil(poskodenie*(1 - stat2->Getodolnostvociposkodeniu())));
		stat2->Sethp(stat2->Gethp() - konecnePoskodenie);
		return meno + "\nattack dmg " + std::to_string(konecnePoskodenie);
	}
	else {
		return meno + "\nmiss.";
	}

	
	
}

int AkciaDmg::minPoskodenie(Statistika* statistika) const
{
	if (typ == AkciaTyp::FYZICKA) {
		return static_cast<int>(ceil(0.9*statistika->Getminposkodenie()*zakladnyDmg));
	}
	else {
		return static_cast<int>(floor(0.8*floor(2 * (statistika->Getintelekt() + statistika->dajUroven()) / 6 + 1) * zakladnyDmg));
	}
	
	
}

int AkciaDmg::maxPoskodenie(Statistika* statistika) const
{
	if (typ == AkciaTyp::FYZICKA) {
		return static_cast<int>(ceil(1.3*statistika->Getmaxposkodenie()*zakladnyDmg));
	}
	else{
		return static_cast<int>(floor(1.1*floor(2 * (statistika->Getintelekt()+ statistika->dajUroven()) / 6 + 1) * zakladnyDmg));
	}
	
}
