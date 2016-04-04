#if !defined(StavHlavneMenu_h)
#define StavHlavneMenu_h

#include <string>
#include <vector>
#include "Stav.h"
#include "Audio.h"

class Tlacidlo;

/// <summary>
/// Stav ktorý zobrazi hlavne menu s ponuku
/// </summary>
class StavHlavneMenu : public Stav
{

public:
	StavHlavneMenu(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra);
	virtual ~StavHlavneMenu();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

private:
	std::vector<Tlacidlo*> tlacidla;
	signed int oznacene;

	Audio opening;
	sf::Texture pozadieTextura;
	sf::Sprite pozadie;

};

#endif