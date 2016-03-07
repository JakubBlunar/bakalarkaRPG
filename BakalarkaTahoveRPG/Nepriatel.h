#if !defined(nepriatel_h)
#define nepriatel_h

#include "Statistika.h"

#include "Npc.h"
#include <map>
#include <string>

class Predmet;

class Nepriatel : public Npc
{

public:
	Nepriatel(std::string paMeno,std::string obrazok, DialogovyStrom* dialog, Statistika* paStatistika);
	virtual ~Nepriatel();

	Statistika* Getstatistika();
	void Setstatistika(Statistika* newVal);
	Akcia* vyberAkciu(std::map<Akcia*,int>* cooldowny);
	sf::Sprite* Getobrazok();
	void pridajDropItem(std::string, Predmet*);
	std::map< std::string, Predmet*>* dropQuestPredmetov();
private:
	Statistika* statistika;
	sf::Texture textura;
	sf::Sprite* obrazok;
	
	std::map< std::string,Predmet*>* questDrop;

};
#endif
