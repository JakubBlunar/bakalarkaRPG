#include "AkciaPridanieEfektu.h"

#include "Statistika.h"
#include "Efekt.h"
#include "EfektUpravStat.h"

AkciaPridanieEfektu::AkciaPridanieEfektu(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana, Efekt* efekt, bool naHraca)
	:Akcia(meno,obrazok,casCastenia,cooldown,trvanie,popis,mana,AkciaTyp::FYZICKA)
{
	this->efekt = efekt;
	this->hrac = naHraca;
}


AkciaPridanieEfektu::~AkciaPridanieEfektu()
{
	delete efekt;
	Akcia::~Akcia();
}

std::string AkciaPridanieEfektu::vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas){
	Akcia::vykonajSa(statHrac, statNepriatel,aktCas);
	if (hrac) {
		statHrac->pridajEfekt(efekt, aktCas + sf::milliseconds(trvanie));
		return meno + " aplikoval na npc efekt\n    " + efekt->popis(statHrac);
	}
	else {
		statNepriatel->pridajEfekt(efekt, aktCas + sf::milliseconds(trvanie));
		return meno + " aplikoval na hraca efekt\n    " + efekt->popis(statNepriatel);
	}
}

std::string AkciaPridanieEfektu::dajPopis(Statistika* stat) {
	return popis+ "\n"+efekt->popis(stat);
}