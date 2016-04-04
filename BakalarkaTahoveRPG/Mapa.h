#if !defined(Mapa_h)
#define Mapa_h

#include <SFML\Graphics.hpp>

using namespace std;

class Policko;
class Hrac;
class Hra;
class StavHranieHry;
class Oblast;

/// <summary>
/// Enum ktor˝ udava smer pohybu mapy
/// </summary>
enum PohybMapy {
	STOJI = 0,
	VPRAVO = 1,
	VLAVO = 2,
	HORE = 3,
	DOLE = 4
};

/// <summary>
/// Mapa po ktor· tvorÌ Ëasù sveta
/// </summary>
class Mapa
{

public:
	/// <summary>
	/// VytvorÌ novu mapu s priehladn˝mi polickami
	/// </summary>
	/// <param name="menoMapy">meno subboru mapy</param>
	/// <param name="paHrac">aktualny hrac</param>
	/// <param name="hram">instancia hry</param>
	/// <param name="paVyska">vyska mapy </param>
	/// <param name="paSirka">sirka mapy</param>
	Mapa(string menoMapy, Hrac* paHrac,Hra* hram , int paSirka, int paVyska);
	~Mapa();
	
	/// <summary>
	/// Vykreslenie celej mapy a vöetkeho na okno
	/// </summary>
	/// <param name="okno">okno na ktorÈ sa m· vykresliù</param>
	void render(sf::RenderWindow* okno);

	/// <summary>
	/// aktualizacia celej mapy v hernej sluËke
	/// </summary>
	void update();

	/// <summary>
	/// Hrac si zvolil interakciu , podla priorit sa zvoli Ëinnosù, ak je loot tak sa zavoa callback funkcia ktor· spusti lootovanie
	/// </summary>
	/// <param name="paStav">Stavrozhrania hranie hry , kde hr·Ë vidi loot</param>
	/// <param name="callbackFunkcia">funkcia ktor· nastavi stavu aby zobrazoval loot na policku</param>
	void hracInterakcia(StavHranieHry* paStav, void(StavHranieHry::*callbackFunkcia)()) const;

	/// <summary>
	/// NastavÌ mape hraËa ktor˝ na nej je
	/// </summary>
	/// <param name="paHrac"></param>
	void setHrac(Hrac* paHrac);

	/// <summary>
	/// Vrati vysku mapy 
	/// </summary>
	/// <returns>int pocet policok</returns>
	int Getvyska() const;

	/// <summary>
	/// Vrati pocet policok ktorÈ ma mapa na sirku
	/// </summary>
	/// <returns>int pocet policok</returns>
	int Getsirka() const;

	/// <summary>
	/// Nastavi vysku a sirku mapy
	/// </summary>
	/// <param name="paSirka">pocetPolicok na sirku</param>
	/// <param name="paVyska">pocetPolicok na vysku</param>
	void setSirkaVyska(int paSirka, int paVyska);

	/// <summary>
	/// Metoda v ktorej mapa povie policku na suradnici x,y ûe skoËil na neho hrac
	/// </summary>
	/// <param name="x">suradnica policka x</param>
	/// <param name="y">suradnica policka y</param>
	void hracSkocilNaPolicko(int x, int y) const;

	/// <summary>
	/// Vrati ci je mozny pohyb na policko x,y
	/// </summary>
	/// <param name="x">pozicia policka x</param>
	/// <param name="y">pozicia policka y</param>
	/// <returns></returns>
	bool jeMoznyPohyb(int x, int y) const;

	/// <summary>
	/// Zacne posuvat mapu o jedno policko vpravo
	/// </summary>
	void posunVpravo();

	/// <summary>
	/// Zacne posuvat mapu o jedno policko vlavo
	/// </summary>
	void posunVlavo();

	/// <summary>
	/// Zacne posuvat mapu o jedno policko hore
	/// </summary>
	void posunHore();

	/// <summary>
	/// Zacne posuvat mapu o jedno policko dole
	/// </summary>
	void posunDole();

