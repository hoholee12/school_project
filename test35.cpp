#include<cstdlib>
#include<cstdio>
#include<cstring>
#include"tools.h"

struct list{
	int data;
	list *next;
};

int main(){
	list first, second, third;
	first.data=1;
	second.data=2;
	third.data=3;
	
	second.next=&third;
	first.next=&second;
	
	//printf("%d %d %d\n", first.data, first.next->data, first.next->next->data);
	printf("%d %d %d\n", first.data, (*first.next).data, (*(*first.next).next).data); //same shit.
	
	return 0;
}