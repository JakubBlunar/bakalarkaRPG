#if !defined(Quest_h)
#define Quest_h

#include <string>
#include <vector>

using namespace std;

class QuestOdmena;
class Nepriatel;
class Hrac;
class Predmet;
class Poziadavka;

enum StavQuestu {
	NEPRIJATY = 0,
	ROZROBENY = 1,
	SPLNENIE_POZIADAVIEK = 2,
	DOKONCENY = 3,
};

class Quest
{
public:
	void zabitieNpc(Nepriatel* nepriatel);
	void lootnutiePredmetu(Predmet* paPredmet);
	void kontrola();
	string getPopis();
	void dokonciSa(Hrac* hrac);
	void setStav(StavQuestu paStav);
	StavQuestu Getstav();
	string Getnazov();
	void pridajOdmenu(Predmet* paPredmet);
	string GetpopisOdmeny();
	Quest(string paNazov, string paPopis, int pocetXp, int pocetZlata);
	void pridajPoziadavku(Poziadavka* poziadavka);
protected:
	
	
	vector <Poziadavka* > poziadavky;
	string nazov;
	StavQuestu stav;
	string popis;
	QuestOdmena* odmena;
};

#endif