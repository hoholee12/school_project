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
	
	/*advanced algorithm*/
	//approx. 150ms faster than test20.cpp with 10000 random numbers.
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(array[i]>array[j])swap(array[i],array[j]);
		}
	}
	//print
	for(int i=0;i<size;i++){
		cout<<array[i]<<' ';
	}
	delete [] array;
	return 0;
}