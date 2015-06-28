#include<cstdlib>
#include<cstdio>
#include<cstring>
#include"tools.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-parameter"
//common ascii stuff
//0~9 => 48~57
//a~z => 97~122
//A~Z => 65~90

int main(int argc, char **argv, char **envp){
	if(!argv[1]) argv[1]="0";
	if(argv[1][1]){
		printf("requires a single character.\n");
		exit(1);
	}
	if(!argv[2]) argv[2]="8";
	printbit(argv[1][0], atoi(argv[2])/*segfault if empty*/);
	return 0;
}

