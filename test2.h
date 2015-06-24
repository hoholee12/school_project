#ifndef test2
#define test2
#include"test.h"
#include<string>
#include<cstdlib>

class forloopadder: public loopadder{
public:
	forloopadder(string name): loopadder(name){}
	int calculate(){
		int tmp=0;
		for(int i=getx();i<=gety();i++){
			tmp+=i;
		}
		return tmp;
	}

};

class whileloopadder: public loopadder{
public:
	whileloopadder(string name): loopadder(name){}
	int calculate(){
		int tmp=0;
		int i=getx();
		while(i<=gety()){
			tmp+=i;
			i++;
		}
		return tmp;
	}

};

class dowhileloopadder: public loopadder{
public:
	dowhileloopadder(string name): loopadder(name){}
	int calculate(){
		int tmp=0;
		int i=getx();
		do{
			tmp+=i;
			i++;
		}while(i<=gety());
		return tmp;
	}

};



class andgate: public abstractgate{
public:
	andgate(): abstractgate(){}
	bool operation(){
		return x&&y;
		
	}
};

class orgate: public abstractgate{
public:
	orgate(): abstractgate(){}
	bool operation(){
		return x||y;
		
	}
};

class xorgate: public abstractgate{
public:
	xorgate(): abstractgate(){}
	bool operation(){
		return !(x||y);
		
	}
};

#include<climits>

class intstack: public abstractstack{
	int *stack= new int [INT_MAX];
public:
	bool push(int n){
		for(int i=0; i<INT_MAX; i++){
			if(!stack[i]){
				stack[i]=n;
				break;
			}
		}
		return true;
		
	}
	bool pop(int &n){
		for(int i=0; i<INT_MAX; i++){
			if(!stack[i]){
				n=stack[i-1];
				stack[i-1]=0;
				break;
			}
		}
	
		return true;
	}
	int size(){
		for(int i=0;i<INT_MAX;i++){
			if(!stack[i]){
				return i;
			}
		}
		return 0;
	}


};

class oval: public shape{
public:
	oval(string name="", int width=0, int height=0): shape(name, width, height){}
	double getarea(){
		return 0;
	
	}
};
class rect: public shape{
public:
	rect(string name="", int width=0, int height=0): shape(name, width, height){}
	double getarea(){
		return width*height;
	
	}
};
class triangular: public shape{
public:
	triangular(string name="", int width=0, int height=0): shape(name, width, height){}
	double getarea(){
		return width*height/2;
	
	}

};
class point{
	int x, y;
public:
	point(int x=0, int y=0){
		this->x=x; this->y=y;
	}
	void show(){cout<<'('<<x<<','<<y<<')'<<endl;}
};
#endif