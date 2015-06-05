using namespace std;
//#define kmtomilex
#include"test2.h"

int main(){

#ifndef kmtomilex
	wontodollar wd(1010);
	wd.run();
#else
	kmtomile tomile(1.609344);
	tomile.run();
#endif
	return 0;
}