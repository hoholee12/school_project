#include<cstdlib>
#include<cstdio>
#include<signal.h>
#include<cstring>
#include"tools.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wparentheses"
//common ascii stuff
//0~9 => 48~57
//a~z => 97~122
//A~Z => 65~90

static int num1=0, nums=0;

void handler(int){
	printf("fuck you.\n");
	//printf("%d %d\n", ::num1, ::nums);
	//exit(0);
}

static const int zero=0;
int main(int argc, char **argv, char **envp){
	int ch;
	signal(SIGINT, handler); //^C politely ask
	signal(SIGTSTP, handler); //^Z pause a process
	signal(SIGQUIT, handler); //^\ mercilessly kill
	signal(SIGTERM, handler); // terminate
	while((ch=getchar())){
		if((ch>='A')&&(ch<='Z')) ::num1++;
		else if((ch>='a')&&(ch<='z')) ::nums++;
	}
	return 0;
}