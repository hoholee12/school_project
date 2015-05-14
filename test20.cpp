#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>

#ifdef _WIN32
#include<conio.h>
#else
#include<ncurses.h>
#include<unistd.h>
#endif
using namespace std;

void swap(int &a,int &b){
	int temp=a;
	a=b;b=temp;
}

int main(int argc, char** argv){
	static int option;
	if(argv[1])option=atoi(argv[1]);
	else option=0;
	srand((unsigned)time(0));
	const int size=option;
	int *array=new int[size];
	for(int i=0;i<size;i++){
		array[i]=rand()%size;
	}
	
	/*a very generic algorithm*/
	bool click=false;
	int count=0;
	while(1){
		for(int i=1;i<size;i++){
			count++;
			if(count%(rand()%(size*(size/10))+1)==0){//improve performance. +1 to avoid dividing by zero.
				cout<<"\rcounting: "<<count<<" cycles";
				cout.flush();}
			if(array[i-1]>array[i]){
				swap(array[i-1],array[i]);
				click=true;
			}
		}
		if(click==false)break;
		click=false;
	}
	cout<<"\rcounting: "<<count<<" cycles";
	cout.flush();
	char input;
	cout<<endl<<"count finished. view generated?(y/n)";
#ifndef _WIN32
	cin.clear();
	cin.ignore(32767,'\n');
#endif
	cin>>input;
	if(input=='y'){
		//print
		for(int i=0;i<size;i++){
			cout<<array[i]<<'\t';
		}
	}else cout<<endl<<"aborted.";
	delete [] array;
	return 0;
}