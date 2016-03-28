#if !defined(VolbaPredQpolozkou_h)
#define VolbaPredQpolozkou_h

#include "DialogovyStrom.h"
#include "Quest.h"
#include <map>

class Hrac;
class VolbaPredQpolozkou :public DialogVolba
{
public:
	VolbaPredQpolozkou(int dalsia, Quest* paQuest);
	~VolbaPredQpolozkou();
	void akcia(Hrac* hrac) override;
	std::string Gettext() override;
	void vlozText(StavQuestu paStav, std::string paText);
	Quest* getQuest();
private:
	Quest* quest;
	std::map<StavQuestu, std::string> texty;
};

#endif