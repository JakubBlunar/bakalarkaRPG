#if !defined(Mapa_h)
#define Mapa_h

#include <SFML\Graphics.hpp>
#include <string>

using namespace std;

class Policko;
class Hrac;
class Hra;
class StavHranieHry;
class Oblast;

enum PohybMapy {
	STOJI = 0,
	VPRAVO = 1,
	VLAVO = 2,
	HORE = 3,
	DOLE = 4
};

class Mapa
{

public:
	Mapa(string menoMapy, Hrac* paHrac,Hra* hram,int paVyska , int paSirka);
	~Mapa();
	
	void hracInterakcia(StavHranieHry* paStav, void(StavHranieHry::*callbackFunkcia)());

	void setHrac(Hrac* paHrac);
	int Getvyska();
	int Getsirka();
	void setSirkaVyska(int paSirka, int paVyska);

	void hracSkocilNaPolicko(int x, int y);
	bool jeMoznyPohyb(int x, int y);
	void posunVpravo();
	void posunVlavo();
	void posunHore();
	void posunDole();
	PohybMapy Getsmerpohybu();

	void posunHracaNaPolicko(int x, int y,int smerPohladu);
	void posun(int posunX, int posunY);
	void render(sf::RenderWindow* okno);
	void update(double delta);

	string Getmeno();
	Policko* GetPolicko(int x, int y);
	void nastavPolicko(int x, int y, Policko*);
	sf::FloatRect Getzobrazenaoblast();
	sf::Time aktCas();
	vector<string>* Getmoznynepriatelia();

	void pridajNepriatela(Oblast paOblast, string paCo);

	void setHrobSuradnice(sf::Vector2i);
	sf::Vector2i Gethrobsuradnice();
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

	//snima cas ktorý prešiel od vytvorenia
	sf::Clock casovac;
	//textura ktorá sa vykresli ak je na policku nejaký predmet
	sf::Texture batohTextura;
	sf::Sprite batoh;
	sf::Texture zltyVykricnikTextura;
	sf::Sprite zltyVykricnik;
	sf::Texture zltyOtaznikTextura;
	sf::Sprite zltyOtaznik;
	sf::Texture sedyOtaznikTextura;
	sf::Sprite sedyOtaznik;
};

#endif