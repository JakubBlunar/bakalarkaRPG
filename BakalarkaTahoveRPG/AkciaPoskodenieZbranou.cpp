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

bool AkciaPoskodenieZbranou::vykonajSa(Statistika* statHrac, Statistika* statNepriatel) {
	Akcia::vykonajSa(statHrac, statNepriatel);

	std::random_device rd;
	std::mt19937 generator(rd());

	std::uniform_int_distribution<int> uni(minPoskodenie(), maxPoskodenie());
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