#if !defined(StavInventar_h)
#define StavInventar_h

#include <SFML\Graphics.hpp>
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
	void update() override;

	/// <summary>
	/// Nastavi na true ak hr·Ë otvara inventar z boja , potom ked sa odide z tohto stavu ide sa nasp‰ù do boja.
	/// </summary>
	/// <param name="paNa">ci sa otvara tento stav z boja</param>
	void Setzboja(bool paNa);

protected:
	/// <summary>
	/// Vykresli okno predmetu nad oznaceny predmet
	/// </summary>
	/// <param name="predmet">predmet ktoreho info zobrazi</param>
	/// <param name="x">pozicia x na ktoru zobrazi</param>
	/// <param name="y">pozicia y na ktoru zobrazi</param>
	/// <param name="okno">okno na ktore sa vykresluje</param>
	void vykresliOknoPredmetu(Predmet* predmet, int x, int y, sf::RenderWindow* okno, bool predaj) const;
	std::vector<Tlacidlo*> tlacidla;

	int oznacene;
	sf::RectangleShape ukazovatel;
	int nasirku;

	bool otvoreneZboja;

	Tlacidlo* tlacidloSpat;
	Inventar* inventar;
	Hrac* hrac;

	/// <summary>
	/// Pouzije oznacen˝ predmet
	/// </summary>
	void pouziPredmet();
};
#endif