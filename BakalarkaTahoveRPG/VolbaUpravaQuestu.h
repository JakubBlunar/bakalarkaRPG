#if !defined(VolbaUpravaQuestu_h)
#define VolbaUpravaQuestu_h

#include "DialogovyStrom.h"
#include "Quest.h"
#include <map>

class Hrac;


class VolbaUpravaQuestu:public DialogVolba 
{
public:
	VolbaUpravaQuestu(int dalsia,Quest* paQuest);
	~VolbaUpravaQuestu();
	void akcia(Hrac* hrac) override;
	std::string Gettext() override;
	void vlozText(StavQuestu paStav, std::string paText);
	Quest* getQuest() const;
private:
	Quest* quest;
	std::map<StavQuestu, std::string> texty;
};

#endif