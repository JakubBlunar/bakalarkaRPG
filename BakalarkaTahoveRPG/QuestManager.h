#if !defined(QuestManager_h)
#define QuestManager_h
#include <deque>

class Quest;
class Hrac;

enum Event {
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
	std::deque<Quest*>* Getnedokoncenequesty();
	std::deque<Quest*>* Getdokoncenequesty();
	bool maQuest(std::string paNazovQuestu);
	void udalost(Event, void* param);
	Quest* getQuest(std::string paNazov);

	void dokoncenieQuestu(std::string meno,Hrac* hrac);
	void nacitanyQuest(Quest* paQuest);
	std::deque<Quest*>* Getnacitanequesty();
	
	Quest* Getzaciatocnyquestnpc(std::string menoNpc);
	Quest* Getkonciaciquestnpc(std::string menoNpc);
private:
	std::deque<Quest*>* nacitaneQuesty;
	
	std::deque<Quest*>* nedokonceneQuesty;
	std::deque<Quest*>* dokonceneQuesty;

};

#endif