#pragma once
#include "Quest.h"

class Hrac;

class QuestKill :
	public Quest
{
public:
	QuestKill(std::string paNazov,std::string paPopis, std::string paKohoZabit, int paKolkokrat, int pocetXp, int pocetZlata);
	~QuestKill();
	void zabitieNpc(Nepriatel* nepriatel);
	void dokonciSa(Hrac* paHrac);
	void lootnutiePredmetu(Predmet* paPredmet);
	void kontrola();
	std::string getPopis();
private:
	int kolkoZabit;
	std::string kohoZabit;
	int pocetZabiti;

};

