#include<cstdlib>
#include<cstdio>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()
#include<type_traits>
int main(){
	char test[]="ABCABCABCABCABCABCABC";
	char *str=test; //use this method if you dont want to get some BS.
	char *ptr=strchr(str, 'A');
	char *ptr2=strrchr(str, 'A');
	printf("%s\t%s\t%s\n", ptr, str, ptr2);
	
	return 0;
}