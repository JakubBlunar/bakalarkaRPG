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
class QuestPolozka;
class DialogVolba;

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
	Quest(string paNazov, string paPopis, int pocetXp, int pocetZlata,string paStartNpc,string paEndNpc);
	void pridajPoziadavku(Poziadavka* poziadavka);

	void Setpredchadzajuci(Quest* paQuest);
	void Setnasledujuci(Quest* paQuest);
	Quest* Getnasledujuci();
	Quest* Getpredchadzajuci();
	string Getstartnpc();
	string Getendnpc();

	void SetdialogPolozka(QuestPolozka* paPolozka);
	void SetvolbaKuQuestu(DialogVolba* paVolba);

	QuestPolozka* GetdialogPolozka();
	DialogVolba* GetvolbaKuQuestu();

private:
	Quest* predchadzajuci;
	Quest* nasledujuci;
	vector <Poziadavka* > poziadavky;
	string nazov;
	StavQuestu stav;
	string popis;
	QuestOdmena* odmena;

	string startNpc = "";
	string endNpc = "";


	QuestPolozka* dialogPolozka;
	DialogVolba* volbaKuQuestu;

};

#endif