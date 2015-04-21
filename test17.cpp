#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
using namespace std;

class Player{
private:
	string name;
public:
	Player(){}
	void inputname(string name){this->name=name;}
	string printname(){return name;}
};

class GamblingGame{
private:
	Player *firstp;
	Player *secondp;
public:
	GamblingGame(Player *firstp, Player *secondp){
		this->firstp=firstp;
		this->secondp=secondp;
	}
	void show(){
		//cout<<firstp->printname()<<' '<<secondp->printname();
		while(1){
			cout<<firstp->printname()<<":<Enter>";cin.ignore();
			int *p=new int[3];
			cout<<'\t';
			int prev=5;int same=0;
			for(int i=0;i<3;i++){
				*(p+i)=rand()%3;
				if(prev==5)
					prev=*(p+i);
				else if(*(p+i)==prev)
					same++;
				cout<<'\t'<<*(p+i);
			}
			if(same==2){cout<<'\t'<<firstp->printname()<<"님 승리!!"<<endl;break;}
			else cout<<"\t아쉽네요!"<<endl;
			delete [] p;
			cout<<secondp->printname()<<":<Enter>";cin.ignore();
			int *q=new int[3];
			cout<<'\t';
			prev=5;same=0;
			for(int i=0;i<3;i++){
				*(q+i)=rand()%3;
				if(prev==5)
					prev=*(q+i);
				else if(*(q+i)==prev)
					same++;
				cout<<'\t'<<*(q+i);
			}
			if(same==2){cout<<'\t'<<secondp->printname()<<"님 승리!!"<<endl;break;}
			else cout<<"\t아쉽네요!"<<endl;
			delete [] q;
		}
	}
};

int main(){
	srand((unsigned)time(NULL));
	Player *p=new Player[2];
	cout<<"*****갬블링 게임을 시작합니다. *****"<<endl;
	string name;
	cout<<"첫번째 선수 이름>>";cin>>name;p->inputname(name);
	cout<<"두번째 선수 이름>>";cin>>name;(p+1)->inputname(name);
	//cout<<p->printname()<<' '<<(p+1)->printname()<<endl;
	GamblingGame hello(p,p+1);
	cin.ignore();
	hello.show();
	return 0;
}
