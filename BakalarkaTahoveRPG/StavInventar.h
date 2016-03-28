#if !defined(StavInventar_h)
#define StavInventar_h

#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;
class Inventar;
class Predmet;
class Tlacidlo;

class StavInventar : public Stav
{

public:
	StavInventar(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavInventar();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;

	void Setzboja(bool paNa);

protected:
	void vykresliOknoPredmetu(Predmet* predmet, int x, int y, sf::RenderWindow* okno, bool predaj) const;

	int oznacene;
	sf::RectangleShape ukazovatel;
	int nasirku;

	bool otvoreneZboja;

	Tlacidlo* tlacidloSpat;
	Inventar* inventar;
	Hrac* hrac;
};
#endif