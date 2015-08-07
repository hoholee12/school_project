#include<cstdlib> //malloc
#include<cstdio>
#include<csignal>
#include<pthread.h>
#include<cstring> //memstuff

char *memchr(char *str, const char ch, size_t/*unsigned int*/ n){
	size_t i=0;
	for(; i<n&&(str[0]!=ch); i++) str++;
	if(!str[0]) return NULL;
	return str;
}

int main(){
	char test[]="ABCDEABCDEABCDE";
	char *str=test;
	for(; (str=memchr(str, 'A', strlen(str))); str++) printf("%s\n", str); //in between bracket - str received something: true, str received NULL: false.
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done