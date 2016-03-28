#if !defined(QuestManager_h)
#define QuestManager_h
#include <deque>

using namespace std;

class Quest;
class Hrac;

enum QuestEvent {
	ZABITIE_NPC,
	LOOTNUTIE_PREDMETU,
	VYHODENIE_PREDMETU
};



class QuestManager
{
public:
	QuestManager();
	~QuestManager();

	//questy
	void pridajQuest(Quest* quest);
	deque<Quest*>* Getnedokoncenequesty() const;
	deque<Quest*>* Getdokoncenequesty() const;
	bool maQuest(string paNazovQuestu) const;
	void udalost(QuestEvent e, void* param) const;
	Quest* getQuest(string paNazov) const;

	void dokoncenieQuestu(string meno,Hrac* hrac);
	void nacitanyQuest(Quest* paQuest) const;

	Quest* GetNacitanyQuest(string paNazov) const;
	deque<Quest*>* Getnacitanequesty() const;

	Quest* Getzaciatocnyquestnpc(string menoNpc) const;
	Quest* Getkonciaciquestnpc(string menoNpc) const;

	void pridajDoNedokoncenych(Quest* paQuest) const;
	void pridajDoDokoncenych(Quest* paQuest) const;
private:
	deque<Quest*>* nacitaneQuesty;
	
	deque<Quest*>* nedokonceneQuesty;
	deque<Quest*>* dokonceneQuesty;

};

#endif