	/// <summary>
	/// Vr·ti smer pohybu mapy
	/// </summary>
	/// <returns>smer pohybu</returns>
	PohybMapy Getsmerpohybu() const;

	/// <summary>
	/// Presunie hraca na policko x ,y a bude otoceny na smer pohladu
	/// </summary>
	/// <param name="x">pozicia policka x</param>
	/// <param name="y">pozicia policka y</param>
	/// <param name="smerPohladu">smer pohladu hraca</param>
	void posunHracaNaPolicko(int x, int y,int smerPohladu);

	/// <summary>
	/// Posunie mapu o x ,y pixelov
	/// </summary>
	/// <param name="posunX">smer x</param>
	/// <param name="posunY">smer y</param>
	void posun(int posunX, int posunY);

	/// <summary>
	/// Vrati meno suboru v ktorom je ulozena mapa
	/// </summary>
	/// <returns>meno mapy</returns>
	string Getmeno() const;

	/// <summary>
	/// Vr·ti policko na suradnici x,y
	/// </summary>
	/// <param name="x">suradnica x</param>
	/// <param name="y">suradnica y</param>
	/// <returns></returns>
	Policko* GetPolicko(int x, int y) const;

	/// <summary>
	/// Nastavi policko na x,y na policko zadane parametrom
	/// </summary>
	/// <param name="x">suradnica x</param>
	/// <param name="y">suradnica y</param>
	/// <param name="policko">nove ppolicko</param>
	void nastavPolicko(int x, int y, Policko* policko) const;

	/// <summary>
	/// Vrati zobrazenu oblast ktoru vidÌ hrac
	/// </summary>
	/// <returns>Rectangle zobrazenej oblasti</returns>
	sf::FloatRect Getzobrazenaoblast() const;

	/// <summary>
	/// Aktualny cas 
	/// </summary>
	/// <returns></returns>
	sf::Time aktCas() const;

	/// <summary>
	/// Vrati nepriatelov Ëo moûu hraËa napadnuù
	/// </summary>
	/// <returns>pole nepriatelov</returns>
	vector<string>* Getmoznynepriatelia();
	
	/// <summary>
	/// Prida nepriatela na danu oblast
	/// </summary>
	/// <param name="paOblast">obdlznik na mape ktor˝ tvor˝ oblast</param>
	/// <param name="paCo">meno nepriatela</param>
	void pridajNepriatela(Oblast paOblast, string paCo);

	/// <summary>
	/// Nastavi suradnice hrobu na x,y
	/// </summary>
	/// <param name="">pozicia hrobu na mape</param>
	void setHrobSuradnice(sf::Vector2i);

	/// <summary>
	/// Vrati suradnice hrobu
	/// </summary>
	/// <returns>pozicia hrobu na mape</returns>
	sf::Vector2i Gethrobsuradnice() const;

	/// <summary>
	/// Zobrazi minimapu 
	/// </summary>
	void toogleMinimapa();
private:

	vector<Oblast*> oblasti;
	sf::Vector2i hrobSuradnice;

	Hra* hra;
	Hrac* hrac;
	Policko*** mapa;
	vector<string>* moznyNepriatelia;
	string menoMapy;

	int sirka;
	int vyska;

	int posunX;
	int posunY;
	int pohybDelta;
	PohybMapy smerPohybu;

	sf::View view;

	//snima cas ktor˝ preöiel od vytvorenia
	sf::Clock casovac;
	//textura ktor· sa vykresli ak je na policku nejak˝ predmet
	sf::Texture batohTextura;
	sf::Sprite batoh;
	sf::Texture zltyVykricnikTextura;
	sf::Sprite zltyVykricnik;
	sf::Texture zltyOtaznikTextura;
	sf::Sprite zltyOtaznik;
	sf::Texture sedyOtaznikTextura;
	sf::Sprite sedyOtaznik;

	bool minimapa;
};

#endif