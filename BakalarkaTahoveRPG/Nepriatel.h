#if !defined(nepriatel_h)
#define nepriatel_h

#include "Statistika.h"

#include "Npc.h"
#include <map>

class Predmet;

/// <summary>
/// Specifick� npc , ktor� mo�e napadnu� hr��a
/// </summary>
class Nepriatel : public Npc
{

public:
	/// <summary>
	/// Vytvori nepriatela
	/// </summary>
	/// <param name="paMeno">meno nepriatela</param>
	/// <param name="obrazok">obrazok ako bude vyzerat</param>
	/// <param name="dialog">dialog s hracom</param>
	/// <param name="paStatistika">ak� bude ma� schopnosti a vlastnosti</param>
	Nepriatel(std::string paMeno,std::string obrazok, DialogovyStrom* dialog, Statistika* paStatistika);
	virtual ~Nepriatel();

	/// <summary>
	/// Vrati nepriatelovu statistiku
	/// </summary>
	/// <returns>nepriatelova statistika</returns>
	Statistika* Getstatistika() const;

	/// <summary>
	/// Nastavi nepriatelovu statistiku na novu
	/// </summary>
	/// <param name="newVal">nova statistika</param>
	void Setstatistika(Statistika* newVal);

	/// <summary>
	/// Metoda rozhodne aku akciu chce nepriatel pozuzit proti hracovi
	/// </summary>
	/// <param name="cooldowny">zoznam akcii ktor� maju cooldowny</param>
	/// <returns>vybrata akcia</returns>
	Akcia* vyberAkciu(std::map<Akcia*,int>* cooldowny) const;

	/// <summary>
	/// Vrati obrazok ako nepriatel vyzer�
	/// </summary>
	/// <returns>obrazok nepriatela</returns>
	sf::Sprite* Getobrazok() const;

	/// <summary>
	/// Prida predmet ktor� moze padnut ak m� hra� ur�it� quest
	/// </summary>
	/// <param name="nazovQuestu">nazov questu</param>
	/// <param name="p">predmet ktor� na nom m� pada�</param>
	void pridajDropItem(std::string nazovQuestu, Predmet* p) const;

	/// <summary>
	/// Vrati cel� quest drop
	/// </summary>
	/// <returns>zoznam questov a predmety ktor� na nich maju pada�</returns>
	std::map< std::string, Predmet*>* dropQuestPredmetov() const;
private:
	Statistika* statistika;
	sf::Texture textura;
	sf::Sprite* obrazok;
	
	std::map< std::string,Predmet*>* questDrop;

};
#endif
