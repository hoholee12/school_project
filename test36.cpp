#include<cstdlib>
#include<cstdio>
#include<cstring>
#include"tools.h"

struct list{
	int data;
	list *next;
};

int main(){
	list *head;
	//head=(list *)malloc(sizeof(list));
	//list *head=new list;
	head=new list; //same shit.
	head->data=1;
	printf("%d\n", head->data);
	
	return 0;
}