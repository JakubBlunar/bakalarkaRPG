#if !defined(VolbaObchodovanie_h)
#define VolbaObchodovanie_h

#include "DialogovyStrom.h"

class Hrac;

class VolbaObchodovanie :public DialogVolba
{
public:
	VolbaObchodovanie(string paText, int dalsia,std::string akyObchod);
	~VolbaObchodovanie();
	void akcia(Hrac* hrac) override;
private:
	std::string obchod;
};

#endif