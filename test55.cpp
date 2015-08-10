//#include<stdlib.h> //malloc
#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<string.h> //memstuff
//#include<ctype.h>
#include<math.h> //fmod

char *memchr(char *str, const char ch, size_t/*unsigned int*/ n){
	size_t i=0;
	for(; i<n&&(str[0]!=ch); i++) str++;
	if(!str[0]) return NULL;
	return str;
}

const int MAX=128;

typedef struct{
	int quot;
	int rem;

} div_t;

typedef struct{
	long quot;
	long rem;
} ldiv_t;


div_t *div(int a, int b){
	div_t *blah=new div_t;
	blah->quot=a/b;
	blah->rem=a%b;
	return blah;
}

ldiv_t *ldiv(long a, long b){
	ldiv_t *blah=new ldiv_t;
	blah->quot=a/b;
	blah->rem=a%b;
	return blah;
}


int main(){
	div_t *result1;
	ldiv_t *result2;
	result1=div(12345, 2345);
	result2=ldiv(123456789, 12345678);
	
	printf("%d, %d\n", result1->quot, result1->rem);
	printf("%ld, %ld\n", result2->quot, result2->rem);
	
	printf("%g\n", fmod(23.456, 2.345));
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done