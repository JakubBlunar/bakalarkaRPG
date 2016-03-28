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

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;

	void nacitajObchod(std::string aky);
private:
	enum {KUPA,PREDAJ} typObchodu;
	std::vector<Predmet*>* dostupnePredmety;
	


};
#endif
