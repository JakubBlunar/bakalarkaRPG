#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;
class Inventar;
class Predmet;
class DialogovyStrom;
class Npc;

class StavDialog : public Stav
{

public:
	StavDialog(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavDialog();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);
	void Setdialog(Npc* paNpc);

private:
	Npc* npc;
	DialogovyStrom* dialog;
	int oznacene;
};