#if !defined(StavHranieHry_h)
#define  StavHranieHry_h

#include "Stav.h"
#include <vector>
#include "Audio.h"

class Mapa;
class Hrac;
class Predmet;

/// <summary>
/// Stav ktor� predstavuje hranie hry, vykresluje sa tu mapa , hrac , npc a v�etko ostatn�
/// </summary>
class StavHranieHry : public Stav
{

public:
	StavHranieHry(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra,Mapa* mapa);
	virtual ~StavHranieHry();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

	/// <summary>
	/// Nastavi aktualnu mapu na ktorej je hra�
	/// </summary>
	/// <param name="newVal">nova mapa</param>
	void Setmapa(Mapa* newVal);
	
	/// <summary>
	/// Vrati aktualnu mapu
	/// </summary>
	/// <returns>aktualna mapa</returns>
	Mapa* getMapa() const;

private:

	/// <summary>
	/// Nacita loot z policka na ktorom stoji hra� a prepne stav do zobrazovania lootu
	/// </summary>
	void zobrazLoot();
	Mapa* mapa;
	Hrac* hrac;

	std::vector<Predmet*>* loot;
	int lootIndex;
	Audio* hudba;
};

#endif