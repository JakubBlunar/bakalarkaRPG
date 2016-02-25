#include "EfektUpravStat.h"
#include "Statistika.h"


EfektUpravStat::EfektUpravStat(std::string obrazok,std::string paCo, int paOkolko):Efekt(obrazok)
{
	this->co = paCo;
	this->zakladOkolko = paOkolko;
}


EfektUpravStat::~EfektUpravStat()
{
	Efekt::~Efekt();
}

void EfektUpravStat::aplikujSa(Statistika* statistika) {
	statistika->zvysStat(zakladOkolko, co);
}

void EfektUpravStat::zrusUcinok(Statistika* statistika) {
	statistika->zvysStat(-zakladOkolko, co);
}

int EfektUpravStat::hodnotaEfektu() {
	return zakladOkolko;
}

std::string EfektUpravStat::popis() {
	//sila
	if (  co== "sila") {
		if (hodnotaEfektu() > 0) {
			return "Zvysi silu o " + std::to_string(hodnotaEfektu());
		}
		else {
			return "Znizi silu o " + std::to_string(-hodnotaEfektu());
		}
	}

	if (co == "hpMax") {
		if (hodnotaEfektu() > 0) {
			return "Zvysi maxHp o " + std::to_string(hodnotaEfektu());
		}
		else {
			return "Znizi maxHp o " + std::to_string(-hodnotaEfektu());
		}
	}

	//intel
	if (co == "intel") {
		if (hodnotaEfektu() > 0) {
			return "Zvysi intelekt o " + std::to_string(hodnotaEfektu());
		}
		else {
			return "Znizi intelekt o " + std::to_string(-hodnotaEfektu());
		}
	}

	//rychlost
	if (co == "rychlost") {
		if (hodnotaEfektu() > 0) {
			return "Zvysi rychlost o " + std::to_string(hodnotaEfektu());
		}
		else {
			return "Znizi rychlost o " + std::to_string(-hodnotaEfektu());
		}
	}

	//obrana
	if (co == "obrana") {
		if (hodnotaEfektu() > 0) {
			return "Zvysi obranu o " + std::to_string(hodnotaEfektu());
		}
		else {
			return "Znizi obranu o " + std::to_string(-hodnotaEfektu());
		}
	}

	else return "neznamy efekt";
}