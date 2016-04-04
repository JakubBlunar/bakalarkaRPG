#if !defined(stavCredits_h)
#define stavCredits_h

#include "Stav.h"

/// <summary>
/// Stav ktorý zobrazuje Credits
/// </summary>
class StavCredits
	:public Stav
{
public:
	StavCredits(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavCredits();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;
};

#endif
