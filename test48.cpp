#include<cstdlib>
#include<cstdio>
#include<csignal>
#include<pthread.h>
#include<cstring>

typedef struct list{
	char name[10];
	int age;
	list *next;

} list;

int main(){
	//list *ptr=new list [sizeof(list)];
	list *ptr=(list *)malloc(sizeof(list));
	
	if(!ptr) exit(1); //failed
	
	strcpy(ptr->name, "joker");
	ptr->age=30;
	
	//ptr->next=new list [sizeof(list)];
	ptr->next=(list *)malloc(sizeof(list));
	strcpy(ptr->next->name, "johnny");
	ptr->next->age=35;
	
	printf("%s's age: %d\n", ptr->name, ptr->age);
	printf("%s's age: %d\n", ptr->next->name, ptr->next->age);
	
	
	return 0;
}