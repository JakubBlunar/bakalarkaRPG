#pragma once
#if !defined(npc_h)
#define npc_h

#include <SFML\Graphics.hpp>
#include <string>

class Animacia;
class Hrac;
class DialogovyStrom;

class Npc
{

public:
	Npc(std::string meno, DialogovyStrom* dialog);
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