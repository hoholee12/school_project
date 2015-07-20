#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()
#include<type_traits>
int main(){
	char str[]="hello";
	append(str, "fuck", 3);
	printf("%s\n", str);
	return 0;
}