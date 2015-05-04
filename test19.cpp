#include<iostream>
using namespace std;

class myintstack{
private:
	int *p=new int[10];
	int tos; //top index of stack
public:
	myintstack(){for(int i=0;i<10;i++){
		p[i]=-1;
	}}
	bool push(int n){
		for(int i=0; i<10;i++){
			if(p[i]==-1){
				p[i]=n;
				tos=i;
				//cout<<p[i]<<endl;
				return true;
			}
		}
		return false;
	}
	bool pop(int &n){
		for(int i=0;i<10;i++){
			if(p[tos-i]!=-1){n=p[tos-i]; p[tos-i]=-1;return true;}
		}
		return false;
	}
};

int main(){

	myintstack a;
	//if(a.push(12)){cout<<"okay";}else cout<<"not okay";
	for(int i=0;i<11;i++){
		if(a.push(i))cout<<i<<' ';
		else cout<<endl<<i+1<<"th stack full"<<endl;
	}
	int n;
	for(int i=0;i<11;i++){
		if(a.pop(n))cout<<n<<' ';
		else cout<<endl<<i+1<<"th stack empty";
	}
	cout<<endl;
	return 0;
}