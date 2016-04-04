#ifndef loader_h
#define loader_h
#include <SFML\Graphics.hpp>
#include <map>
#include <vector>

#include "json.h"

using namespace std;

class Npc;
class Hra;
class Mapa;
class DialogovyStrom;
class Nepriatel;
class Predmet;
class Quest;
class Zameranie;


/// <summary>
/// Loader sluzi na nacitavanie obsahu zo suborov
/// </summary>
class Loader {
public:

	/// <summary>
	/// Staticka metoda , sluzi ako konstruktor
	/// </summary>
	/// <returns>Instancia</returns>
	static Loader* Instance();

	/// <summary>
	/// Nastavi loaderovi instanciu hry
	/// </summary>
	/// <param name="paHra">aktualna hra</param>
	void setHra(Hra* paHra);

	/// <summary>
	/// Metoda ktorá nacita mapu , ulozi ju do nacitaných map a nastavi ju do stav hrania hry
	/// </summary>
	/// <param name="paMeno">meno mapy</param>
	/// <param name="paX">pozicia x na ktoru polozit hraca</param>
	/// <param name="paY">pozicia y na ktoru polozit hraca</param>
	/// <param name="smer">smer pohladu hraca</param>
	void nacitajMapu(string paMeno,int paX,int paY,int smer);

	/// <summary>
	/// Metoda ktorá nacita font
	/// </summary>
	/// <param name="menoFontu">nazov suboru s fontom</param>
	/// <returns>nacitany font</returns>
	sf::Font* nacitajFont(string menoFontu);

	/// <summary>
	/// Metoda ktorá nacita dialog
	/// </summary>
	/// <param name="paMeno">nazov suboru v ktorom je ulozeny dialog</param>
	/// <returns>Nacitany dialog</returns>
	DialogovyStrom* nacitajDialog(string paMeno) const;

	/// <summary>
	/// Metoda ktora nacita nepriatela
	/// </summary>
	/// <param name="paMeno">meno suboru s nepriatelom</param>
	/// <returns>nacitany nepriatel</returns>
	Nepriatel* nacitajNepriatela(string paMeno) const;

	/// <summary>
	/// Nacita predmety ktoré su v danom obchode
	/// </summary>
	/// <param name="paMeno">subor v ktorom su ulozene predmety obchodu</param>
	/// <returns>zoznam nacitaných suborov</returns>
	vector<Predmet*>* nacitajObchod(string paMeno) const;

	/// <summary>
	/// Metoda nacita quest a prida ho do nacitaných questov v spravcovi questov
	/// </summary>
	/// <param name="paMeno">nazov suboru s questom</param>
	/// <returns>nacitany quest</returns>
	Quest* nacitajQuest(string paMeno) const;

	/// <summary>
	/// Vrati aktualnu hru
	/// </summary>
	/// <returns>aktualna hra</returns>
	Hra* Gethra() const;
	
	/// <summary>
	/// Nacita zameranie zo suboru
	/// </summary>
	/// <param name="paMeno">nazov suboru zo zameranim</param>
	/// <returns>nacitane zameranie</returns>
	Zameranie* nacitajZameranie(string paMeno) const;

	/// <summary>
	/// Ulozi aktualny progress hraca do suboru
	/// </summary>
	/// <returns>true ak sa podarilo, false ak nastala chyba</returns>
	bool save() const;

	/// <summary>
	/// Nacita hru zo suboru
	/// </summary>
	void load();

private:

	/// <summary>
	/// vytvorenie loadera
	/// </summary>
	Loader(): hra(nullptr)
	{
	};
	Loader(Loader const&): hra(nullptr)
	{};
	Loader& operator=(Loader const&) const
	{
		return *instancia;
	};
	static Loader* instancia;

	Hra* hra;
	map<int, sf::Texture*> textury;
	map<string, Mapa*> nacitaneMapy;
	
	/// <summary>
	/// Nacita npc na mape a prida ich do mapy
	/// </summary>
	/// <param name="menoMapy">meno suboru mapy</param>
	/// <param name="mapa">nacitana mapa</param>
	void nacitajNpc(string menoMapy, Mapa* mapa) const;
	
	map<string, sf::Font*> nacitaneFonty;
	
	/// <summary>
	/// Rozparsuje Json format predmetu do Objektu predmet
	/// </summary>
	/// <param name="jPredmet">json objekt predmet</param>
	/// <returns>Vytvoreny predmet</returns>
	Predmet* parsujPredmet(Json::Value jPredmet) const;

	/// <summary>
	/// Vrati nahodne cislo z rozsahu od do
	/// </summary>
	/// <param name="min">minimum</param>
	/// <param name="max">maximum</param>
	/// <returns>vygenerované cislo</returns>
	int  nahodneCislo(int min, int max) const;

	/// <summary>
	/// Zmaze vsetko na okne a vykresli stav nacitania
	/// </summary>
	void zobrazLoadingScreen() const;
};

#endif // LOADER.H