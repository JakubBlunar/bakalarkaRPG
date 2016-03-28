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

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;
	void Setdialog(Npc* paNpc);

private:
	Npc* npc;
	DialogovyStrom* dialog;
	int oznacene;
};