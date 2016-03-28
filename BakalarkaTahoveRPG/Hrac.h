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
	hore = 0,
	dole = 1,
	vlavo = 2,
	vpravo = 3,
	stoji = 4
};

class Hrac
{

public:
	static bool save(Hrac* paHrac);

	Hrac(Zameranie* paZameranie);
	virtual ~Hrac();

	SmerPohladu GetSmerPohladu() const;

	void render(sf::RenderWindow* paOkno) const;
	void update(double delta);
	void zmenSmerPohladu(SmerPohladu smer);
	void posun(int x, int y);
	void animaciaTick() const;

	void chodVpravo();
	void chodVlavo();
	void chodHore();
	void chodDole();
	bool GethybeSa() const;

	void setPolickoX(int paX);
	void setPolickoY(int paY);
	void setOffsetX(int paX);
	void setOffsetY(int pax);

	int GetoffsetX() const;
	int GetoffsetY() const;
	int GetpolickoX() const;
	int GetpolickoY() const;

	void setMapa(Mapa*);
	Mapa* getMapa() const;

	Statistika* Getstatistika() const;
	void Setstatistika(Statistika* paStatistika);
	Zameranie* GetZameranie() const;
	Inventar* Getinventar() const;
	void vyhodPredmet(Predmet* predemet) const;

	void pridajSkusenosti(int pocet, bool oznamenie = true) const;
	QuestManager* Getmanazerquestov() const;
	
	

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

