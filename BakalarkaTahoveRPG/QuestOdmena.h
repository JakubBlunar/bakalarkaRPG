#if !defined(QuestOdmena_h)
#define QuestOdmena_h

#include <vector>
using namespace std;

class Predmet;

/// <summary>
/// Trieda predstavuje všetko èo hraè dostane za dokoncenie questu
/// </summary>
class QuestOdmena
{
public:
	/// <summary>
	/// Vytvorí novu odmenu
	/// </summary>
	/// <param name="pocetXp">kolko hrac dostane xp</param>
	/// <param name="pocetZlata">kolko hrac dostane zlata</param>
	QuestOdmena(int pocetXp,int pocetZlata);
	~QuestOdmena();

	/// <summary>
	/// Vrati predmety , ktoré hráè dostane za dokoncenie questu
	/// </summary>
	/// <returns>zoznam predmetov</returns>
	vector<Predmet*>* getPredmety() const;

	/// <summary>
	/// Pridá predmet do zoznamu odmien
	/// </summary>
	/// <param name="paPredmet">predmet ktorý hrac dostane ako odmenu</param>
	void pridajPredmet(Predmet* paPredmet) const;

	/// <summary>
	/// Vrati pocet zlata ktoré hrác dostane za splnenie questu
	/// </summary>
	/// <returns>pocet zlata</returns>
	int Getpocetzlata() const;


	/// <summary>
	/// Vrati pocet xp ktoré hrác dostane za splnenie questu
	/// </summary>
	/// <returns>pocet xp</returns>
	int Getpocetxp() const;
private:
	int pocetZlata;
	int pocetXp;
	vector<Predmet*>* predmety;
};

#endif