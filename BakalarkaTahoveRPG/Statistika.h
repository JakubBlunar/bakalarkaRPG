#if !defined(statistika_h)
#define statistika_h

#include <SFML\Graphics.hpp>
#include <map>
#include <vector>
#include "Timer.h"

using namespace std;

class Predmet;
class Akcia;
class Efekt;

/// <summary>
/// Statistika predstavuje vlastnosti hraca alebo npc, kolko ma zivota , many , teda skoro vöetko Ëo je potrebne na boj
/// </summary>
class Statistika
{

public:

	/// <summary>
	/// vytvorÌ statistiku z defaultn˝mi nastaveniami
	/// </summary>
	Statistika();

	/// <summary>
	/// Vytvori statistiku
	/// </summary>
	/// <param name="paUroven">Uroven postavy</param>
	/// <param name="paHp">pocet zivota</param>
	/// <param name="paHpMax">maximalny pocet zivita</param>
	/// <param name="paMp">mnozstvo many</param>
	/// <param name="mpMax">maximalne mnozstvo many</param>
	/// <param name="paSila">velkost sily</param>
	/// <param name="paIntelekt">velkost intelektu</param>
	/// <param name="paRychlost">velkost rychlosti</param>
	/// <param name="paObrana">velkost obrany</param>
	/// <param name="paObleceneVeci">zoznam oblecen˝ch vecÌ</param>
	Statistika(int paUroven, int paHp, int paHpMax, int paMp, int mpMax,int paSila, int paIntelekt, int paRychlost, int paObrana,map<int, Predmet*>* paObleceneVeci = new map<int,Predmet*>());
	virtual ~Statistika();

	/// <summary>
	/// Vrati aktivne efekty ktorÈ su na danej statistike
	/// </summary>
	/// <returns>zoznam efektov</returns>
	map<Efekt*, sf::Time>* Getaktivneefekty() const;

	/// <summary>
	/// Vrati zoznam oblecen˝ch vecÌ.
	/// </summary>
	/// <returns>zoznam oblecen˝ch vecÌ</returns>
	map<int, Predmet*>* Getoblecene() const;

	/// <summary>
	/// Vrati akcie ktorÈ moze pouzivat dana statistika
	/// </summary>
	/// <returns>zoznam akcii</returns>
	vector<Akcia*>* Getakcie() const;

	/// <summary>
	/// Prida akciu do statistiky. Potom je ju mozme pouzivat v boji.
	/// </summary>
	/// <param name="paAkcia">Akcia na pridanie</param>
	void vlozAkciu(Akcia* paAkcia);

	/// <summary>
	/// Prida sa efekt. S trvanÌm do.
	/// </summary>
	/// <param name="paEfekt">efekt ktor˝ sa ma pridat</param>
	/// <param name="aktivnyDo">dokedy bude tento efekt aktivny</param>
	void pridajEfekt(Efekt* paEfekt, sf::Time aktivnyDo);

	/// <summary>
	/// Zrusenie aktivneho efektu a vratenie statistiky do normalu.
	/// </summary>
	/// <param name="paEfekt">efekt ktor˝ treba zruöiù</param>
	void zrusEfekt(Efekt* paEfekt);

	/// <summary>
	/// Vrati sancu na uhyb aku m· dana statistika
	/// </summary>
	/// <returns>sanca na vyhnutie zasahu</returns>
	double Getsancanauhyb() const;

	/// <summary>
	/// Vr·ti odolnost vypocitanu zo statistiky.
	/// </summary>
	/// <returns>odolnost voci poskodeniu</returns>
	double Getodolnostvociposkodeniu() const;

	/// <summary>
	/// Vrati r˝chlost utoku zbranÈ
	/// </summary>
	/// <returns>rychlost v ms</returns>
	int Getrychlostutoku() const;

	/// <summary>
	/// Vrati uroven statistiky
	/// </summary>
	/// <returns>uroven</returns>
	int dajUroven() const;

	/// <summary>
	/// Vrati aktualny pocet bodov zdravia statistiky.
	/// </summary>
	/// <returns>pocez zdravia</returns>
	int Gethp() const;

	/// <summary>
	/// Vrati maximalny pocet bodov zdravia statistiky
	/// </summary>
	/// <returns>maximalne hp</returns>
	int GethpMax() const;

