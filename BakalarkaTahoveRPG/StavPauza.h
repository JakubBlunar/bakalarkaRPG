#if !defined(StavPauza_h)
#define StavPauza_h

#include "Stav.h"

class Tlacidlo;

/// <summary>
/// Stav Zobrazuje obrazovku , ktoru hr�� vid� ked pozastav� hru
/// </summary>
class StavPauza : public Stav
{

public:
	StavPauza(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavPauza();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

private:
	std::vector<Tlacidlo*> tlacidla;
	signed int oznacene;
};
#endif