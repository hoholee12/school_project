#include<stdlib.h> //malloc, srand, rand, abort
#include<stdio.h> //perror(uses strerror)
#include<signal.h>
#include<pthread.h>
#include<search.h>
#include<string.h> //memstuff, strstuff, strerror(finds out what the error number represent)
//#include<ctype.h>
#include<math.h> //fmod
#include<time.h>
#include<errno.h>

#define NDEBUG //put before assert.h to skip debugging.
#include<assert.h>

char *memchr(char *str, const char ch, size_t/*unsigned int*/ n){
	size_t i=0;
	for(; i<n&&(str[0]!=ch); i++) str++;
	if(!str[0]) return NULL;
	return str;
}

template<typename T> void arrsort(T *arr){
	int i, j, fail=0;
	T tmp;
	do{
		for(i=0; arr[i+1]; i++){
			if(arr[i]>arr[i+1]){
				tmp=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=tmp;
			}
		}
		for(j=0; arr[j+1]; j++){
			if(arr[j]>arr[j+1]){
				fail=1;
				break;
			}
		}
		if(i==j) fail=0;
	}while(fail==1);
}


void seed(){
	srand((unsigned)time(NULL)); //functions CANNOT be called from global...
}

int compare(const void *a, const void *b){
	return strcmp((char *)a, (char *)b);
}

template<typename T>void myassert(T exp){
	if(!exp){
		printf("%s:%d:Assertion failed.\n", __FILE__, __LINE__);
		abort();
	}

}

void my_perror(const char *str){
	printf("%s: %s\n", str, strerror(errno));
}
//int hello;
//hello=0; //this is not possible outside of function.

//int hello=0; //only this works. global variable

int main(int argc, char **argv){
	
	errno=0; //initialize.
	
	int i;
	printf("argc: %d\n", argc-1); //argv[0] is the name of the executable itself, duh
	
	for(i=1; i<argc; i++) printf("%8d: %s\n", i, argv[i]);
	
	return errno;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done
