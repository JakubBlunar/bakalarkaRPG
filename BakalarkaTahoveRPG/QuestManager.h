#if !defined(QuestManager_h)
#define QuestManager_h
#include <deque>

using namespace std;

class Quest;
class Hrac;

/// <summary>
/// Event ktor� sa mo�e vyskytnu� pri plneni questu
/// </summary>
enum QuestEvent {
	ZABITIE_NPC,
	LOOTNUTIE_PREDMETU,
	VYHODENIE_PREDMETU
};


/// <summary>
/// Spravca questov ktor� organizuje hra�ove questy
/// </summary>
class QuestManager
{
public:
	/// <summary>
	/// Vytvorenie nov�ho mana�era
	/// </summary>
	QuestManager();
	~QuestManager();

	//questy

	/// <summary>
	/// Pridanie questu hracovi , prida sa do jeho nedokoncen�ch questov
	/// </summary>
	/// <param name="quest"></param>
	void pridajQuest(Quest* quest) const;

	/// <summary>
	/// Vrati hracove nedokoncene questy
	/// </summary>
	/// <returns>zoznam nedokoncen�ch questov</returns>
	deque<Quest*>* Getnedokoncenequesty() const;

	/// <summary>
	/// Vrati hracove dokoncene questy
	/// </summary>
	/// <returns>zoznam dokoncen�ch questov</returns>
	deque<Quest*>* Getdokoncenequesty() const;

	/// <summary>
	/// Skontroluje �i hra� ma dany quest , medzi dokoncen�mi aj prijat�mi
	/// </summary>
	/// <param name="paNazovQuestu">nazov questu</param>
	/// <returns>true, false podla toho ci najde</returns>
	bool maQuest(string paNazovQuestu) const;

	/// <summary>
	/// Spracovanie udalosti vzniknutej v hre ktor� je spojen� s questom
	/// </summary>
	/// <param name="e">udalost</param>
	/// <param name="param">nejak� parameter zalezi podla udalosti</param>
	void udalost(QuestEvent e, void* param) const;

	/// <summary>
	/// Vrati quest ktor� ma dan� nazov
	/// </summary>
	/// <param name="paNazov">nazov questu</param>
	/// <returns>najden� quest</returns>
	Quest* getQuest(string paNazov) const;

	/// <summary>
	/// Dokoncenie questu , ktor� ma dan� nazov
	/// </summary>
	/// <param name="meno">nazov questu</param>
	/// <param name="hrac">hrac ktor� dokon�il quest</param>
	void dokoncenieQuestu(string meno,Hrac* hrac);

	/// <summary>
	/// Loader oznamuje mana�erovi �e na�ital tento quest , ten quest sa ulozi do nacitan�ch questov
	/// </summary>
	/// <param name="paQuest">nacitan� quest</param>
	void nacitanyQuest(Quest* paQuest) const;

	/// <summary>
	/// Vrati nacitan� quest s dan�m menom
	/// </summary>
	/// <param name="paNazov">meno questu</param>
	/// <returns>nacitan� quest alebo nullptr ak nenajde</returns>
	Quest* GetNacitanyQuest(string paNazov) const;
	
	/// <summary>
	/// Vrati nacitane questy
	/// </summary>
	/// <returns>zoznam nacitan�ch questov</returns>
	deque<Quest*>* Getnacitanequesty() const;

	/// <summary>
	/// Vrati quest ktor� e�te nie je splnen�, a za�ina u daneho npc
	/// </summary>
	/// <param name="menoNpc">meno npc</param>
	/// <returns>najden� quest alebo nullptr</returns>
	Quest* Getzaciatocnyquestnpc(string menoNpc) const;

	/// <summary>
	/// Vrati quest ktor� je rozroben� a kon�� u daneho npc
	/// </summary>
	/// <param name="menoNpc">meno npc</param>
	/// <returns>quest alebo nullptr</returns>
	Quest* Getkonciaciquestnpc(string menoNpc) const;

	/// <summary>
	/// Prida quest do dokoncen�ch questov
	/// </summary>
	/// <param name="paQuest">quest na pridanie</param>
	void pridajDoNedokoncenych(Quest* paQuest) const;

	/// <summary>
	/// Prida quest do nedokoncen�ch questov
	/// </summary>
	/// <param name="paQuest">quest na pridanie</param>
	void pridajDoDokoncenych(Quest* paQuest) const;

	/// <summary>
	/// Vrati pocet dokoncen�ch a nedokoncen�ch questov
	/// </summary>
	/// <returns>int celkov� pocet</returns>
	int Getpocetquestov() const;
private:
	deque<Quest*>* nacitaneQuesty;
	
	deque<Quest*>* nedokonceneQuesty;
	deque<Quest*>* dokonceneQuesty;

};

#endif