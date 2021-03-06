#include<stdlib.h> //malloc, srand, rand, abort, atoi
#include<stdio.h> //perror(uses strerror)
#include<signal.h>
#include<pthread.h>
#include<search.h>
#include<string.h> //memstuff, strstuff, strerror(finds out what the error number represent)
//#include<ctype.h>
#include<math.h> //fmod
#include<time.h>
#include<errno.h>
#include<unistd.h> //getopt #getrekt

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

//char str[] == array of chars aka string
//char *str[] == pointer of strings aka ??


void stuff(int *hello){
	hello=(int *)malloc(1*sizeof(int));
	hello[0]=420;
	printf("%d\n", hello[0]);
}

void stuff2(int **hello){
	*hello=(int *)malloc(1*sizeof(int));
	*hello[0]=420;

}

//always declare heap inside main function.
//if you want to do it on other function, you will have to use the double pointer to pass back to main.(otherwise segfault happens)



void testprint(char **arr){
	static int seed_ready=0;
	if(seed_ready!=1){
		seed();
		seed_ready=1;
	}
	int x=rand()%3;
	int y=rand()%3;
	printf("%c\n", arr[y][x]);

}

int flag=0; //global var, can be declared on others by extern.
//static int flag=0; //extern undeclarable in other cpp files.

//declaring function that use a global var that was not declared yet will confuse the compiler...do it orderly!
void output_file(FILE *fp){
	int ch, line=1;
	if(flag) printf("1   ");
	while((ch=getc(fp))!=EOF){
		putc(ch, stdout);
		if(flag&&(ch=='\n')) printf("%-4d", ++line);
	}
}

extern char **environ;

int main(int argc, char *argv[], char *envp[]){
	errno=0;
	printf("environ version\n");
	for(int i=0; environ[i]; i++) printf("%s\n", environ[i]);
	printf("envp version\n");
	for(int i=0; envp[i]; i++) printf("%s\n", envp[i]);
	
	
	
	return errno;
}


//for i in $(ls); do echo -n -e "\e[1;31m$i\e[0m   "; cat $i; done
