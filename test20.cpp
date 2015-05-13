#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;

void swap(int &a,int &b){
	int temp=a;
	a=b;b=temp;
}

int main(int argc, char* argv[]){
	static int option;
	if(argv[1])option=atol(argv[1]);
	else option=0;
	srand((unsigned)time(0));
	const int size=option;
	int *array=new int[size];
	for(int i=0;i<size;i++){
		array[i]=rand()%size;
	}
	
	/*a very generic algorithm*/
	bool click=false;
	while(1){
		for(int i=1;i<size;i++){
			if(array[i-1]>array[i]){
				swap(array[i-1],array[i]);
				click=true;
			}
		}
		if(click==false)break;
		click=false;
	}
	//print
	for(int i=0;i<size;i++){
		cout<<array[i]<<' ';
	}
	delete [] array;
	return 0;
}