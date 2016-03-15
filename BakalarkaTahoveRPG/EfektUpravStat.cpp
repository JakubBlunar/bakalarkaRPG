#include "EfektUpravStat.h"
#include "Statistika.h"


EfektUpravStat::EfektUpravStat(std::string obrazok,std::string paCo, int paZaklad):Efekt(obrazok)
{
	this->co = paCo;
	this->zakladOkolko = paZaklad;
}


EfektUpravStat::~EfektUpravStat()
{
	Efekt::~Efekt();
}

void EfektUpravStat::aplikujSa(Statistika* statistika) {
	statistika->zvysStat(hodnotaEfektu(), co);
}

void EfektUpravStat::zrusUcinok(Statistika* statistika) {
	statistika->zvysStat(-hodnotaEfektu(), co);
}

int EfektUpravStat::hodnotaEfektu() {
	if (zakladOkolko > 0) {
		return (int)floor(floor((2 * zakladOkolko) * statistikaNaPocitanie->dajUroven() / 100 )) + 1;
	}
	else if (zakladOkolko < 0) {
		return (int)floor(floor((2 * zakladOkolko) * statistikaNaPocitanie->dajUroven() / 100)) -1;
	}
	else return 1;
}

std::string EfektUpravStat::popis() {
	//sila
	int hodnota = hodnotaEfektu();
	if (  co== "sila") {
		
		if (hodnota > 0) {
			return "Zvysi silu o " + std::to_string(hodnota);
		}
		else {
			return "Znizi silu o " + std::to_string(-hodnota);
		}
	}

	if (co == "hpMax") {
		if (hodnota > 0) {
			return "Zvysi maxHp o " + std::to_string(hodnota);
		}
		else {
			return "Znizi maxHp o " + std::to_string(-hodnota);
		}
	}

	//intel
	if (co == "intel") {
		if (hodnota > 0) {
			return "Zvysi intelekt o " + std::to_string(hodnota);
		}
		else {
			return "Znizi intelekt o " + std::to_string(-hodnota);
		}
	}

	//rychlost
	if (co == "rychlost") {
		if (hodnota > 0) {
			return "Zvysi rychlost o " + std::to_string(hodnota);
		}
		else {
			return "Znizi rychlost o " + std::to_string(-hodnota);
		}
	}

	//obrana
	if (co == "obrana") {
		if (hodnota > 0) {
			return "Zvysi obranu o " + std::to_string(hodnota);
		}
		else {
			return "Znizi obranu o " + std::to_string(-hodnota);
		}
	}

	else return "neznamy efekt";
}