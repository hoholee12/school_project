#include<cstdlib>
#include<cstdio>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()
#include<type_traits>
int main(){
	const int blocksize=20;
	char str[blocksize]="fuck off";
	//printf("input string=>");
	//scanf("%s", str); //str itself is an address that points to array.
	//scanf also does not play nicely with "char *str" format....
	
	strrev(str);
	printf("%s\n", str);
	
	//for(int i=strlen(str)-1; i>=0; i--) printf("%c", str[i]);
	
	
	
	
	return 0;
}