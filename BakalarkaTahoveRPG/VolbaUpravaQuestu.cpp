#include "VolbaUpravaQuestu.h"
#include "Quest.h"
#include "QuestManager.h"
#include "Hrac.h"
#include "Loader.h"
#include "Hra.h"
#include "Stav.h"
#include "PopupOkno.h"

VolbaUpravaQuestu::VolbaUpravaQuestu(int dalsia, Quest* paQuest):DialogVolba("",dalsia)
{
	this->quest = paQuest;
}


VolbaUpravaQuestu::~VolbaUpravaQuestu()
{
}



void VolbaUpravaQuestu::akcia(Hrac* hrac) {


	if (!hrac->Getmanazerquestov()->maQuest(quest->Getnazov())) {
		hrac->Getmanazerquestov()->pridajQuest(quest);
		std::cout << "Pridanie questu " << quest->Getnazov() << std::endl;
		Loader::Instance()->Gethra()->dajStav("hranieHry")->zobrazPopup(new PopupOkno("Uspesne si prijal quest " + quest->Getnazov() ));
	}
	else {

		Quest* quest = hrac->Getmanazerquestov()->getQuest(this->quest->Getnazov());

		switch (quest->Getstav())
		{
		case StavQuestu::ROZROBENY:
			
			break;
		case StavQuestu::SPLNENIE_POZIADAVIEK:
			hrac->Getmanazerquestov()->dokoncenieQuestu(this->quest->Getnazov(), hrac);
			break;
		case StavQuestu::DOKONCENY:
			
			break;
		default:
			
			break;
		}

	}

}

std::string VolbaUpravaQuestu::Gettext() {
	
	Hrac* hrac = Loader::Instance()->Gethra()->GetHrac();

	if (!hrac->Getmanazerquestov()->maQuest(quest->Getnazov())) {
		if (texty.count(StavQuestu::NEPRIJATY)) {
			return texty.at(StavQuestu::NEPRIJATY);
		}
	}
	else {
		Quest* quest = hrac->Getmanazerquestov()->getQuest(this->quest->Getnazov());

		switch (quest->Getstav())
		{
		case StavQuestu::ROZROBENY:
			if (texty.count(StavQuestu::ROZROBENY)) {
				return texty.at(StavQuestu::ROZROBENY);
			}
			break;
		case StavQuestu::SPLNENIE_POZIADAVIEK:
			if (texty.count(StavQuestu::SPLNENIE_POZIADAVIEK)) {
				return texty.at(StavQuestu::SPLNENIE_POZIADAVIEK);
			}
			break;
		case StavQuestu::DOKONCENY:
			if (texty.count(StavQuestu::DOKONCENY)) {
				return texty.at(StavQuestu::DOKONCENY);
			}
			break;
		default:
			return "Neznamy";
			break;
		}
		

	}
	return "Neznamy";
}

void VolbaUpravaQuestu::vlozText(StavQuestu paStav, std::string paText) {
	texty.insert_or_assign(paStav, paText);
}

Quest* VolbaUpravaQuestu::getQuest() {
	return quest;
}