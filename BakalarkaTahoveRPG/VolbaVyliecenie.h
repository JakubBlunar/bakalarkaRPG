#if !defined(VolbaVyliecenie_h)
#define VolbaVyliecenie_h

#include "DialogovyStrom.h"

class Hrac;

class VolbaVyliecenie :public DialogVolba
{
public:
	VolbaVyliecenie(string paText, int dalsia);
	~VolbaVyliecenie();
	void akcia(Hrac* hrac) override;
};

#endif