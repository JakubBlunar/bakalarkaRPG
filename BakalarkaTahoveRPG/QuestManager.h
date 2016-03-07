#if !defined(QuestManager_h)
#define QuestManager_h
#include <deque>

class Hrac;

enum Event {
	ZABITIE_NPC,
	LOOTNUTIE_PREDMETU,
	VYHODENIE_PREDMETU
};

class Quest;

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

private:

	
	std::deque<Quest*>* nedokonceneQuesty;
	std::deque<Quest*>* dokonceneQuesty;
};

#endif