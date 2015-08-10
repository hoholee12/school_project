#include<stdlib.h> //malloc, srand, rand
#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<string.h> //memstuff
//#include<ctype.h>
#include<math.h> //fmod
#include<time.h>

char *memchr(char *str, const char ch, size_t/*unsigned int*/ n){
	size_t i=0;
	for(; i<n&&(str[0]!=ch); i++) str++;
	if(!str[0]) return NULL;
	return str;
}

const int MAX=128;


void seed(){
	srand((unsigned)time(NULL)); //functions CANNOT be called from global...
}

int main(){
	seed();
	
	for(int i=0; i<10; i++) printf("%d ", rand()%100);
	
	printf("\n");
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done