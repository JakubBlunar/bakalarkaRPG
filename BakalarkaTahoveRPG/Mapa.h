#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class Policko;
class Hrac;
//#include "Npc.h"

class Mapa
{

public:
	Mapa(Hrac* paHrac);
	~Mapa();
	//Policko *m_Policko;
	//Npc *m_Npc;
	void setHrac(Hrac* paHrac);
	int Getvyska();
	int Getsirka();


	void posunVpravo();
	void posunVlavo();
	void posunHore();
	void posunDole();
	int Getsmerpohybu();

	void posun(int posunX, int posunY);
	void render(sf::RenderWindow* okno);
	void update(double delta);

	void nacitajMapu(std::string paCesta);

private:
	Hrac* hrac;
	Policko* mapa[100][100];
	
	int sirka;
	int vyska;

	int posunX;
	int posunY;
	bool hybeSa;
	int pohybDelta;
	int smerPohybu;

};