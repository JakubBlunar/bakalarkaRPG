#if !defined(StavInventar_h)
#define StavInventar_h

#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;
class Inventar;
class Predmet;

class StavInventar : public Stav
{

public:
	StavInventar(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavInventar();

	virtual void onEnter();
	virtual void onExit();
	virtual void render();
	virtual void update(double delta);

protected:
	void vykresliOknoPredmetu(Predmet* predmet, int x, int y, sf::RenderWindow* okno, bool predaj);

	int oznacene;
	sf::RectangleShape ukazovatel;
	int nasirku;

	Inventar* inventar;
	Hrac* hrac;
};
#endif