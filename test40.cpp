#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<csignal>
#include"tools.h"
#define max(a, b) (a>b)?a:b
//#include<ctype.h> //isalpha()


#include<type_traits>
int main(){
	printf("%d\n", std::is_same<int, int>::value); //1
	printf("%d\n", std::is_same<const int, int>::value); //0

	return 0;
}