#if !defined(StavLoading_h)
#define StavLoading_h
#include "Stav.h"

/// <summary>
/// Stav ktorý sa vykresli na zaèiatku naèítavania
/// </summary>
class StavLoading:public Stav
{
public:
	StavLoading(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavLoading();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

};

#endif