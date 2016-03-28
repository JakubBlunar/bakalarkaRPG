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

class Loader {
public:
	static Loader* Instance();
	void setHra(Hra* paHra);
	void nacitajMapu(string paMeno,int paX,int paY,int smer);
	sf::Font* nacitajFont(string menoFontu);
	DialogovyStrom* nacitajDialog(string paMeno) const;
	Nepriatel* nacitajNepriatela(string paMeno) const;
	vector<Predmet*>* nacitajObchod(string paMeno) const;
	Quest* nacitajQuest(string paMeno) const;
	bool Getnacitava() const;
	Hra* Gethra() const;
	
	Zameranie* nacitajZameranie(string paMeno) const;

	bool save() const;
	void load();

private:
	Loader(): hra(nullptr)
	{
		nacitava = false;
	};
	Loader(Loader const&): nacitava(false), hra(nullptr)
	{};
	Loader& operator=(Loader const&) const
	{
		return *instancia;
	};
	static Loader* instancia;

	bool nacitava;

	Hra* hra;
	map<int, sf::Texture*> textury;
	map<string, Mapa*> nacitaneMapy;
	
	void nacitajNpc(string menoMapy, Mapa* mapa) const;
	
	map<string, sf::Font*> nacitaneFonty;
	
	Predmet* parsujPredmet(Json::Value jPredmet) const;

	int  nahodneCislo(int min, int max) const;
	void zobrazLoadingScreen() const;
};

#endif // LOADER.H