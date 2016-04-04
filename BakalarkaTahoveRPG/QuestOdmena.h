#if !defined(QuestOdmena_h)
#define QuestOdmena_h

#include <vector>
using namespace std;

class Predmet;

/// <summary>
/// Trieda predstavuje v�etko �o hra� dostane za dokoncenie questu
/// </summary>
class QuestOdmena
{
public:
	/// <summary>
	/// Vytvor� novu odmenu
	/// </summary>
	/// <param name="pocetXp">kolko hrac dostane xp</param>
	/// <param name="pocetZlata">kolko hrac dostane zlata</param>
	QuestOdmena(int pocetXp,int pocetZlata);
	~QuestOdmena();

	/// <summary>
	/// Vrati predmety , ktor� hr�� dostane za dokoncenie questu
	/// </summary>
	/// <returns>zoznam predmetov</returns>
	vector<Predmet*>* getPredmety() const;

	/// <summary>
	/// Prid� predmet do zoznamu odmien
	/// </summary>
	/// <param name="paPredmet">predmet ktor� hrac dostane ako odmenu</param>
	void pridajPredmet(Predmet* paPredmet) const;

	/// <summary>
	/// Vrati pocet zlata ktor� hr�c dostane za splnenie questu
	/// </summary>
	/// <returns>pocet zlata</returns>
	int Getpocetzlata() const;


	/// <summary>
	/// Vrati pocet xp ktor� hr�c dostane za splnenie questu
	/// </summary>
	/// <returns>pocet xp</returns>
	int Getpocetxp() const;
private:
	int pocetZlata;
	int pocetXp;
	vector<Predmet*>* predmety;
};

#endif