#include "AkciaLiecenie.h"
#include "Statistika.h"
#include <random>



AkciaLiecenie::AkciaLiecenie(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana, AkciaTyp typ, int paZakladnyHeal):Akcia(meno, obrazok, casCastenia, cooldown, trvanie, popis, mana, typ)
{
	this->zakladnyHeal = paZakladnyHeal;
}


AkciaLiecenie::~AkciaLiecenie()
{
}


bool AkciaLiecenie::vykonajSa(Statistika* statHrac, Statistika* statNepriatel) {
	Akcia::vykonajSa(statHrac, statNepriatel);

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> uni(minLiecenie(statHrac), maxLiecenie(statHrac));
	int healing = uni(generator);

	statHrac->zvysStat(healing, "hp");
	return true;
}

int AkciaLiecenie::minLiecenie(Statistika* statistika) {
	/*int stat;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return (int)ceil(0.7*stat* zakladnyHeal);
	*/
	return 10;
}

int AkciaLiecenie::maxLiecenie(Statistika* statistika) {
	/*int stat;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return (int)ceil(1.3*stat* zakladnyHeal);*/
	return 20;
}