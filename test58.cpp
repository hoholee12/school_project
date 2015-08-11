#include<stdlib.h> //malloc, srand, rand
#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<search.h>
#include<string.h> //memstuff, strstuff
//#include<ctype.h>
#include<math.h> //fmod
#include<time.h>

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



int main(int argc, char **argv){
	const int tablesize=10;
	const int elementsize=15;
	
	char table[tablesize][elementsize]={"hello", "linux", "c"};
	char *ptr;
	size_t datanum=3;
	
	ptr=(char *)lfind("linux", table, &datanum, elementsize, compare);
	if(ptr==NULL) printf("not found.\n");
	else printf("%s\n", ptr);
	
	ptr=(char *)lfind("programming", table, &datanum, elementsize, compare);
	if(ptr==NULL) printf("not found.\n");
	else printf("%s\n", ptr);
	
	
	return 0;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done
