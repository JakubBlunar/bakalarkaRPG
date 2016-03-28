#pragma once
#include <map>

#include "Stav.h"

class StavRozhrania
{

public:
	StavRozhrania(Stav* pociatocnyStav);
	~StavRozhrania();

	void render() const;
	void update(double cas);
	void pridajStav(Stav* stav);
	Stav* GetaktualnyStav() const;
	void zmenStav(std::string stav);
	Stav* dajStav(std::string stav);

private:
	std::map<std::string, Stav*> stavy;
	Stav* aktualnyStav;
	Stav* nasledujuci;
};
