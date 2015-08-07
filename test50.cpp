#include<cstdlib> //malloc
#include<cstdio>
#include<csignal>
#include<pthread.h>
#include<cstring> //memstuff

int main(){
	int *ptr;
	int arr[5]={1,2,3,4,5};
	int i;
	
	ptr=(int *)calloc(5, sizeof(int));
	if(ptr==NULL) exit(1);
	memcpy(ptr, arr, sizeof(int)*5);
	
	for(i=0; i<5; i++) printf("%d ", ptr[i]);
	printf("\n");
	
	ptr=(int *)realloc(ptr, sizeof(int)*10);
	if(ptr==NULL) exit(1);
	memcpy(ptr+5, arr, sizeof(int)*5);
	
	for(i=0; i<10; i++) printf("%d ", ptr[i]);
	
	free(ptr);
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done