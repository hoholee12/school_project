#include<iostream>
using namespace std;

void swap(int &a,int &b){
	int temp=a;
	a=b;b=temp;
}

int main(){
	const int size=5;
	bool click=false;
	int array[size]={23,42,56,78,32};
	while(1){
		for(int i=1;i<size;i++){
			if(array[i-1]>array[i]){
				//cout<<array[i-1]<<' '<<array[i]<<endl;
				swap(array[i-1],array[i]);
				click=true;
			}
		}
		if(click==false)break;
		click=false;
	}
	for(int i=0;i<size;i++){
		cout<<array[i]<<' ';
	}
	return 0;
}