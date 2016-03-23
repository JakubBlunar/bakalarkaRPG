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

	bool jeRovnaka(Oblast paOblast);
	bool obsahujeSuradnicu(sf::Vector2i paPos);
	void pridajNepriatela(string paMeno);
	vector<string> Getnepriatelia();

	const int x;
	const int y;
	const int w;
	const int h;
private:
	vector<string> nepriatelia;
};

