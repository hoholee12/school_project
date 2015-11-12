#include<stdio.h>

void stuff(void (*f)(int)){
	
	
	
}

void func(int x){
	
	fprintf(stdout, "hello, world\n");
	
	
}


int main(){
	stuff(func);

	return 0;
}