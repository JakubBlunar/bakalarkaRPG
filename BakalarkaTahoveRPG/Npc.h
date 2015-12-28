#pragma once
#if !defined(npc_h)
#define npc_h

#include <SFML\Graphics.hpp>
#include <string>

//#include "Npc dialog.h"
//#include "DialogovyStrom.h"
//#include "Animacia.h"
class Animacia;
class Hrac;
class DialogovyStrom;

class Npc
{

public:
	Npc(std::string meno);
	virtual ~Npc();
	std::string Getmeno();

	DialogovyStrom* Getdialog();
	sf::Sprite* dajObrazok();
	virtual void dialog(Hrac* hrac);
	void update();

	void Setanimacia(Animacia* animacia);
private:
	Animacia *animacia;
	DialogovyStrom* dialogStrom;
	std::string meno;

};
#endif