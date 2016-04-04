#if !defined(StavObchod_h)
#define StavObchod_h

#include "StavInventar.h"
#include <vector>

class Predmet;
class Tlacidlo;

/// <summary>
/// Stav predstavuje Obchodovanie s npc, kde hr·Ë moûe kupvoaù a pred·vaù predmety.
/// </summary>
class StavObchod :
	public StavInventar
{
public:
	StavObchod(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavObchod();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

	/// <summary>
	/// Nacita obchod, ktor˝ bude dan˝ stav zobrazovaù
	/// </summary>
	/// <param name="aky">nazov suboru v ktorom je ulozeny obchod</param>
	void nacitajObchod(std::string aky);
private:
	enum {KUPA,PREDAJ} typObchodu;
	std::vector<Predmet*>* dostupnePredmety;
	void predajPredmet();
	void kupPredmet();


};
#endif
