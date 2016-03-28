#pragma once
#include <string>
#include <vector>
#include "Stav.h"

/**
* - nova hra, koniec, pokracovat
*/

class Tlacidlo;
class StavHlavneMenu : public Stav
{

public:
	StavHlavneMenu(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra);
	virtual ~StavHlavneMenu();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;

private:
	std::vector<Tlacidlo*> tlacidla;
	signed int oznacene;
};

