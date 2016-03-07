#if !defined(Quest_h)
#define Quest_h

#include <string>

using namespace std;

class QuestOdmena;
class Nepriatel;
class Hrac;
class Predmet;

enum StavQuestu {
	NEPRIJATY = 0,
	ROZROBENY = 1,
	SPLNENIE_POZIADAVIEK = 2,
	DOKONCENY = 3,
};

class Quest
{
public:
	virtual void zabitieNpc(Nepriatel* nepriatel) = 0;
	virtual void lootnutiePredmetu(Predmet* paPredmet) = 0;
	virtual void kontrola() = 0;
	virtual string getPopis();
	virtual void dokonciSa(Hrac* hrac);
	void setStav(StavQuestu paStav);
	StavQuestu Getstav();
	string Getnazov();
	void pridajOdmenu(Predmet* paPredmet);
	string GetpopisOdmeny();
protected:
	Quest(string paNazov,string paPopis, int pocetXp, int pocetZlata);
	

	string nazov;
	StavQuestu stav;
	string popis;
	QuestOdmena* odmena;
};

#endif