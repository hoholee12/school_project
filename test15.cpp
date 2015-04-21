#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;

class Date{
private:
	int year; int month; int day;
public:
	Date(int year, int month, int day){this->year=year;this->month=month;this->day=day;}
	Date(string date){
		const char *cdate=date.c_str();
		//cout<<cdate<<endl;
		char *p=new char[10];
		int count=0;int j=0;
		for(int i=0;i<=strlen(cdate);i++){
			p[j]=cdate[i];
			//cout<<cdate[i]<<endl;
			j++;
			if(cdate[i]=='/'||cdate[i]=='\0'){ //one word: FUCK.
				//cout<<p<<endl;
				j=0;
				if(count==0){
					year=atoi(p);
				}else if(count==1){
					month=atoi(p);
				}else if(count==2){
					day=atoi(p);
				}
				delete [] p;
				p=new char[10];
				count++;
			}
		}
	}
	void show(){cout<<year<<"년"<<month<<"월"<<day<<"일"<<endl;}
	int getYear(){return year;}
	int getMonth(){return month;}
	int getDay(){return day;}
};

int main(int argc, char *argv[]){
	Date birth(2014,3,20);
	Date independenceDay("1945/8/15");
	independenceDay.show();
	cout<<birth.getYear()<<','<<birth.getMonth()<<','<<birth.getDay()<<endl;
	return 0;
}