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
	Quest(string paNazov, string paPopis, int pocetXp, int pocetZlata, string paStartNpc, string paEndNpc, string nazovSuboru);
	~Quest();
	void zabitieNpc(Nepriatel* nepriatel);
	void lootnutiePredmetu(Predmet* paPredmet);
	void kontrola();
	string getPopis();
	void dokonciSa(Hrac* hrac);
	void setStav(StavQuestu paStav);
	StavQuestu Getstav() const;
	string Getnazov() const;
	void pridajOdmenu(Predmet* paPredmet) const;
	string GetpopisOdmeny() const;
	
	void pridajPoziadavku(Poziadavka* poziadavka) const;

	void Setpredchadzajuci(Quest* paQuest);
	void Setnasledujuci(Quest* paQuest);
	Quest* Getnasledujuci() const;
	Quest* Getpredchadzajuci() const;
	string Getstartnpc() const;
	string Getendnpc() const;
	string Getnazovsuboru() const;

	void SetdialogPolozka(QuestPolozka* paPolozka);
	void SetvolbaKuQuestu(DialogVolba* paVolba);

	QuestPolozka* GetdialogPolozka() const;
	DialogVolba* GetvolbaKuQuestu() const;

	vector<Poziadavka*>* Getpoziadavky() const;

private:
	Quest* predchadzajuci;
	Quest* nasledujuci;
	vector <Poziadavka* >* poziadavky;
	string nazov;
	StavQuestu stav;
	string popis;
	QuestOdmena* odmena;

	string startNpc = "";
	string endNpc = "";

	

	string nazovSuboru;

	QuestPolozka* dialogPolozka;
	DialogVolba* volbaKuQuestu;

};

#endif