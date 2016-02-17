
#if !defined(PopupOkno_h)
#define PopupOkno_h

#include <string>
#include <queue>
class PopupOkno
{
public:
	PopupOkno(std::string paText);
	~PopupOkno();
	void pridajStranku(std::string text);
	std::string aktualnaStrana();
	std::string dajDalsi();
	bool skoncil();
private:
	std::queue<std::string> texty;
	bool koniec;
};


#endif

