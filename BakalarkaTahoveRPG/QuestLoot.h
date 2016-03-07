#pragma once

#include "Quest.h"
class QuestLoot
	:public Quest
{
public:
	QuestLoot(std::string paMeno,std::string paPopis, std::string paMenoPredmetu, int pocetKs, int pocetXp, int pocetZlata);
	~QuestLoot();
	void zabitieNpc(Nepriatel* nepriatel);
	void dokonciSa(Hrac* paHrac);
	void lootnutiePredmetu(Predmet* paPredmet);
	void kontrola();
	std::string coZbierat();
	std::string getPopis();
private:
	int potrebneMnozstvo;
	std::string menoPredmetu;
};

