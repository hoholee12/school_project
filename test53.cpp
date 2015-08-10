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
	const char *quit="quit";
	char *str=new char [0]; //c++ 'new' allows dynamic expanding.
	
	for(;;){
		printf("input string ==> ");
		scanf("%s", str);
		if(!memcmp(str, quit, 4)) break;
		printf("%s\n", str);
	}
	delete [] str;
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done