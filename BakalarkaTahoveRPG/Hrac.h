#pragma once

#include <SFML\Graphics.hpp>
//#include "Statistika.h"
//#include "Inventar.h"
//#include "Animacia.h"
//#include "Zameranie.h"

class Zameranie;
class Animacia;

enum SmerPohladu
{
	hore,
	dole,
	vlavo,
	vpravo
};

class Hrac
{

public:
	Hrac(Zameranie* paZameranie);
	virtual ~Hrac();

	void posunSa(int kam);
	void render(sf::RenderWindow* paOkno);
	void update(double delta);
	void zmenSmerPohladu(SmerPohladu smer);

	int GetoffsetX();
	int GetoffsetY();
	int GetpolickoX();
	int GetpolickoY();

private:
	Animacia* animaciaDole;
	Animacia* animaciaHore;
	Animacia* animaciaVlavo;
	Animacia* animaciaVpravo;
	//vector<Quest> dokonceneQuesty;
	//Inventar inventar;
	//std::Map<string, Predmet> oblecene;
	//vector<Quest> questy;
	SmerPohladu smerPohladu;
	//Statistika statistika;
	Zameranie* zameranie;

	int polickoX;
	int polickoY;
	int offsetX;
	int offsetY;

};

