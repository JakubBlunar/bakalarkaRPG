#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class Policko;
class Hrac;
class Hra;

class Mapa
{

public:
	Mapa(std::string menoMapy, Hrac* paHrac,Hra* hra);
	~Mapa();
	
	void hracInterakcia();

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
	int Getsmerpohybu();

	void posunHracaNaPolicko(int x, int y,int smerPohladu);
	void posun(int posunX, int posunY);
	void render(sf::RenderWindow* okno);
	void update(double delta);

	Policko* GetPolicko(int x, int y);
	void nastavPolicko(int x, int y, Policko*);
	//void nacitajMapu(std::string paMeno);
	
private:
	Hra* hra;
	Hrac* hrac;
	Policko* mapa[100][100];
	std::map<int, sf::Texture*> textury;

	int sirka;
	int vyska;

	int posunX;
	int posunY;
	int pohybDelta;
	int smerPohybu;


};