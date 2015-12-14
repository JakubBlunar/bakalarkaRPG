#pragma once

#include <SFML\Graphics.hpp>
//#include "Statistika.h"
//#include "Inventar.h"

class Mapa;
class Zameranie;
class Animacia;
class Statistika;

enum SmerPohladu
{
	hore,
	dole,
	vlavo,
	vpravo,
	stoji
};

class Hrac
{

public:
	Hrac(Zameranie* paZameranie);
	virtual ~Hrac();

	void render(sf::RenderWindow* paOkno);
	void update(double delta);
	void zmenSmerPohladu(SmerPohladu smer);
	void posun(int x, int y);
	void animaciaTick();

	void chodVpravo();
	void chodVlavo();
	void chodHore();
	void chodDole();
	bool GethybeSa();

	void setPolickoX(int paX);
	void setPolickoY(int paY);
	void setOffsetX(int paX);
	void setOffsetY(int pax);

	int GetoffsetX();
	int GetoffsetY();
	int GetpolickoX();
	int GetpolickoY();

	void setMapa(Mapa*);

	Statistika* Getstatistika();
	void Setstatistika(Statistika* paStatistika);
	Zameranie* GetZameranie();

	void pridajSkusenosti(int pocet);
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
	Statistika* statistika;
	Zameranie* zameranie;

	int polickoX;
	int polickoY;
	int offsetX;
	int offsetY;

	SmerPohladu smerPohybu;
	bool hybeSa;
	int pohybDelta;

	Mapa* mapa;
};

