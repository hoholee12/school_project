#include<iostream>
using namespace std;

class ArrayUtility2{
private:

public:
	static int *concat(int s1[],int s2[], int size){ //in order to pass an address, function needs to have an asterisk.
		int *stuff=new int[size*2];
		for(int i=0; i<size;i++){
			stuff[i]=s1[i];
		}
		for(int i=0; i<size;i++){
			stuff[i+5]=s2[i];
		}
		return stuff;
	}
	static int *remove(int s1[],int s2[], int size, int &retSize){
		int *stuff=new int[size];
		for(int i=0; i<size;i++){
			stuff[i]=s1[i];
		}
		for(int i=0; i<size;i++){
			for(int j=0; j<size;i++){
				if(stuff[i]==s2[j]){
					stuff[i]=NULL; //null
				}
			}
		}
		for(int i=0; i<size;i++){
			if(stuff[i])retSize++;
		}
		return stuff;
	}
};

int main(){
	int x[5];
	cout<<"정수 삽입 5개 x>>";
	for(int i=0; i<5;i++)cin>>x[i];
	int y[5];
	cout<<"정수 삽입 5개 y>>";
	for(int i=0; i<5;i++)cin>>y[i];
	
	int *stuff=ArrayUtility2::concat(x,y,5);
	for(int i=0; i<10; i++){
		cout<<stuff[i]<<' ';
	}
	delete [] stuff;
	cout<<"x[]-y[]";
	int retSize=0;
	int *stuff2=ArrayUtility2::remove(x,y,5,retSize);
	cout<<retSize<<"chars"<<endl;
	
	delete [] stuff2;
	return 0;
}