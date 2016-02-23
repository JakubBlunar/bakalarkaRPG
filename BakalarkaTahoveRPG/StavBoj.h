#if !defined(stavBoj_h)
#define stavBoj_h
#include "Stav.h"

class Hrac;
class Boj;
class Tlacidlo;

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
	Boj* boj;
	Tlacidlo* tlacidla[3][9];
};

#endif
