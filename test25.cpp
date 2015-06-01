#include<iostream>
#include<climits>
using namespace std;

class stack{
private:
	int *stuff;
public:
	stack(){stuff=new int [INT_MAX];}
	bool operator!(){ //check if empty
		if(!stuff[0]) return true;
		else return false;
	}
	stack operator<<(int stuff){ //push
		for(int i=0; i<INT_MAX;i++){
			if(!this->stuff[i]){
				this->stuff[i]=stuff;
				break;
			}
		
		}
		return *this;
	}
	void operator~(){ //pop all
		for(int i=0; i<INT_MAX;i++){
			if(!this->stuff[i]){
				break;
			}
			cout<<this->stuff[i]<<' ';
			this->stuff[i]=0; //NULL
		}
		cout<<endl;
	}
	stack operator>>(int &stuff){ //pop
		if(!this->stuff[0]){
			cout<<"empty."<<endl;
		}else{
		for(int i=0; i<INT_MAX;i++){
			if(!this->stuff[i]){
				stuff=this->stuff[i-1];
				this->stuff[i-1]=0; //NULL
				break;
			}
		}
		}
		return *this;
	}
	/*stack operator>>(int &avg){
		avg=0;int j=0;
		for(int &i=j; i<INT_MAX;i++){
			if(!stuff[i]){
				break;
			}
			avg+=stuff[i];
		}
		avg/=j;
		return *this;
	}*/
};

int main(){
	stack slack;
	slack<<3<<5<<10;
	while(1){
		if(!slack) break;
		int x;
		slack>>x;
		cout<<x<<' ';
	}
	cout<<endl;
	
	return 0;
}