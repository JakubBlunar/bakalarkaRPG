#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Hra;
class PopupOkno;

enum StavAkcia {
	NORMAL,
	ZOBRAZUJE_POPUP,
	ZOBRAZUJE_LOOT
};


class Stav
{

public:
	Stav(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra);
	virtual ~Stav();
	virtual void update(double delta);
	virtual void render();
	virtual void onEnter();
	virtual void onExit();
	std::string Getnazov();
	void Setnazov(std::string paNazov);
	void zobrazPopup(PopupOkno* paCo);

	bool GetzobrazujePopup();

protected:
	StavAkcia stav;
	sf::Font* font;

	std::string nazov;
	sf::RenderWindow* okno;
	Hra* hra;

	PopupOkno* popupText;

	bool stlacenaKlavesa;
	bool stlacenaMys;
};
