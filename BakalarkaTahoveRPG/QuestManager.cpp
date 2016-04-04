#include "QuestManager.h"
#include "Quest.h"
#include "Nepriatel.h"

#include "Loader.h"
#include "Hra.h"
#include "Stav.h"
#include "PopupOkno.h"
#include "AudioManager.h"

QuestManager::QuestManager()
{
	nedokonceneQuesty = new std::deque<Quest*>();
	dokonceneQuesty = new std::deque<Quest*>();
	nacitaneQuesty = new std::deque<Quest*>();
}


QuestManager::~QuestManager()
{
	
}

void QuestManager::pridajQuest(Quest* quest) const
{
	if (!maQuest(quest->Getnazov())) {
		nedokonceneQuesty->push_front(quest);
		quest->setStav(StavQuestu::ROZROBENY);
		Loader::Instance()->Gethra()->Getstav("hranieHry")->zobrazPopup(new PopupOkno("You have got a new quest: " + quest->Getnazov()));
		AudioManager::Instance()->playEfekt("beep");
	}
}


std::deque<Quest*>* QuestManager::Getnedokoncenequesty() const
{
	return nedokonceneQuesty;
}

std::deque<Quest*>* QuestManager::Getdokoncenequesty() const
{
	return dokonceneQuesty;
}

void QuestManager::udalost(QuestEvent paEvent, void* param) const
{

	Nepriatel* nepriatel;
	Predmet* predmet;

	switch (paEvent)
	{
	case QuestEvent::ZABITIE_NPC:
		nepriatel = static_cast<Nepriatel*>(param);
		for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
			nedokonceneQuesty->at(i)->zabitieNpc(nepriatel);
		}
		break;
	case QuestEvent::LOOTNUTIE_PREDMETU:
		predmet = static_cast<Predmet*>(param);
		for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
			nedokonceneQuesty->at(i)->lootnutiePredmetu(predmet);
		}
		break;
	case QuestEvent::VYHODENIE_PREDMETU:
		for (unsigned int i = 0; i< nedokonceneQuesty->size(); i++) {
			nedokonceneQuesty->at(i)->kontrola();
		}
		break;
	}

}

bool QuestManager::maQuest(std::string paNazov) const
{
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

Quest* QuestManager::getQuest(std::string paNazov) const
{
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
			if (q->Getnasledujuci() != nullptr) {
				if(q->Getnasledujuci()->Getautoaccept()) pridajQuest(q->Getnasledujuci());
			}
		}
	}

}

void QuestManager::nacitanyQuest(Quest* paQuest) const
{
	nacitaneQuesty->push_back(paQuest);
}

deque<Quest*>* QuestManager::Getnacitanequesty() const
{
	return nacitaneQuesty;
}

Quest* QuestManager::Getzaciatocnyquestnpc(string menoNpc) const
{

	for (unsigned int i = 0; i < nacitaneQuesty->size(); i++) {
		if (nacitaneQuesty->at(i)->Getstartnpc() == menoNpc && nacitaneQuesty->at(i)->Getpredchadzajuci() == nullptr && nacitaneQuesty->at(i)->Getstav() == StavQuestu::NEPRIJATY) {
			if (std::find(nedokonceneQuesty->begin(), nedokonceneQuesty->end(), nacitaneQuesty->at(i)) == nedokonceneQuesty->end()) {
				return nacitaneQuesty->at(i);
			}
		}
		else if(nacitaneQuesty->at(i)->Getstartnpc() == menoNpc && nacitaneQuesty->at(i)->Getpredchadzajuci() != nullptr && nacitaneQuesty->at(i)->Getpredchadzajuci()->Getstav() == StavQuestu::DOKONCENY  && nacitaneQuesty->at(i)->Getstav() == StavQuestu::NEPRIJATY)
		{
			if (std::find(nedokonceneQuesty->begin(), nedokonceneQuesty->end(), nacitaneQuesty->at(i)) == nedokonceneQuesty->end()) {
				return nacitaneQuesty->at(i);
			}
		}
	}
	return nullptr;
}

Quest* QuestManager::Getkonciaciquestnpc(string menoNpc) const
{
	for (unsigned int i = 0; i < nedokonceneQuesty->size(); i++) {
		if (nedokonceneQuesty->at(i)->Getendnpc() == menoNpc) {
			return nedokonceneQuesty->at(i);
		}
	}
	return nullptr;
}

Quest* QuestManager::GetNacitanyQuest(string paNazov) const
{
	for (unsigned int i = 0; i < nacitaneQuesty->size(); i++) {
		if (nacitaneQuesty->at(i)->Getnazov() == paNazov) return nacitaneQuesty->at(i);
	}
	return nullptr;
}

void QuestManager::pridajDoNedokoncenych(Quest* paQuest) const
{
	if (GetNacitanyQuest(paQuest->Getnazov()) == nullptr) {
		nacitaneQuesty->push_back(paQuest);
	}

	nedokonceneQuesty->push_back(paQuest);

}

void QuestManager::pridajDoDokoncenych(Quest* paQuest) const
{
	if (GetNacitanyQuest(paQuest->Getnazov()) == nullptr) {
		nacitaneQuesty->push_back(paQuest);
	}

	dokonceneQuesty->push_back(paQuest);
}

int QuestManager::Getpocetquestov() const
{
	return nedokonceneQuesty->size() + dokonceneQuesty->size();
}
