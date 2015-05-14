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
	
	/*advanced algorithm*/
	//approx. 1.5 times faster, almost half less cycle count.
	long long count=0;
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			count++;
			if(count%(rand()%(size*(size/10))+1)==0){//improve performance. +1 to avoid dividing by zero.
				cout<<"\rcounting: "<<count<<" cycles";
				cout.flush();}
			if(array[i]>array[j])swap(array[i],array[j]);
		}
	}
	cout<<"\rcounting: "<<count<<" cycles";
	cout.flush();
	char input;
	cout<<endl<<"count finished. view generated?(y/n)";
#ifndef _WIN32
	cin>>input;
#else
	input=getch();
#endif
	if(input=='y'){
		//print
		for(int i=0;i<size;i++){
			cout<<array[i]<<'\t';
		}
	}else cout<<endl<<"aborted.";
	delete [] array;
	return 0;
}