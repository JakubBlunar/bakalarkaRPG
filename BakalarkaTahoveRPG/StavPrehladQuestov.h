#if !defined(StavPrehladQuestov_h)
#define StavPrehladQuestov_h
#include "Stav.h"

#include <vector>

class QuestManager;
class Tlacidlo;

/// <summary>
/// Stav ktorý zobrazuje rozrobené a dokoncené hráèove questy
/// </summary>
class StavPrehladQuestov :
	public Stav
{
public:
	StavPrehladQuestov(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavPrehladQuestov();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

private:
	QuestManager* spravcaQuestov;
	sf::CircleShape dole;
	sf::CircleShape hore;

	unsigned int zakliknute;
	unsigned int indexOd;
	unsigned int pocet;
	std::vector<Tlacidlo*> tlacidla;
	Tlacidlo* tlacidloSpat;
};
#endif
