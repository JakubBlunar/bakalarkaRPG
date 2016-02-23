#if !defined(boj_h)
#define boj_h

#include <map>
#include "Timer.h"


class Akcia;
class Hrac;
class Nepriatel;
class Statistika;

class Boj
{

public:
	Boj(Hrac* paHrac, Nepriatel* paNpc);
	virtual ~Boj();

	void bojStart();
	bool koniecBoja();
	Statistika* Gethracovastatistika();
	Statistika* Getnpcstatistika();
	//vstupOdHraca();
	bool cakaNaVybratieAkcie();
	void hracVybralAkciu(Akcia* paAkcia);
	sf::Time Getcasvboji();
	void update();
	bool maAkciaCooldown(Akcia* paAkcia);
	float castBarProgres();
private:
	Hrac* hrac;
	Akcia* hracAkcia;
	std::map<Akcia*, int> hracCooldowny;
	int hracCasVykonaniaAkcie;
	//std::vector<Buff> hracBuffy;

	Nepriatel* npc;
	Akcia* npcAkcia;
	int npcCasVykonaniaAkcie;
	std::map<Akcia*, int> npcCooldowny;
	//std::vector<Buff> npcBuffy;
	bool vyber;

	Timer casovac;
	bool koniec;
	bool boloVyhodnotenie;
	void vyhodnotenie();
};
#endif
