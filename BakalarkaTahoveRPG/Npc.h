#pragma once
#if !defined(npc_h)
#define npc_h

#include <SFML\Graphics.hpp>

class Animacia;
class Hrac;
class DialogovyStrom;

class Npc
{

public:
	Npc(std::string meno, DialogovyStrom* dialog);
	virtual ~Npc();
	std::string Getmeno() const;

	DialogovyStrom* Getdialog() const;
	sf::Sprite* dajObrazok() const;
	virtual void dialog(Hrac* hrac);
	void update() const;

	void Setanimacia(Animacia* animacia);
private:
	Animacia *animacia;
	DialogovyStrom* dialogStrom;
	std::string meno;

};
#endif