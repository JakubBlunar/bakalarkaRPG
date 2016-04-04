#if !defined(QuestManager_h)
#define QuestManager_h
#include <deque>

using namespace std;

class Quest;
class Hrac;

/// <summary>
/// Event ktorı sa moe vyskytnu pri plneni questu
/// </summary>
enum QuestEvent {
	ZABITIE_NPC,
	LOOTNUTIE_PREDMETU,
	VYHODENIE_PREDMETU
};


/// <summary>
/// Spravca questov ktorı organizuje hraèove questy
/// </summary>
class QuestManager
{
public:
	/// <summary>
	/// Vytvorenie nového manaera
	/// </summary>
	QuestManager();
	~QuestManager();

	//questy

	/// <summary>
	/// Pridanie questu hracovi , prida sa do jeho nedokoncenıch questov
	/// </summary>
	/// <param name="quest"></param>
	void pridajQuest(Quest* quest) const;

	/// <summary>
	/// Vrati hracove nedokoncene questy
	/// </summary>
	/// <returns>zoznam nedokoncenıch questov</returns>
	deque<Quest*>* Getnedokoncenequesty() const;

	/// <summary>
	/// Vrati hracove dokoncene questy
	/// </summary>
	/// <returns>zoznam dokoncenıch questov</returns>
	deque<Quest*>* Getdokoncenequesty() const;

	/// <summary>
	/// Skontroluje èi hraè ma dany quest , medzi dokoncenımi aj prijatımi
	/// </summary>
	/// <param name="paNazovQuestu">nazov questu</param>
	/// <returns>true, false podla toho ci najde</returns>
	bool maQuest(string paNazovQuestu) const;

	/// <summary>
	/// Spracovanie udalosti vzniknutej v hre ktorá je spojená s questom
	/// </summary>
	/// <param name="e">udalost</param>
	/// <param name="param">nejakı parameter zalezi podla udalosti</param>
	void udalost(QuestEvent e, void* param) const;

	/// <summary>
	/// Vrati quest ktorı ma danı nazov
	/// </summary>
	/// <param name="paNazov">nazov questu</param>
	/// <returns>najdenı quest</returns>
	Quest* getQuest(string paNazov) const;

	/// <summary>
	/// Dokoncenie questu , ktorı ma danı nazov
	/// </summary>
	/// <param name="meno">nazov questu</param>
	/// <param name="hrac">hrac ktorı dokonèil quest</param>
	void dokoncenieQuestu(string meno,Hrac* hrac);

	/// <summary>
	/// Loader oznamuje manaerovi e naèital tento quest , ten quest sa ulozi do nacitanıch questov
	/// </summary>
	/// <param name="paQuest">nacitanı quest</param>
	void nacitanyQuest(Quest* paQuest) const;

	/// <summary>
	/// Vrati nacitanı quest s danım menom
	/// </summary>
	/// <param name="paNazov">meno questu</param>
	/// <returns>nacitanı quest alebo nullptr ak nenajde</returns>
	Quest* GetNacitanyQuest(string paNazov) const;
	
	/// <summary>
	/// Vrati nacitane questy
	/// </summary>
	/// <returns>zoznam nacitanıch questov</returns>
	deque<Quest*>* Getnacitanequesty() const;

	/// <summary>
	/// Vrati quest ktorı ešte nie je splnenı, a zaèina u daneho npc
	/// </summary>
	/// <param name="menoNpc">meno npc</param>
	/// <returns>najdenı quest alebo nullptr</returns>
	Quest* Getzaciatocnyquestnpc(string menoNpc) const;

	/// <summary>
	/// Vrati quest ktorı je rozrobenı a konèí u daneho npc
	/// </summary>
	/// <param name="menoNpc">meno npc</param>
	/// <returns>quest alebo nullptr</returns>
	Quest* Getkonciaciquestnpc(string menoNpc) const;

	/// <summary>
	/// Prida quest do dokoncenıch questov
	/// </summary>
	/// <param name="paQuest">quest na pridanie</param>
	void pridajDoNedokoncenych(Quest* paQuest) const;

	/// <summary>
	/// Prida quest do nedokoncenıch questov
	/// </summary>
	/// <param name="paQuest">quest na pridanie</param>
	void pridajDoDokoncenych(Quest* paQuest) const;

	/// <summary>
	/// Vrati pocet dokoncenıch a nedokoncenıch questov
	/// </summary>
	/// <returns>int celkovı pocet</returns>
	int Getpocetquestov() const;
private:
	deque<Quest*>* nacitaneQuesty;
	
	deque<Quest*>* nedokonceneQuesty;
	deque<Quest*>* dokonceneQuesty;

};

#endif