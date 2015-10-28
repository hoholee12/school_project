#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>


int main(){
	void *arr;
	
	arr=malloc(10);
	
	((int *)arr)[0]=123;
	((int *)arr)[1]=456;
	((int *)arr)[2]=789;
	((int *)arr)[3]=101112;
	((int *)arr)[4]=131415;
	
	((int *)arr)[5]=161718;
	printf("%d %d %d %d %d %d\n", ((int *)arr)[0], ((int *)arr)[1], ((int *)arr)[2], ((int *)arr)[3], ((int *)arr)[4], ((int *)arr)[5]);
	free(arr); /*what?!*/
	
	
	
	return 0;
	
}