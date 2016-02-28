#if !defined(VolbaPridanieQuestu_h)
#define VolbaPridanieQuestu_h

#include "DialogovyStrom.h"

class Hrac;

class VolbaPridanieQuestu:public DialogVolba 
{
public:
	VolbaPridanieQuestu(string paText, int dalsia);
	~VolbaPridanieQuestu();
	void akcia(Hrac* hrac);
};

#endif