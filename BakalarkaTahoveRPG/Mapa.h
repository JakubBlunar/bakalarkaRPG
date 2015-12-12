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
	Mapa(std::string menoMapy,Hrac* paHrac,Hra* hra,int posHracaX, int posHracaY, int smerPohladu);
	~Mapa();
	

	void setHrac(Hrac* paHrac);
	int Getvyska();
	int Getsirka();

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

	void nacitajMapu();
	bool GetNacitava();
private:
	Hra* hra;
	Hrac* hrac;
	std::string meno;
	Policko* mapa[100][100];
	std::map<int, sf::Texture*> textury;
	std::map<int, std::string> specialnePolicka;

	int sirka;
	int vyska;

	int posunX;
	int posunY;
	bool hybeSa;
	int pohybDelta;
	int smerPohybu;
	bool hracSkocil;

	bool nacitavam;
};