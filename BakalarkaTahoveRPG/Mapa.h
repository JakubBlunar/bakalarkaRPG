#pragma once

#include <SFML\Graphics.hpp>

class Policko;
class Hrac;
//#include "Npc.h"

class Mapa
{

public:
	Mapa(Hrac* hrac);
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