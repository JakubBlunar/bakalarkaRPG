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

int QuestOdmena::Getpocetxp() const
{
	return pocetXp;
}

int QuestOdmena::Getpocetzlata() const
{
	return pocetZlata;
}

vector<Predmet*>* QuestOdmena::getPredmety() const
{
	return predmety;
}

void QuestOdmena::pridajPredmet(Predmet* paPredmet) const
{
	predmety->push_back(paPredmet);
}
