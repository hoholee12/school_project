#include<iostream>
#include<climits>
using namespace std;

class statistics{
private:
	int *stuff;
public:
	statistics(){stuff=new int [INT_MAX];}
	bool operator!(){ //check if empty
		if(!stuff[0]) return true;
		else return false;
	}
	statistics operator<<(int stuff){ //push
		for(int i=0; i<INT_MAX;i++){
			if(!this->stuff[i]){
				this->stuff[i]=stuff;
				break;
			}
		
		}
		return *this;
	}
	void operator~(){ //pop
		for(int i=0; i<INT_MAX;i++){
			if(!this->stuff[i]){
				break;
			}
			cout<<this->stuff[i]<<' ';
			this->stuff[i]=0;
		}
		cout<<endl;
	}
	statistics operator>>(int &avg){
		avg=0;int j=0;
		for(int &i=j; i<INT_MAX;i++){
			if(!stuff[i]){
				break;
			}
			avg+=stuff[i];
		}
		avg/=j;
		return *this;
	}
};

int main(){
	statistics stat;
	//stat.push(1);
	if(!stat) cout<<"no data"<<endl;

	int x[5];
	cout<<"enter five integers";
	
	for(int i=0;i<5;i++){ cin>>x[i];stat<<x[i];}
	stat<<100<<200;
	//~stat;
	
	if(!stat) cout<<"no data"<<endl;
	
	int avg;
	stat>>avg;
	cout<<"average = "<<avg<<endl;
	
	return 0;
}