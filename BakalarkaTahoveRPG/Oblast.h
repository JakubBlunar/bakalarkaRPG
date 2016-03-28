#pragma once

#include "SFML\Graphics.hpp"

#include <string>
#include <vector>

using namespace std;

class Oblast
{
public:
public:
	Oblast(int paX, int paY, int paW, int paH);

	bool jeRovnaka(Oblast paOblast) const;
	bool obsahujeSuradnicu(sf::Vector2i paPos) const;
	void pridajNepriatela(string paMeno);
	vector<string> Getnepriatelia() const;

	const int x;
	const int y;
	const int w;
	const int h;
private:
	vector<string> nepriatelia;
};

