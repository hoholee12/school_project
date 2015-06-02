#include<iostream>
using namespace std;

class basememory{
	char *mem;
protected:
	basememory(int size){mem=new char[size];}
public:
	char read(int i){return mem[i];}
	void write(int i, char a){mem[i]=a;}
};

class rom: public basememory{
public:
	rom(int size, char *ch, int arr): basememory(size){
		for(int i=0;i<arr;i++){
			write(i, ch[i]);
		}
	} //burned to rom
};

class ram: public basememory{
public:
	ram(int size): basememory(size){}
	
};

int main(){
	char x[5]={'h', 'e', 'l', 'l', 'o'};
	rom biosrom(1024*10, x, 5);
	ram mainmemory(1024*1024);
	
	for(int i=0; i<5; i++) mainmemory.write(i, biosrom.read(i));
	for(int i=0; i<5; i++) cout<<mainmemory.read(i);
	
	return 0;
}