#include<cstdlib>
#include<cstdio>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()
#include<type_traits>
int main(){
	char test[]="linux sucks sucks bsd dick";
	char *str=test; //use this method if you dont want to get some BS.
	printf("%d\n", str); // %x -> hex address
	strstr(str, "sucks");
	printf("%s\t%d\n", str, str);
	strrstr(str, "sucks", 1);
	printf("%s\t%d\n", str, str);
	
	return 0;
}