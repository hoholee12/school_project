#include<iostream>
using namespace std;

class basearray{
private:
	int capacity;
	int *mem;
protected:
	basearray(int capacity=100){this->capacity=capacity; mem=new int [capacity];}
	~basearray(){delete [] mem;}
	void put(int index, int val){mem[index]=val;}
	int get(int index){return mem[index];}
	int getcapacity(){return capacity;}
};

class myqueue: public basearray{
public:
	myqueue(int capacity): basearray(capacity){}
	void enqueue(int n){
		for(int i=0;i<getcapacity();i++){
			if(!get(i)){
				put(i, n);
				break;
			}
		}
	}
	int capacity(){return getcapacity();}
	int length(){
		int x=0;
		for(int &i=x;i<getcapacity();i++){
			if(get(i)) break;
		}
		int j=x;
		for(int &i=j;i<getcapacity();i++){
			if(!get(i)) break;
		}
		return j-x;
	}
	int dequeue(){
		int tmp;
		for(int i=0;i<getcapacity();i++){
			if(get(i)){
				tmp=get(i);
				put(i, 0); //NULL
				break;
			}
		}
		return tmp;
	}
};

int main(){
	myqueue mq(100);
	int n;
	cout<<"큐에 삽입할 5개의 정수를 입력하라>> ";
	for(int i=0;i<5;i++){
		cin>>n;
		mq.enqueue(n);
	}
	cout<<"큐의 용량:"<<mq.capacity()<<", 큐의 크기:"<<mq.length()<<endl;
	cout<<"큐의 원소를 순서대로 제거하여 출력한다>> ";
	while(mq.length()!=0){
		cout<<mq.dequeue()<<' ';
	}
	cout<<endl<<"큐의 현재 크기:"<<mq.length()<<endl;
	return 0;
}