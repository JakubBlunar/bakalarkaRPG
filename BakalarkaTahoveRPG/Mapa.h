#pragma once


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
	void render();
	void update();

private:
	Hrac* hrac;
	Policko** mapa;
	int sirka;
	int vyska;

};