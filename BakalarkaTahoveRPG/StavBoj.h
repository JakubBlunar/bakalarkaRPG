#if !defined(stavBoj_h)
#define stavBoj_h
#include "Stav.h"

class Hrac;
class Boj;
class Tlacidlo;
class Akcia;

class StavBoj:public Stav
{
public:
	StavBoj(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavBoj();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

	void setBoj(Boj* boj);

private:
	void vykresliInfoAkcie(Akcia* akcia,sf::Vector2f pozicia);

	Boj* boj;
	Tlacidlo* tlacidla[3][9];
	std::vector<Akcia*>* hracoveAkcie;
	Tlacidlo* logHranice;
	Tlacidlo* doInventara;
	
	int oznacene;
	sf::RectangleShape ukazovatel;
};

#endif
