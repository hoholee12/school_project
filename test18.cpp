#include<iostream>
#include<string>
using namespace std;

class Histogram{
private:
	string str;
public:
	Histogram(string str){this->str=str;}
	void countChart(string str);
	void put(string str){this->str+=str;}
	void putc(char c){this->str+=c;}
	void print(){cout<<str<<endl<<endl;
		int count=0;
		for(int i=0;i<str.length();i++){
			if(str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z'){
				count++;
				if(str[i]>='A'&&str[i]<='Z'){
					str[i]=str[i]+'a'-'A';
				}
			}
		}
		cout<<"총 알파벳 수 "<<count<<endl<<endl;
		countChart(str);
	}
};

inline void Histogram::countChart(string str){
	int hello=0;
	for(char i='a';i<='z';i++){
		hello=0;
		for(int j=0; j<str.length();j++){
			if(i==str[j])
				hello++;
		}
		cout<<i<<" ("<<hello<<") : ";
		for(int i=1;i<=hello;i++)
			cout<<'*';
		cout<<endl;
	}
}

int main(){
	Histogram elvisHisto("Wise men say, only fools rush in But I can't help, ");
	elvisHisto.put("falling in love with you");
	elvisHisto.putc('-');
	elvisHisto.put("Elvis Presley");
	elvisHisto.print();
	return 0;
}