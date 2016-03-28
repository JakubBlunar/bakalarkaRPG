#if !defined(boj_h)
#define boj_h

#include <map>
#include <deque>
#include "Timer.h"

using namespace std;

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
	string Getlog(int paOd, int paDo);
	Nepriatel* Getnepriatel();
private:
	Hrac* hrac;
	Akcia* hracAkcia;
	map<Akcia*, int> hracCooldowny;
	int hracCasVykonaniaAkcie;

	Nepriatel* npc;
	Akcia* npcAkcia;
	int npcCasVykonaniaAkcie;
	map<Akcia*, int> npcCooldowny;

	bool vyber;
	Timer casovac;
	bool koniec;
	bool boloVyhodnotenie;
	void vyhodnotenie();
	deque<string> logBoja;

};
#endif