	/// <summary>
	/// Vrati intelekt statistiky
	/// </summary>
	/// <returns>intelekt</returns>
	int Getintelekt() const;

	/// <summary>
	/// Vrati aktualne mnozstvo many 
	/// </summary>
	/// <returns>mnozstvo many</returns>
	int Getmp();

	/// <summary>
	/// Vrati maximalne mnozstvo many statistiky
	/// </summary>
	/// <returns>maximalne mnozstvo many</returns>
	int GetmpMax() const;

	/// <summary>
	/// Vrati obranu statistiky
	/// </summary>
	/// <returns>obrana statistiky</returns>
	int Getobrana() const;

	/// <summary>
	/// Vrati rychlost statistiky
	/// </summary>
	/// <returns>rychlost statistiky</returns>
	int Getrychlost() const;

	/// <summary>
	/// Vrati silu statistiky
	/// </summary>
	/// <returns>sila statistiky</returns>
	int Getsila() const;

	/// <summary>
	/// Vrati pocet skusenosti ktoru ma statistika
	/// </summary>
	/// <returns>pocet skusenosti</returns>
	int Getskusenosti() const;

	/// <summary>
	/// Vrati hodnotu statu ktor˝ je specifikovany pomocou parametra
	/// </summary>
	/// <param name="aky">Ëoho hodnotu vratit</param>
	/// <returns>hodnota danej statistiky</returns>
	int Statistika::Getstat(string aky) const;

	/// <summary>
	/// Nastavi hp na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void Sethp(int novaHodnota);
	/// <summary>
	/// Nastavi maximalne hp na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void SethpMax(int novaHodnota);

	/// <summary>
	/// Nastavi intelekt na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void Setintelekt(int novaHodnota);

	/// <summary>
	/// Nastavi mnozstvo many na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void Setmp(int novaHodnota);

	/// <summary>
	/// Nastavi obranu na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void Setobrana(int novaHodnota);

	/// <summary>
	/// Nastavi rychlost na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void Setrychlost(int novaHodnota);

	/// <summary>
	/// Nastavi silu na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void Setsila(int novaHodnota);

	/// <summary>
	/// Nastavi skusenosti na novu hodnotu
	/// </summary>
	/// <param name="novaHodnota">nova hodnota</param>
	void Setskusenosti(int novaHodnota);

	/// <summary>
	/// Zvysi stat zadany parametrom o danu hodnotu
	/// </summary>
	/// <param name="kolko">ktor˝ stat</param>
	/// <param name="paCo">o kolko zmenit</param>
	void zvysStat(int kolko, string paCo);

	/// <summary>
	/// prida k aktualnemu mnozstvu xp pocet
	/// </summary>
	/// <param name="pocet">pocet kolko pridat</param>
	void pridajXp(int pocet);

	/// <summary>
	/// Nastavi uroven na novu hodnotu
	/// </summary>
	/// <param name="paUroven">nova hodnota urovne</param>
	void setUroven(int paUroven);

	/// <summary>
	/// Nastavi combat na true alebo false
	/// </summary>
	/// <param name="paNa">nova hodnota</param>
	void setCombat(bool paNa);

	/// <summary>
	/// Prepocita poskodenia podla nasaden˝ch zbranÌ
	/// </summary>
	void prepocitajPoskodenia();

	/// <summary>
	/// Vrati minimalne poskodenie
	/// </summary>
	/// <returns>minimalne poskodenie</returns>
	int Getminposkodenie() const;

	/// <summary>
	/// Vrati maximalne poskodenie
	/// </summary>
	/// <returns>maximalne poskodenie</returns>
	int Getmaxposkodenie() const;
private:
	int hp;
	int hpMax;
	int intelekt;
	int mp;
	int mpMax;
	int obrana;
	int rychlost;
	int sila;
	int skusenosti;
	int uroven;
	int minPoskodenie;
	int maxPoskodenie;

	vector<Akcia*>* akcie;
	map<int, Predmet*>* oblecene;
	map<Efekt*, sf::Time>* aktivneEfekty;

	Timer timerMp;
	sf::Time poslednaObnova;
	bool combat;
};
#endif 
