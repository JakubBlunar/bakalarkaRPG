#include "QuestOdmena.h"



QuestOdmena::QuestOdmena(int pocetXp, int pocetZlata)
{
	this->pocetXp = pocetXp;
	this->pocetZlata = pocetZlata;
	predmety = new vector<Predmet*>();
}


QuestOdmena::~QuestOdmena()
{
	delete predmety;
}

int QuestOdmena::Getpocetxp() {
	return pocetXp;
}

int QuestOdmena::Getpocetzlata() {
	return pocetZlata;
}

vector<Predmet*>* QuestOdmena::getPredmety() {
	return predmety;
}

void QuestOdmena::pridajPredmet(Predmet* paPredmet) {
	predmety->push_back(paPredmet);
}