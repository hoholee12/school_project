#ifndef test2
#define test2
#include"test.h"
#include<string>
#include<cstdlib>
#ifndef kmtomilex
class wontodollar: public converter{
public:
	wontodollar(double ratio): converter(1/ratio){}
	double convert(double src){
		return src*ratio;
	}
	string getsourcestring(){ return "원";}
	string getdeststring(){return "달러";}


};
#else
class kmtomile: public converter{
public:
	kmtomile(double ratio): converter(1/ratio){}
	double convert(double src){
		return src*ratio;
	}
	string getsourcestring(){ return "km";}
	string getdeststring(){return "mile";}


};
#endif


#endif