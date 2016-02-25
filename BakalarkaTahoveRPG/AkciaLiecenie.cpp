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


std::string AkciaLiecenie::vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas) {
	Akcia::vykonajSa(statHrac, statNepriatel, aktCas);

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> uni(minLiecenie(statHrac), maxLiecenie(statHrac));
	int healing = uni(generator);
	statHrac->zvysStat(healing, "hp");
	return meno + " - lieci sa za " + std::to_string(healing);
}

int AkciaLiecenie::minLiecenie(Statistika* statistika) {
	int stat;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return (int)ceil(0.7*stat* zakladnyHeal);
}

int AkciaLiecenie::maxLiecenie(Statistika* statistika) {
	int stat;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return (int)ceil(1.3*stat* zakladnyHeal);
}