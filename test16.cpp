#include<iostream>
#include<string>
using namespace std;

class Histogram{
private:
	string *p;
public:
	Histogram(string str){p=new string(str);}
	void put(string str){*p+=str;}
	void putc(char c){*p+=c;}
	void print(){cout<<*p<<endl<<endl;
		char j; int alphabetNum=0;
		for(int i=0; i<p->length();i++){
			j=(*p)[i];
			if(j>='A'&&j<='Z'){
				(*p)[i]=j-'Z'+'z';
				alphabetNum++;
			}else if(j>='a'&&j<='z')
				alphabetNum++;
		}
		cout<<"총 알파벳 수 "<<alphabetNum<<endl<<endl;
		int hello;
		for(char i='a';i<='z';i++){
			hello=0;
			for(int j=0; j<p->length();j++){
				if(i==(*p)[j])
					hello++;
			}
			cout<<i<<" ("<<hello<<") : ";
			for(int i=1;i<=hello;i++)
				cout<<'*';
			cout<<endl;
		}
	};
};

int main(){
	Histogram elvisHisto("Wise men say, only fools rush in But I can't help, ");
	elvisHisto.put("falling in love with you");
	elvisHisto.putc('-');
	elvisHisto.put("Elvis Presley");
	elvisHisto.print();
	return 0;
}