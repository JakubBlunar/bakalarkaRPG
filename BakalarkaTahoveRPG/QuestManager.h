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
	deque<Quest*>* Getnedokoncenequesty();
	deque<Quest*>* Getdokoncenequesty();
	bool maQuest(string paNazovQuestu);
	void udalost(QuestEvent e, void* param);
	Quest* getQuest(string paNazov);

	void dokoncenieQuestu(string meno,Hrac* hrac);
	void nacitanyQuest(Quest* paQuest);

	Quest* GetNacitanyQuest(string paNazov);
	deque<Quest*>* Getnacitanequesty();

	Quest* Getzaciatocnyquestnpc(string menoNpc);
	Quest* Getkonciaciquestnpc(string menoNpc);
private:
	deque<Quest*>* nacitaneQuesty;
	
	deque<Quest*>* nedokonceneQuesty;
	deque<Quest*>* dokonceneQuesty;

};

#endif