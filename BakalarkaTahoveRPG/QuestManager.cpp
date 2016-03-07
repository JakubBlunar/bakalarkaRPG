#include "QuestManager.h"
#include "Quest.h"
#include "Nepriatel.h"


QuestManager::QuestManager()
{
	nedokonceneQuesty = new std::deque<Quest*>();
	dokonceneQuesty = new std::deque<Quest*>();
}


QuestManager::~QuestManager()
{
	
}

void QuestManager::pridajQuest(Quest* quest) {
	nedokonceneQuesty->push_front(quest);
	quest->setStav(StavQuestu::ROZROBENY);
}


std::deque<Quest*>* QuestManager::Getnedokoncenequesty() {
	return nedokonceneQuesty;
}

std::deque<Quest*>* QuestManager::Getdokoncenequesty() {
	return dokonceneQuesty;
}

void QuestManager::udalost(Event paEvent, void* param) {

	Nepriatel* nepriatel;
	Predmet* predmet;

	switch (paEvent)
	{
	case Event::ZABITIE_NPC:
		nepriatel = (Nepriatel*)param;
		for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
			nedokonceneQuesty->at(i)->zabitieNpc(nepriatel);
		}
		break;
	case Event::LOOTNUTIE_PREDMETU:
		predmet = (Predmet*)param;
		for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
			nedokonceneQuesty->at(i)->lootnutiePredmetu(predmet);
		}
		break;
	case Event::VYHODENIE_PREDMETU:
		for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
			nedokonceneQuesty->at(i)->kontrola();
		}
		break;
	}

}

bool QuestManager::maQuest(std::string paNazov) {
	bool ma = false;

	for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
		if (nedokonceneQuesty->at(i)->Getnazov() == paNazov) {
			ma = true;
		}
	}

	for (unsigned int i = 0; i< dokonceneQuesty->size(); i++) {
		if (dokonceneQuesty->at(i)->Getnazov() == paNazov) {
			ma = true;
		}
	}
	return ma;
}

Quest* QuestManager::getQuest(std::string paNazov) {
	for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
		if (nedokonceneQuesty->at(i)->Getnazov() == paNazov) {
			return nedokonceneQuesty->at(i);
		}
	}

	for (unsigned int i = 0; i< dokonceneQuesty->size(); i++) {
		if (dokonceneQuesty->at(i)->Getnazov() == paNazov) {
			return dokonceneQuesty->at(i);
		}
	}
	return nullptr;
}


void QuestManager::dokoncenieQuestu(std::string meno, Hrac* hrac) {

	Quest* q = nullptr;
	for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
		if (nedokonceneQuesty->at(i)->Getnazov() == meno) {
			q = nedokonceneQuesty->at(i);
			nedokonceneQuesty->erase(nedokonceneQuesty->begin() + i);
			dokonceneQuesty->push_back(q);
			q->dokonciSa(hrac);

		}
	}

}