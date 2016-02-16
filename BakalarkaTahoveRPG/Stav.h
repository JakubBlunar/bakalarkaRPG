#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Hra;

enum StavAkcia {
	NORMAL,
	ZOBRAZUJE_POPUP
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
	void zobrazPopup(std::string paCo);
protected:
	StavAkcia stav;
	sf::Font* font;

	std::string nazov;
	sf::RenderWindow* okno;
	Hra* hra;

	std::string popupText;

	bool stlacenaKlavesa;
	bool stlacenaMys;
};
