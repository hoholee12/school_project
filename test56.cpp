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
	double fra, itr;
	printf("%g\n", ceil(123.45));
	printf("%g\n", floor(345.67));
	
	fra=modf(123.45, &itr);
	printf("%g, %g\n", itr, fra);
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done