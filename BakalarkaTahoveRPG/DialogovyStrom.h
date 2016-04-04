#if !defined(DialogovyStrom_h)
#define DialogovyStrom_h


#include <string>
#include <vector>

using namespace std;

class Quest;
class Hrac;
/// <summary>
/// Stav dialogu
/// </summary>
enum DialogStav { VYTVORENY, INIT, BEZI, SKONCIL };

class DialogPolozka;

/// <summary>
/// Trieda ktor· reprezentuje volbu , ktoru si moûe hr·Ë vybraù
/// </summary>
class DialogVolba {
public:
	virtual ~DialogVolba()
	{
	}

	/// <summary>
	/// Konstruktor vytvorÌ volbu s textom a indexom nasledujucej polozky
	/// </summary>
	/// <param name="paText">text polozky</param>
	/// <param name="dalsia">index dalsej</param>
	DialogVolba(string paText, int dalsia);
	virtual string Gettext();
	int dalsia;

	/// <summary>
	/// akcia po vybratÌ polozky
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	virtual void akcia(Hrac* hrac);
private:
	string text;

};

/// <summary>
/// Polozka ktor˝ predstavuje to Ëo npc povie, obashuje aj volby , ako moze hrac odpovedat.
/// </summary>
class DialogPolozka {
public:
	
	/// <summary>
	/// VytvorÌ dialogovu polozku z 0 volbami a textom.
	/// </summary>
	/// <param name="paText">text , ktor˝ reprezentuje odpoved npc</param>
	DialogPolozka(string paText);
	
	
	virtual ~DialogPolozka();
	
	/// <summary>
	/// Vrati pocet dialogov˝ch volieb , ktorÈ si moze hrac vyberat.
	/// </summary>
	/// <returns>int Pocet volieb</returns>
	virtual int pocetMoznosti();
	
	/// <summary>
	/// Prid· volbu medzi volby.
	/// </summary>
	/// <param name="paVolba">Volba ktoru si bude mocù hraË vybraù.</param>
	void pridajMoznost(DialogVolba* paVolba);

	/// <summary>
	/// Vrati text polozky
	/// </summary>
	/// <returns>string text polozky</returns>
	virtual string Gettext();

	/// <summary>
	/// Vr·ti volbu na indexe i
	/// </summary>
	/// <param name="paIndex">Dialog Volba vybrata</param>
	/// <returns></returns>
	virtual DialogVolba* Getvolba(int paIndex);

	/// <summary>
	/// Zmaze volbu z dialogov˝ch moznosti
	/// </summary>
	/// <param name="paVolba">paVolba na zmazanie</param>
	void zmazMoznost(DialogVolba* paVolba);
protected:
	string text;
	vector<DialogVolba*> dialogoveMoznosti;

};


/// <summary>
/// Trieda reprezentujuca dialog. Obsahuje Polozky a volby.
/// </summary>

class DialogovyStrom
{
public:
	/// <summary>
	/// vytvori prazdny dialog
	/// </summary>
	DialogovyStrom();

	/// <summary>
	/// Prid· moznost k zaciatocnej polozke a polozku na ktoru t·to moznost ukazuje
	/// </summary>
	/// <param name="paVolba">Volba k novej polozke</param>
	/// <param name="paPolozka">nova polozka</param>
	void DialogovyStrom::pridajMoznost(DialogVolba* paVolba, DialogPolozka* paPolozka);
	
	/// <summary>
	/// Zmaze moznost zo zaciatocnej polozky a polozku na ktoru t·to moznost ukazuje
	/// </summary>
	/// <param name="paVolba">volba na zmazanie</param>
	/// <param name="paPolozka">polozka ktor· sa zmaze zo zoznamu</param>
	void DialogovyStrom::zmazMoznost(DialogVolba* paVolba, DialogPolozka* paPolozka);

	/// <summary>
	/// K prvej polozke prid· text ku dialogovej polozke ktor· spravuje quest
	/// </summary>
	/// <param name="paQuest">quest</param>
	void Setdialogquest(Quest* paQuest);

	/// <summary>
	/// NastavÌ aktualnu polozku na prvu polozku v zozname poloziek a stav dialogu na init
	/// </summary>
	void init();

	/// <summary>
	/// Vrati stav dialogu
	/// </summary>
	/// <returns>DialogStav stav dialogu</returns>
	DialogStav Getstav() const;

	/// <summary>
	/// Vrati aktualnu polozku na ktorej sa hr·c nachadza
	/// </summary>
	/// <returns>DialogPolozka aktualna polozka</returns>
	DialogPolozka* Getaktualnapolozka() const;

	/// <summary>
	/// Na koniec zoznamu poloziek vlozi novu polozku
	/// </summary>
	/// <param name="paPolozka">polozka na vlozenie</param>
	void vlozPolozku(DialogPolozka* paPolozka);

	/// <summary>
	/// NastavÌ stav dialogu na stav bezi
	/// </summary>
	int zacniDialog();

	/// <summary>
	/// NastavÌ aktualnu polozku podla moznosti ktoru si hrac vybral
	/// </summary>
	/// <param name="moznost">index volby v aktualnej polozke</param>
	int zmenPolozku(int moznost);
	~DialogovyStrom();
private:
	Quest* dialogQuest;
	DialogStav stav;
	DialogPolozka *aktualnaPolozka;
	vector<DialogPolozka *> castiDialogu;
};

#endif