#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
#include<ctype.h> //isalpha()



int numalpha=0; //global variable

void result(int){
	printf("%d\n", numalpha);
	exit(0);
}

int main(){
	int ch;
	signal(SIGINT, result); //^C politely ask
	signal(SIGTSTP, result); //^Z pause a process
	signal(SIGQUIT, result); //^\ mercilessly kill
	signal(SIGTERM, result); // terminate
	while((ch=getchar())!=EOF){
		//if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
		if(isalpha(ch)){
			numalpha++;
		}
	}
	result(0); //^D end of input
	
	
	
	return 0;
}