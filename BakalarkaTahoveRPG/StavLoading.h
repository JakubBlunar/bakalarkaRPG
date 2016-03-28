#pragma once
#include "Stav.h"

class StavLoading:public Stav
{
public:
	StavLoading(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavLoading();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;

};

