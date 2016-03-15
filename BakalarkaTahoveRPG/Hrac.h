#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <deque>

class Mapa;
class Zameranie;
class Animacia;
class Statistika;
class Inventar;
class Predmet;
class QuestManager;

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
	static bool save(Hrac* paHrac);

	Hrac(Zameranie* paZameranie);
	virtual ~Hrac();

	SmerPohladu GetSmerPohladu();

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
	Mapa* getMapa();

	Statistika* Getstatistika();
	void Setstatistika(Statistika* paStatistika);
	Zameranie* GetZameranie();
	Inventar* Getinventar();
	void vyhodPredmet(Predmet* predemet);

	void pridajSkusenosti(int pocet);
	QuestManager* Getmanazerquestov();
	
	

private:
	Animacia* animaciaDole;
	Animacia* animaciaHore;
	Animacia* animaciaVlavo;
	Animacia* animaciaVpravo;
	Inventar* inventar;

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

	QuestManager* manazerQuestov;
};

