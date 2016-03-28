#pragma once
#include <vector>
#include <iostream>
#include "Stav.h"
#include <SFML\Graphics.hpp>

class Zameranie;

class StavVolbaZamerania : public Stav
{

public:
	StavVolbaZamerania(std::string paNazov,sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavVolbaZamerania();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;
private:
	signed int oznacene;

	float scale;
	bool setnuteScale;

	Tlacidlo* tlacidla[3];

	sf::Texture warriorTextura;
	sf::Sprite warriorObrazok;

	sf::Texture mageTextura;
	sf::Sprite mageObrazok;

	sf::Texture rogueTextura;
	sf::Sprite rogueObrazok;

	void zvoleneZameranie(int paIndex) const;
};
