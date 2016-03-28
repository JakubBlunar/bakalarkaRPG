#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <deque>

class Hra;
class PopupOkno;
class Tlacidlo;

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
	std::string Getnazov() const;
	void Setnazov(std::string paNazov);
	void zobrazPopup(PopupOkno* paCo);

	bool GetzobrazujePopup() const;

protected:
	StavAkcia stav;
	sf::Font* font;

	std::string nazov;
	sf::RenderWindow* okno;
	Hra* hra;

	std::deque<PopupOkno*> popupText;

	bool stlacenaKlavesa;
	bool stlacenaMys;

	Tlacidlo* popDalej;

	static std::string floattostring(float cislo);
};
