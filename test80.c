#include<stdio.h>
#include"test80.h"

char *func_str(){
	static char ptr[]="hello, world";
	
	
	return ptr;
}

char *func_str2(){
	char ptr[]="doesnt work";
	
	
	return ptr;
}

int main(){
	char *ptr;
	
	ptr=func_str();
	func_str2();
	
	printf("%s\n", ptr);
	
	return 0;
}