#include<cstdlib>
#include<cstdio>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()
#include<type_traits>
int main(){
	char str[]="seoulKorea";
	
	char *str2=strpbrk(str, "elmnopsu");
	
	printf("%s\n", str2);
	
	return 0;
}