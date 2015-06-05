#ifndef test
#define test
#include<string>
#include<iostream>
using namespace std;
class converter{
protected:
	double ratio;
	virtual double convert(double src)=0;
	virtual string getsourcestring()=0;
	virtual string getdeststring()=0;
public:
	converter(double ratio){this->ratio=ratio;}
	void run(){
		double src;
		cout<<getsourcestring()<<"을 "<<getdeststring()<<"로 바꿉니다. ";
		cout<<getsourcestring()<<"을 입력하세요>> ";
		cin>>src;
		cout<<"변환 결과: "<<convert(src)<<getdeststring()<<endl;
	}
};

#endif