#include "AkciaPoskodenieZbranou.h"
#include "Statistika.h"
#include <map>
#include "Predmet.h"
#include <iostream>
#include <random>

AkciaPoskodenieZbranou::AkciaPoskodenieZbranou(std::string meno, std::string popis, Statistika* paStatistika):Akcia(meno,"ruka", 10000, 10000, 10000, popis, 0, AkciaTyp::FYZICKA)
{
	this->statistika = paStatistika;
}


AkciaPoskodenieZbranou::~AkciaPoskodenieZbranou()
{
}

int AkciaPoskodenieZbranou::GetcasCastenia() {
	return statistika->Getrychlostutoku();
}

int AkciaPoskodenieZbranou::Getcooldown() {
	return 0;
}

sf::Sprite* AkciaPoskodenieZbranou::Getobrazok() {
	if (statistika->Getoblecene()->count(9)) {
		return statistika->Getoblecene()->at(9)->Getobrazok();
	}
	else {
		return Akcia::Getobrazok();
	}
}

std::string AkciaPoskodenieZbranou::vykonajSa(Statistika* statHrac, Statistika* statNepriatel,sf::Time aktCas) {
	Akcia::vykonajSa(statHrac, statNepriatel,aktCas);

	std::random_device rd;
	std::mt19937 generator(rd());

	std::uniform_int_distribution<int> uni(minPoskodenie(), maxPoskodenie());
	int poskodenie = uni(generator);

	std::uniform_real_distribution<double> real(0, 1);
	double p = real(generator);

	if (p >= statNepriatel->Getsancanauhyb()) {
		int konecnePoskodenie = (int)ceil(poskodenie*(1 - statNepriatel->Getodolnostvociposkodeniu()));
		statNepriatel->Sethp(statNepriatel->Gethp() - konecnePoskodenie);
		return meno + " - utoci s poskodenim " + std::to_string(konecnePoskodenie);
	}
	else {
		return meno + " - miss.";
	}
}

int AkciaPoskodenieZbranou::minPoskodenie() {
	return statistika->Getminposkodenie();

}

int AkciaPoskodenieZbranou::maxPoskodenie() {
	return statistika->Getmaxposkodenie();
}

std::string AkciaPoskodenieZbranou::Getmeno() {
	if (statistika->Getoblecene()->count(9)) {
		return statistika->Getoblecene()->at(9)->Getmeno();
	}
	else {
		return Akcia::Getmeno()+ " holymi rukami";
	}
}