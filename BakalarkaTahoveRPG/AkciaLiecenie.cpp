#include "AkciaLiecenie.h"
#include "Statistika.h"
#include <random>

#include "AudioManager.h"

AkciaLiecenie::AkciaLiecenie(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana, AkciaTyp typ, double paZakladnyHeal):Akcia(meno, obrazok, casCastenia, cooldown, trvanie, popis, mana, typ)
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
	AudioManager::Instance()->playEfekt("healing");
	return meno + " - heal by " + std::to_string(healing);
}

int AkciaLiecenie::minLiecenie(Statistika* statistika) const
{
	int stat = 0;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return static_cast<int>(floor(0.9*floor(2 * stat + statistika->dajUroven() / 5 + 1) * zakladnyHeal));
}

int AkciaLiecenie::maxLiecenie(Statistika* statistika) const
{
	int stat = 0;
	if (typ == AkciaTyp::FYZICKA) {
		stat = statistika->Getsila();
	}
	else if (typ == AkciaTyp::MAGICKA) {
		stat = statistika->Getintelekt();
	}
	return static_cast<int>(floor(1.3*floor(2 * stat + statistika->dajUroven() / 5 + 1) * zakladnyHeal));
}
