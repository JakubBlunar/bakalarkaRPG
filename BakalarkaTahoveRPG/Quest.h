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

/// <summary>
/// Enum predstavuje stav questu
/// </summary>
enum StavQuestu {
	NEPRIJATY = 0,
	ROZROBENY = 1,
	SPLNENIE_POZIADAVIEK = 2,
	DOKONCENY = 3,
};

/// <summary>
/// Quest ktor� mo�e hra� prija� a potom plni�
/// </summary>
class Quest
{
public:

	/// <summary>
	/// Vytvor� nov� quest
	/// </summary>
	/// <param name="paNazov">nazov questu</param>
	/// <param name="paPopis">popis questu</param>
	/// <param name="pocetXp">pocet xp ktor� hrac dostane za splnenie</param>
	/// <param name="pocetZlata">pocet zlata ktor� hr�c dostane za splnenie</param>
	/// <param name="paStartNpc">meno zaciatocneho npc</param>
	/// <param name="paEndNpc">meno konciaceho npc</param>
	/// <param name="nazovSuboru">nazov suboru v ktorom je ulozeny quest</param>
	/// <param name="autoAccept">ci sa quest automaticky prijme</param>
	Quest(string paNazov, string paPopis, int pocetXp, int pocetZlata, string paStartNpc, string paEndNpc, string nazovSuboru,bool autoAccept);
	~Quest();

	/// <summary>
	/// Metoda ktor� v�etk�m po�iadavkam odo�le informaciu �e bol zabit� tento nepriate�
	/// </summary>
	/// <param name="nepriatel">zabit� nepriate�</param>
	void zabitieNpc(Nepriatel* nepriatel);

	/// <summary>
	/// Metoda ktor� v�etk�m po�iadavkam odo�le informaciu �e bol zobran�  predmet
	/// </summary>
	/// <param name="paPredmet">predmet ktor� bol zobran�</param>
	void lootnutiePredmetu(Predmet* paPredmet);

	/// <summary>
	/// Metoda ktor� skontroluje �i u� quest nie je splnen�
	/// </summary>
	void kontrola();

	/// <summary>
	/// Vr�ti popis questu , kompletn� stav
	/// </summary>
	/// <returns>popis questu</returns>
	string getPopis() const;

	/// <summary>
	/// Dokoncenie questu , pridanie odmien 
	/// </summary>
	/// <param name="hrac">hrac ktor� dokoncil quest</param>
	void dokonciSa(Hrac* hrac);

	/// <summary>
	/// Nastavi stav questu na dan� stav
	/// </summary>
	/// <param name="paStav">nova hodnota stavu questu</param>
	void setStav(StavQuestu paStav);

	/// <summary>
	/// Vrati stav questu
	/// </summary>
	/// <returns>stav questu</returns>
	StavQuestu Getstav() const;

	/// <summary>
	/// Vr�ti nazov questu
	/// </summary>
	/// <returns>nazov questu</returns>
	string Getnazov() const;

	/// <summary>
	/// prida odmenu do zoznamu odmien
	/// </summary>
	/// <param name="paPredmet">predmet ktor� je ako nova odmena</param>
	void pridajOdmenu(Predmet* paPredmet) const;

	/// <summary>
	/// Vrati popis odmeny
	/// </summary>
	/// <returns>popis odmeny</returns>
	string GetpopisOdmeny() const;
	
	/// <summary>
	/// Prida poziadavku do zoznamu poziadaviek
	/// </summary>
	/// <param name="poziadavka">nova poziadavka</param>
	void pridajPoziadavku(Poziadavka* poziadavka) const;

	/// <summary>
	/// Nastavi predchadzajuci quest
	/// </summary>
	/// <param name="paQuest">predchadzajuci quest</param>
	void Setpredchadzajuci(Quest* paQuest);

	/// <summary>
	/// Nastavi nasledujuci quest na novu hodnotu
	/// </summary>
	/// <param name="paQuest">nasledujuci quest</param>
	void Setnasledujuci(Quest* paQuest);

	/// <summary>
	/// Vr�ti nasledujuci quest
	/// </summary>
	/// <returns>quest</returns>
	Quest* Getnasledujuci() const;

	/// <summary>
	/// Vr�ti predch�dzaj�ci quest
	/// </summary>
	/// <returns>predchadzajuci quest</returns>
	Quest* Getpredchadzajuci() const;

	/// <summary>
	/// Vrati meno npc u ktoreho quest zacina
	/// </summary>
	/// <returns>meno npc</returns>
	string Getstartnpc() const;

	/// <summary>
	/// Vrati meno npc u ktoreho quest konc�
	/// </summary>
	/// <returns>meno npc</returns>
	string Getendnpc() const;

	/// <summary>
	/// Vrati nazov suboru v ktorom je quest ulozen�
	/// </summary>
	/// <returns>nazov suboru</returns>
	string Getnazovsuboru() const;

	/// <summary>
	/// Polozka ktor� v dialogu bude oznamova� informacie o queste
	/// </summary>
	/// <param name="paPolozka">quest polozka ktor� spravuje quest</param>
	void SetdialogPolozka(QuestPolozka* paPolozka);

	/// <summary>
	/// Volba v dialogu ktor� bude smerova� ku quest polozke s t�mto questom
	/// </summary>
	/// <param name="paVolba">quest volba ku questu</param>
	void SetvolbaKuQuestu(DialogVolba* paVolba);

	/// <summary>
	/// Vrati polozku ktor� spravuje quest
	/// </summary>
	/// <returns>Quest polozka questu</returns>
	QuestPolozka* GetdialogPolozka() const;

	/// <summary>
	/// Vrati volbu ku questu , ked si ju hrac vyberie tak sa mu zobrazi quest polozka
	/// </summary>
	/// <returns>volba ku questu</returns>
	DialogVolba* GetvolbaKuQuestu() const;
	
	/// <summary>
	/// Vr�ti poziadavky ktor� quest vyzaduje
	/// </summary>
	/// <returns>zoznam poziadaviek</returns>
	vector<Poziadavka*>* Getpoziadavky() const;

	/// <summary>
	/// Ci sa quest automaticky prida po skon�en� predchadzajuceho
	/// </summary>
	/// <returns></returns>
	bool Getautoaccept() const;
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

	bool autoAccept;

	string nazovSuboru;

	QuestPolozka* dialogPolozka;
	DialogVolba* volbaKuQuestu;

};

#endif