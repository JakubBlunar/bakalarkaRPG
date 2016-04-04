#pragma once
#include <SFML\Graphics.hpp>

#include "Stav.h"

class Hrac;
class Inventar;
class Predmet;
class DialogovyStrom;
class Npc;

/// <summary>
/// Stav ktor� vykresluje dialog medzi npc a hr��om
/// </summary>
class StavDialog : public Stav
{

public:
	StavDialog(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavDialog();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

	/// <summary>
	/// Nastav� dialog ktor� sa bude zobrazova�
	/// </summary>
	/// <param name="paNpc"></param>
	void Setdialog(Npc* paNpc);

private:
	Npc* npc;
	DialogovyStrom* dialog;
	int oznacene;
};