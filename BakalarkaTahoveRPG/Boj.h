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

/// <summary>
/// Trieda sluûi na organizaciu boja medzi hracom a npc
/// </summary>
class Boj
{

public:
	/// <summary>
	/// VYtvori boj medzi hracom a npc
	/// </summary>
	/// <param name="paHrac"></param>
	/// <param name="paNpc"></param>
	Boj(Hrac* paHrac, Nepriatel* paNpc);
	virtual ~Boj();

	/// <summary>
	/// Spusti sa casovac a t˝m aj boj
	/// </summary>
	void bojStart();

	/// <summary>
	/// Vrati ci je koniec boja alebo nie
	/// </summary>
	/// <returns>true ak je , false ak nie</returns>
	bool koniecBoja() const;

	/// <summary>
	/// Vrati hracovu statistiku
	/// </summary>
	/// <returns>statistika hraca</returns>
	Statistika* Gethracovastatistika() const;

	/// <summary>
	/// Vr·ti npc statistiku
	/// </summary>
	/// <returns>statistika npc</returns>
	Statistika* Getnpcstatistika() const;

	/// <summary>
	/// Metoda ktor· vr·ti , Ëi boj Ëak· na vybratie akcie hracom.
	/// </summary>
	/// <returns>true ak caka, false ak necaka</returns>
	bool cakaNaVybratieAkcie() const;

	/// <summary>
	/// Metoda nastavÌ hracovu akciu na akciu ktoru si vybral
	/// </summary>
	/// <param name="paAkcia">vybrata akcia</param>
	void hracVybralAkciu(Akcia* paAkcia);

	/// <summary>
	/// Vrati cas , kolko trv· boj
	/// </summary>
	/// <returns>pocet sekund od kedy bezi boj</returns>
	sf::Time Getcasvboji() const;

	/// <summary>
	/// Aktualizovanie boja , prepocitanie poskodenia, vykonanie akcii , vyhodnotenie efektov
	/// </summary>
	void update();

	/// <summary>
	/// Vrati ci ma zadana akcia cooldown
	/// </summary>
	/// <param name="paAkcia">akcia ktor· sa zistuje</param>
	/// <returns>true ak m· , false ak nem·</returns>
	bool maAkciaCooldown(Akcia* paAkcia);

	/// <summary>
	/// vr·ti koæko % z nacitavania akcie uû ubehlo
	/// </summary>
	/// <returns>% kolko je nacitane z akcie</returns>
	float castBarProgres() const;

	/// <summary>
	/// Vrati retazec, ktor˝ predstavuje log boja 
	/// </summary>
	/// <param name="paOd">index od ktoreho sa do logu pridaju spravy</param>
	/// <param name="paDo">index po ktor˝ sa budu pridavaù do logu spravy</param>
	/// <returns>spraven˝ log</returns>
	string Getlog(int paOd, int paDo);

	/// <summary>
	/// Vr·ti nepriatela oproti ktorÈmu bojuje hr·Ë
	/// </summary>
	/// <returns>Nepriatel</returns>
	Nepriatel* Getnepriatel() const;
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

	/// <summary>
	/// Vyhodnotenie boja , zisti sa kto vyhral , kto prehral , aktualizuju sa questy a vygeneruju ziskane predmety.
	/// </summary>
	void vyhodnotenie();
	
	deque<string> logBoja;

};
#endif
