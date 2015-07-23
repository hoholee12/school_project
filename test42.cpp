#include<cstdlib>
#include<cstdio>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()
#include<type_traits>
int main(){
	char *ptrstr;
	
	ptrstr=strdup("shrek is love, shrek is life.");
	
	printf("%s\n", ptrstr);
	
	return 0;
}