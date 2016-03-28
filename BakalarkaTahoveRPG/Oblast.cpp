#include "Oblast.h"



Oblast::Oblast(int paX, int paY, int paW, int paH)
	: x(paX), y(paY), w(paW), h(paH)
{

}

bool Oblast::jeRovnaka(Oblast paOblast) const
{
	return (this->x == paOblast.x && this->y == paOblast.y && this->w == paOblast.w && this->h == paOblast.h) ? true : false;
}

bool Oblast::obsahujeSuradnicu(sf::Vector2i paPos) const
{
	return (paPos.x >= x && paPos.x <= x + w && paPos.y >= y && paPos.y <= y + h) ? true : false;
}

void Oblast::pridajNepriatela(string paMeno) {
	if (std::find(nepriatelia.begin(), nepriatelia.end(), paMeno) == nepriatelia.end())
	{
		nepriatelia.push_back(paMeno);
	}
}

vector<string> Oblast::Getnepriatelia() const
{
	return nepriatelia;
}
