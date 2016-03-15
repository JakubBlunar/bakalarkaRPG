#if !defined(statistika_h)
#define statistika_h

#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include "Timer.h"

using namespace std;

class Predmet;
class Akcia;
class Efekt;


class Statistika
{

public:
	Statistika();
	Statistika(int paUroven, int paHp, int paHpMax, int paMp, int mpMax,int paSila, int paIntelekt, int paRychlost, int paObrana,map<int, Predmet*>* paObleceneVeci = new map<int,Predmet*>());
	virtual ~Statistika();

	map<Efekt*, sf::Time>* Getaktivneefekty();
	map<int, Predmet*>* Getoblecene();
	vector<Akcia*>* Getakcie();
	void vlozAkciu(Akcia* paAkcia);
	void pridajEfekt(Efekt* paEfekt, sf::Time aktivnyDo);
	void zrusEfekt(Efekt* paEfekt);

	double Getsancanauhyb();
	double Getodolnostvociposkodeniu();
	int Getrychlostutoku();

	int dajUroven();
	int Gethp();
	int GethpMax();
	int Getintelekt();
	int Getmp();
	int GetmpMax();
	int Getobrana();
	int Getrychlost();
	int Getsila();
	int Getskusenosti();
	int Statistika::Getstat(string aky);
	void Sethp(int novaHodnota);
	void SethpMax(int novaHodnota);
	void Setintelekt(int novaHodnota);
	void Setmp(int novaHodnota);
	void Setobrana(int novaHodnota);
	void Setrychlost(int novaHodnota);
	void Setsila(int novaHodnota);
	void Setskusenosti(int novaHodnota);
	void zvysStat(int kolko, string paCo);
	void pridajXp(int pocet);
	void setUroven(int paUroven);

	void setCombat(bool paNa);

	void prepocitajPoskodenia();
	int Getminposkodenie();
	int Getmaxposkodenie();
private:
	int hp;
	int hpMax;
	int intelekt;
	int mp;
	int mpMax;
	int obrana;
	int rychlost;
	int sila;
	int skusenosti;
	int uroven;
	int minPoskodenie;
	int maxPoskodenie;

	vector<Akcia*>* akcie;
	map<int, Predmet*>* oblecene;
	map<Efekt*, sf::Time>* aktivneEfekty;

	Timer timerMp;
	sf::Time poslednaObnova;
	bool combat;
};
#endif 
