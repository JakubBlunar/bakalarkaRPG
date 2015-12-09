#pragma once

#include <SFML\Graphics.hpp>

class Policko;
class Hrac;
//#include "Npc.h"

class Mapa
{

public:
	Mapa();
	~Mapa();
	//Policko *m_Policko;
	//Npc *m_Npc;

	void posun(int posunY, int posunX);
	void render(sf::RenderWindow* okno);
	void update();

private:
	Hrac* hrac;
	Policko* mapa[100][100];
	int sirka;
	int vyska;
	int posunX;
	int posunY;

};