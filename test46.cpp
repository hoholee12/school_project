#include<cstdlib>
#include<cstdio>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()
#include<type_traits>
int main(){
	char test[]="linux sucks bsd dick";
	char *str=test; //use this method if you dont want to get some BS.
	printf("%x\n", str); // %x -> hex address
	strstr(str, "linux");
	printf("%s\t%x\n", str, str);
	
	return 0;
}