#if !defined(nepriatel_h)
#define nepriatel_h

#include "Statistika.h"

#include "Npc.h"
#include <map>

class Predmet;

class Nepriatel : public Npc
{

public:
	Nepriatel(std::string paMeno,std::string obrazok, DialogovyStrom* dialog, Statistika* paStatistika);
	virtual ~Nepriatel();

	Statistika* Getstatistika() const;
	void Setstatistika(Statistika* newVal);
	Akcia* vyberAkciu(std::map<Akcia*,int>* cooldowny) const;
	sf::Sprite* Getobrazok() const;
	void pridajDropItem(std::string, Predmet*) const;
	std::map< std::string, Predmet*>* dropQuestPredmetov() const;
private:
	Statistika* statistika;
	sf::Texture textura;
	sf::Sprite* obrazok;
	
	std::map< std::string,Predmet*>* questDrop;

};
#endif
