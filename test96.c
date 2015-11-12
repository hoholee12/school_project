#include<stdio.h>

void stuff(void (*f)()){
	int i;
	for(i=0;i<5;i++)
		(*f)();
	
	
}

void func(){
	
	fprintf(stdout, "hello, world\n");
	
	
}


int main(){
	stuff(func);

	return 0;
}