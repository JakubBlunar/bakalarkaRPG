#pragma once
#include "Stav.h"

class Tlacidlo;

class StavPauza : public Stav
{

public:
	StavPauza(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavPauza();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;

private:
	std::vector<Tlacidlo*> tlacidla;
	signed int oznacene;
};
