#include "AkciaPridanieEfektu.h"

#include "Statistika.h"
#include "Efekt.h"

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

std::string AkciaPridanieEfektu::vykonajSa(Statistika* stat1, Statistika* stat2, sf::Time aktCas){
	Akcia::vykonajSa(stat1, stat2,aktCas);
	if (hrac) {
		stat1->pridajEfekt(efekt, aktCas + sf::milliseconds(trvanie));
		return meno + " apply effect \n    " + efekt->popis();
	}
	else {
		stat2->pridajEfekt(efekt, aktCas + sf::milliseconds(trvanie));
		return meno + " apply effect on enemy\n    " + efekt->popis();
	}
}

std::string AkciaPridanieEfektu::dajPopis() {
	return popis+ "\n"+ efekt->popis();
}

void AkciaPridanieEfektu::setStatistika(Statistika* statistika) const
{
	efekt->Setstatistikanapocitanie(statistika);
}
