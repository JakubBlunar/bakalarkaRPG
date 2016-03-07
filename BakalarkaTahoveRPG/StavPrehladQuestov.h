#if !defined(StavPrehladQuestov_h)
#define StavPrehladQuestov_h
#include "Stav.h"

#include <vector>

class QuestManager;
class Tlacidlo;

class StavPrehladQuestov :
	public Stav
{
public:
	StavPrehladQuestov(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavPrehladQuestov();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

private:
	QuestManager* spravcaQuestov;
	sf::CircleShape dole;
	sf::CircleShape hore;

	unsigned int indexOd;
	unsigned int pocet;
	std::vector<Tlacidlo*> tlacidla;
	Tlacidlo* tlacidloSpat;
};
#endif
