#if !defined(Mapa_h)
#define Mapa_h

#include <SFML\Graphics.hpp>
#include <string>

class Policko;
class Hrac;
class Hra;
class StavHranieHry;

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
	Mapa(std::string menoMapy, Hrac* paHrac,Hra* hram,int paVyska , int paSirka);
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

	Policko* GetPolicko(int x, int y);
	void nastavPolicko(int x, int y, Policko*);
	sf::FloatRect Getzobrazenaoblast();
	sf::Time aktCas();
	void pridajNepriatela(std::string meno);
	std::vector<std::string>* Getmoznynepriatelia();
private:
	Hra* hra;
	Hrac* hrac;
	Policko*** mapa;
	std::vector<std::string>* moznyNepriatelia;

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
};

#endif