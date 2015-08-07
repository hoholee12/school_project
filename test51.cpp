#include<cstdlib> //malloc
#include<cstdio>
#include<csignal>
#include<pthread.h>
#include<cstring> //memstuff

int main(){
	for(int i=0; i<256; i++) printf("%c", i); //full ascii table
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done