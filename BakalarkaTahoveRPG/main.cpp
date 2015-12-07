#include "iostream"
#include "Hra.h"


int main()
{
	Hra* hra = new Hra();
	hra->start();
	delete(hra);

    return 0;
}

