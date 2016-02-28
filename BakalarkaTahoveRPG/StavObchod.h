#if !defined(StavObchod_h)
#define StavObchod_h

#include "StavInventar.h"
#include <vector>

class Predmet;

class StavObchod :
	public StavInventar
{
public:
	StavObchod(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavObchod();

	void onEnter();
	void onExit();
	void render();
	void update(double delta);

	void nacitajObchod(std::string aky);
private:
	enum {KUPA,PREDAJ} typObchodu;
	std::vector<Predmet*>* dostupnePredmety;
	


};
#endif
