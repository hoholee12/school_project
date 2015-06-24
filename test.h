#ifndef test
#define test
#include<string>
#include<iostream>
using namespace std;

class loopadder{
	string name;
	int x, y, sum;
	void read(){
		cout<<name<<":"<<endl;
		cout<<"처음 수에서 두번째 수까지 더합니다. 두 수를 입력하세요 >>";
		cin>>x>>y;
	}
	void write(){
		cout<<x<<"에서 "<<y<<"까지의 합 = "<<sum<<" 입니다."<<endl;
	}
protected:
	loopadder(string name=""){this->name=name;}
	int getx(){return x;}
	int gety(){return y;}
	virtual int calculate()=0;
public:
	void run(){
		read();
		sum=calculate();
		write();
	}
};

class abstractgate{
protected:
	bool x, y;
public:
	void set(bool x, bool y){this->x=x;this->y=y;}
	virtual bool operation()=0;
};

class abstractstack{
public:
	virtual bool push(int n)=0;
	virtual bool pop(int &n)=0;
	virtual int size()=0;
};

class shape{
protected:
	string name;
	int width, height;
public:
	shape(string name="", int width=0, int height=0){
		this->name=name; this->width=width; this->height=height;
	}
	virtual double getarea(){return 0;}
	string getname(){return name;}

};

template<class t> class mystack{
	int tos;
	t data[100];
public:
	mystack(){tos=-1;}
	void push(t element){
		if(tos==99){
			cout<<"stack full";
			return;
		}
		tos++;
		data[tos]=element;
	}
	t pop(){
		t retdata;
		if(tos==-1){
			cout<<"stack empty";
			return 0;
		}
		retdata=data[tos--];
		return retdata;
	}
};


#endif