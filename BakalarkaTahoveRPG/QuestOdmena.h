#if !defined(QuestOdmena_h)
#define QuestOdmena_h

#include <vector>
using namespace std;

class Predmet;

class QuestOdmena
{
public:
	QuestOdmena(int pocetXp,int pocetZlata);
	~QuestOdmena();
	vector<Predmet*>* getPredmety();
	void pridajPredmet(Predmet* paPredmet);
	int Getpocetzlata();
	int Getpocetxp();
private:
	int pocetZlata;
	int pocetXp;
	vector<Predmet*>* predmety;
};

#endif